#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float x = 5, y = 50, width = 4, height = 4, velX = 25, velY = 0;
    bool isGrounded = false;
    int jumpCount = 0;
};

#endif