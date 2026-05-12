#ifndef STRUCTS_H
#define STRUCTS_H

struct Platform {
    float x, width;
    bool isTrap = false;
    float triggerX = 0;
    float y = 30, height = 30;
    bool trigger = false;
};

struct Spike {
    float x;
    bool isHidden = false;
    float y = 30;
    float triggerX = 60, width = 4, height = 4;
};

struct Goal {
    float x = 145, y = 30, width = 5, height = 8;
};

struct Player {
    float x = 10, y = 30, width = 2.5, height = 2.5, velX = 28, velY = 0;
    bool isGrounded = false;
    int jumpCount = 0;
};

enum GameState { PLAYING, DIED };

#endif
