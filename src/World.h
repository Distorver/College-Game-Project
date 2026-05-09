#ifndef WORLD_H
#define WORLD_H

struct Platform {
    float x, width;
    bool isTrap = false ;
    float triggerX = 0;
    float y = 30, height = 30;
};

struct Spikes {
    float x;
    bool isHidden = false;
    float triggerX = 65;
    float width = 4, y = 30, height = 4;
};


#endif