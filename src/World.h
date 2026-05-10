#ifndef WORLD_H
#define WORLD_H

struct Platform {
    float x, width;
    bool isTrap = false ;
    float triggerX = 0;
    float y = 30, height = 30;
    bool trigger = false;
};

struct Spikes {
    float x;
    bool isHidden = false;
    float y = 30;
    float triggerX = 60, width = 4, height = 4;
};

struct Goal {
    float x = 145, y = 30, width = 5, height = 6;
};


#endif