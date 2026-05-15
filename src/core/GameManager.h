#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../common/Structs.h"
#include "../common/Constants.h"
#include "../game/LevelData.h"
#include "AudioManager.h"

// Global game state
GameState gameState = PLAYING;
int currentLevel = 1;
Player player;
Goal goal;
bool deathSoundPlayed = false;

Platform* currentPlatforms = nullptr;
int currentNumPlatforms = 0;
Spike* currentSpikes = nullptr;
int currentNumSpikes = 0;

void setLevelData(int level) {
    if (level == 1) {
        currentPlatforms = level1_platforms;
        currentNumPlatforms = NUM_PLATFORMS_L1;
        currentSpikes = level1_spikes;
        currentNumSpikes = NUM_SPIKES_L1;
        goal = {145, 30, 5, 6};
    } else if (level == 2) {
        currentPlatforms = level2_platforms;
        currentNumPlatforms = NUM_PLATFORMS_L2;
        currentSpikes = nullptr;
        currentNumSpikes = 0;
        goal = {145, 30, 5, 6};
    } else if (level == 3) {
        player.x = 140;
        currentPlatforms = level3_platforms;
        currentNumPlatforms = NUM_PLATFORMS_L3;
        currentSpikes = nullptr;
        currentNumSpikes = 0;
        goal = {10, 30, 5, 6};
    }
}

void resetLevelData() {
    if (currentLevel == 1) {
        level1_platforms[1] = {25, 30, true, 30, 30, 30, false};
        level1_platforms[3] = {100, 30, true, 105, 30, 30, false};

        level1_spikes[0] = {61, true, 26};
        level1_spikes[1] = {65, true, 26};
        level1_spikes[2] = {69, true, 26};
        level1_spikes[3] = {73, false, 30};
        level1_spikes[4] = {77, false, 30};
        level1_spikes[5] = {81, false, 30};
        level1_spikes[6] = {85, true, 26};
        level1_spikes[7] = {89, true, 26};
        level1_spikes[8] = {93, true, 26};
    } else if (currentLevel == 2) {
        level2_platforms[0] = {0, 70};
        level2_platforms[1] = {85, 75};
        level2_platforms[2] = {100, 8, true, 80, 30, 15, false};
    } else if (currentLevel == 3) {
        level3_platforms[0] = {0,20,false,0,30,7};
        level3_platforms[1] = {32,20,true,40,30,7};
        level3_platforms[2] = {64,20,true,40,30,7};
        level3_platforms[3] = {96,20,true,40,30,7};
        level3_platforms[4] = {128,20,true,40,30,7};
        level3_platforms[5] = {160,20,true,40,30,7};
    }
}

void resetLevel() {
    player = Player();
    gameState = PLAYING;
    deathSoundPlayed = false;
    setLevelData(currentLevel);
    resetLevelData();
}

void loadLevel(int level) {
    currentLevel = level;
    setLevelData(level);
    resetLevel();
}

void loadNextLevel() {
    if (currentLevel < MAX_LEVELS) {
        currentLevel++;
        loadLevel(currentLevel);
    } else {
        gameState = WON;
    }
}

#endif
