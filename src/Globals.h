#ifndef GLOBALS_H
#define GLOBALS_H

#include "World.h"
#include "Player.h"
#include "GameState.h"

const float GRAVITY = -200.0f;
const float JUMP_FORCE = 60.0f;
const float JUMP_CUT_MULTIPLIER = 0.45f;

Player square;
Goal currentGoal;

int currentLevel = 1;
Platform* currentPlatforms = nullptr;
int currentNumPlatforms = 0;
Spikes* currentSpikes = nullptr;
int currentNumSpikes = 0;

const int numPlatforms_1 = 5;
const int numPlatforms_2 = 3;
const int numPlatforms_3 = 6;

Platform level_1[numPlatforms_1] = {
    {0,25},
    {25,30,true,30},
    {55,45},
    {100,30,true,105},
    {130,30},
};

Platform level_2[numPlatforms_2] = {
    {0,70},
    {85,75},
    {100,8,true,80,30,15}
};

Platform level_3[numPlatforms_3] = {
    {0,20,false,0,30,7},
    {32,20,true,40,30,7},
    {64,20,true,40,30,7},
    {96,20,true,40,30,7},
    {128,20,true,40,30,7},
    {160,20,true,40,30,7}
};

const int numSpikes_1 = 9;

Spikes spikes_1[numSpikes_1] = {
    {61,true,26},
    {65,true,26},
    {69,true,26},

    {73,false,30},
    {77,false,30},
    {81,false,30},

    {85,true,26},
    {89,true,26},
    {93,true,26}
};

void setLevelData(int level) {
    if (level == 1) {
        currentPlatforms = level_1;
        currentNumPlatforms = numPlatforms_1;
        currentSpikes = spikes_1;
        currentNumSpikes = numSpikes_1;
        currentGoal = {145, 30, 5, 6};
    } else if(level == 2) {
        currentPlatforms = level_2;
        currentNumPlatforms = numPlatforms_2;
        currentSpikes = nullptr;
        currentNumSpikes = 0;
        currentGoal = {145, 30, 5, 6};
    }  else if(level == 3) {
        square.x = 140;
        currentPlatforms = level_3;
        currentNumPlatforms = numPlatforms_3;
        currentSpikes = nullptr;
        currentNumSpikes = 0;
        currentGoal = {10, 30, 5, 6};
    } 
}

void resetLevel() {
    square = Player();
    currentState = PLAYING;
    setLevelData(currentLevel);

    if (currentLevel == 1) {
        level_1[1] = {25,30,true,30,30,30,false};
        level_1[3] = {100,30,true,105,30,30,false};

        spikes_1[0] = {61,true,26};
        spikes_1[1] = {65,true,26};
        spikes_1[2] = {69,true,26};

        spikes_1[3] = {73,false,30};
        spikes_1[4] = {77,false,30};
        spikes_1[5] = {81,false,30};

        spikes_1[6] = {85,true,26};
        spikes_1[7] = {89,true,26};
        spikes_1[8] = {93,true,26};
    } else if(currentLevel == 2) {
        square.jumpCount = 1;
        level_2[0] = {0,70};
        level_2[1] = {85,75};
        level_2[2] = {100,8,true,80,30,15,false};
    } else if(currentLevel == 3) {
        level_3[0] = {0,20,false,0,30,7};
        level_3[1] = {32,20,true,40,30,7};
        level_3[2] = {64,20,true,40,30,7};
        level_3[3] = {96,20,true,40,30,7};
        level_3[4] = {128,20,true,40,30,7};
        level_3[5] = {160,20,true,40,30,7};
    }
}

void loadLevel(int level) {
    currentLevel = level;
    setLevelData(level);
    resetLevel();
}

void loadNextLevel() {
    currentLevel = (currentLevel < 3 ? currentLevel + 1 : 1);
    loadLevel(currentLevel);
}

#endif