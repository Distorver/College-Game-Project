#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/prctl.h>

static std::string audioPlayer = "";
static std::atomic<bool> audioInitialized(false);
static std::vector<pid_t> audioPids;
static std::mutex audioPidsMutex;
static std::atomic<bool> audioEnabled(true);
static std::atomic<bool> musicEnabled(true);
static pid_t runSoundPid = -1;
static pid_t musicSoundPid = -1;

static const int MUSIC_VOLUME = 35536; // ~25%
static const int EFFECT_VOLUME = 65536; // max volume for effects

static bool commandExists(const char* cmd) {
    std::string probe = "command -v ";
    probe += cmd;
    probe += " >/dev/null 2>&1";
    return std::system(probe.c_str()) == 0;
}

static void addAudioPid(pid_t pid) {
    std::lock_guard<std::mutex> lock(audioPidsMutex);
    audioPids.push_back(pid);
}

static void removeAudioPid(pid_t pid) {
    std::lock_guard<std::mutex> lock(audioPidsMutex);
    auto it = std::find(audioPids.begin(), audioPids.end(), pid);
    if (it != audioPids.end()) {
        audioPids.erase(it);
    }
}

static void shutdownPid(pid_t pid) {
    if (pid <= 0) return;
    kill(pid, SIGTERM);
    removeAudioPid(pid);
}

static void shutdownAudio() {
    std::lock_guard<std::mutex> lock(audioPidsMutex);
    for (pid_t pid : audioPids) {
        if (pid > 0) {
            kill(pid, SIGTERM);
        }
    }
    audioPids.clear();
    runSoundPid = -1;
    musicSoundPid = -1;
}

static pid_t spawnAudioProcess(const std::vector<std::string>& args) {
    if (args.empty()) return -1;

    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }

    if (pid == 0) {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        std::vector<char*> argv;
        for (const std::string& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);
        execvp(argv[0], argv.data());
        _exit(127);
    }

    addAudioPid(pid);
    return pid;
}

static pid_t spawnShellCommand(const std::string& command) {
    std::vector<std::string> args = { "/bin/sh", "-c", command };
    return spawnAudioProcess(args);
}

static void initAudio() {
    if (audioInitialized) return;
    audioInitialized = true;

    if (commandExists("paplay")) {
        audioPlayer = "paplay";
    } else if (commandExists("aplay")) {
        audioPlayer = "aplay";
    }

    if (!audioPlayer.empty()) {
        std::atexit(shutdownAudio);
    }
}

static std::string audioAssetPath(const char* fileName) {
    return std::string("assets/sounds/") + fileName;
}

static std::vector<std::string> buildAudioCommand(const std::string& path, int volume) {
    std::vector<std::string> args;
    if (audioPlayer == "paplay") {
        args = { audioPlayer, "--volume", std::to_string(volume), path };
    } else if (audioPlayer == "aplay") {
        args = { audioPlayer, path };
    }
    return args;
}

static pid_t playSoundAsync(const std::string& path, int volume, bool loop = false) {
    if (audioPlayer.empty() || !audioEnabled) return -1;
    std::vector<std::string> args = buildAudioCommand(path, volume);
    if (!loop) {
        return spawnAudioProcess(args);
    }

    std::string command;
    if (audioPlayer == "paplay") {
        command = audioPlayer + " --volume " + std::to_string(volume) + " \"" + path + "\"";
    } else {
        command = audioPlayer + " \"" + path + "\"";
    }
    command = "while true; do " + command + "; done";
    return spawnShellCommand(command);
}

inline void playJumpSound() {
    initAudio();
    if (audioPlayer.empty() || !audioEnabled) return;
    playSoundAsync(audioAssetPath("jump.wav"), EFFECT_VOLUME);
}

inline void playDeathSound() {
    initAudio();
    if (audioPlayer.empty()) return;
    playSoundAsync(audioAssetPath("death.wav"), EFFECT_VOLUME);
}

inline void playGoalSound() {
    initAudio();
    if (audioPlayer.empty()) return;
    playSoundAsync(audioAssetPath("goal.wav"), EFFECT_VOLUME);
}

inline void startRunningSound() {
    initAudio();
    if (audioPlayer.empty() || !audioEnabled) return;
    if (runSoundPid > 0) return;
    pid_t pid = playSoundAsync(audioAssetPath("run.wav"), EFFECT_VOLUME, true);
    if (pid > 0) runSoundPid = pid;
}

inline void playRunningSound() {
        initAudio();
    if (audioPlayer.empty()) return;
    playSoundAsync(audioAssetPath("run.wav"), EFFECT_VOLUME);
}

inline void stopRunningSound() {
    if (runSoundPid > 0) {
        shutdownPid(runSoundPid);
        runSoundPid = -1;
    }
}

inline void playBackgroundMusic() {
    initAudio();
    if (audioPlayer.empty() || !audioEnabled || !musicEnabled) return;
    if (musicSoundPid > 0) return;
    pid_t pid = playSoundAsync(audioAssetPath("music.wav"), MUSIC_VOLUME);
    if (pid > 0) musicSoundPid = pid;
}

inline void stopBackgroundMusic() {
    if (musicSoundPid > 0) {
        shutdownPid(musicSoundPid);
        musicSoundPid = -1;
    }
}

inline void stopAudio() {
    shutdownAudio();
}

inline void setAudioEnabled(bool enabled) {
    audioEnabled = enabled;
    if (!enabled) {
        stopAudio();
    } else {
        if (musicEnabled) playBackgroundMusic();
    }
}

inline void toggleAudioEnabled() {
    setAudioEnabled(!audioEnabled);
}

inline bool isAudioEnabled() {
    return audioEnabled;
}

inline void setMusicEnabled(bool enabled) {
    musicEnabled = enabled;
    if (!enabled) {
        stopBackgroundMusic();
    } else if (audioEnabled) {
        playBackgroundMusic();
    }
}

inline void toggleMusicEnabled() {
    setMusicEnabled(!musicEnabled);
}

inline bool isMusicEnabled() {
    return musicEnabled;
}

#endif // AUDIO_MANAGER_H
