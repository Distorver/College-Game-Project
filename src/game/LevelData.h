#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include "../common/Structs.h"

// Level 1 data
const int NUM_PLATFORMS_L1 = 5;
Platform level1_platforms[NUM_PLATFORMS_L1] = {
    {0, 25},
    {25, 30, true, 30},
    {55, 45},
    {100, 30, true, 105},
    {130, 30},
};

const int NUM_SPIKES_L1 = 9;
Spike level1_spikes[NUM_SPIKES_L1] = {
    {61, true, 26},
    {65, true, 26},
    {69, true, 26},
    {73, false, 30},
    {77, false, 30},
    {81, false, 30},
    {85, true, 26},
    {89, true, 26},
    {93, true, 26}
};

// Level 2 data
const int NUM_PLATFORMS_L2 = 3;
Platform level2_platforms[NUM_PLATFORMS_L2] = {
    {0, 70},
    {85, 75},
    {100, 8, true, 80, 30, 15}
};

// Level 3 data
const int NUM_PLATFORMS_L3 = 6;
Platform level3_platforms[NUM_PLATFORMS_L3] = {
    {0, 20, false, 0, 30, 7},
    {32, 20, true, 40, 30, 7},
    {64, 20, true, 40, 30, 7},
    {96, 20, true, 40, 30, 7},
    {128, 20, true, 40, 30, 7},
    {160, 20, true, 40, 30, 7}
};

#endif
