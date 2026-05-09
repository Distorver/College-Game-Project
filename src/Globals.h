#ifndef GLOBALS_H
#define GLOBALS_H

#include "World.h"
#include "Player.h"
#include "GameState.h"


const float GRAVITY = -200.0f;        
const float JUMP_FORCE = 60.0f;       
const float JUMP_CUT_MULTIPLIER = 0.45f;       

Player square;


const int numPlatforms = 3;
Platform levels[numPlatforms] = {
    {0,30},
    {55,40},
    {120,40},
};


#endif