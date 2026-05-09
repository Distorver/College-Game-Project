#ifndef GLOBALS_H
#define GLOBALS_H

#include "World.h"
#include "Player.h"
#include "GameState.h"


const float GRAVITY = -200.0f;        
const float JUMP_FORCE = 60.0f;       
const float JUMP_CUT_MULTIPLIER = 0.45f;       

Player square;


const int numPlatforms = 5;
Platform levels[numPlatforms] = {
    {0,25},
    {25,30,true,30},
    {55,45},
    {100,30,true,105},
    {130,30},
};

const int numSpikes = 9;
Spikes spikes[numSpikes] = {
    {59,true,26},
    {63,true,26},
    {67,true,26},
    
    {71,false,30},
    {75,false,30},
    {79,false,30},

    {83,true,26},
    {87,true,26},
    {91,true,26}
};

void resetLevel() {
    square = Player();
    currentState = PLAYING;

    levels[1] = {25,30,true,30};
    levels[3] = {100,30,true,105};

    spikes[0] = {59,true,26};
    spikes[1] = {63,true,26};
    spikes[2] = {67,true,26};

    spikes[3] = {71,false,30};
    spikes[4] = {75,false,30};
    spikes[5] = {79,false,30};
    
    spikes[6] = {83,true,26};
    spikes[7] = {87,true,26};
    spikes[8] = {91,true,26};
}

#endif