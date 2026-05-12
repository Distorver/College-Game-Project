#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <GL/glut.h>
#include "../common/Structs.h"
#include "../common/Constants.h"
#include "../core/GameManager.h"
#include "../core/InputHandler.h"

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
int frameCount = 0;
float fpsTimer = 0.0f;
int currentFPS = 0;
float lastDx;

void calculateDeltaTime() {
    float currentFrameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    // Update FPS counter
    frameCount++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0f) {
        currentFPS = frameCount;
        frameCount = 0;
        fpsTimer = 0.0f;
    }
}

void updatePhysics() {
    calculateDeltaTime();

    float dx = 0.0f;

    // Horizontal movement
    if (keyStates['a'] || keyStates['A'] || specialKeyStates[GLUT_KEY_LEFT]) {
        dx -= player.velX * deltaTime;
    }
    if (keyStates['d'] || keyStates['D'] || specialKeyStates[GLUT_KEY_RIGHT]) {
        dx += player.velX * deltaTime;
    }

    if(gameState == PLAYING)
        player.x += dx;

    // Platform collision (horizontal)
    for (int i = 0; i < currentNumPlatforms; i++) {
        Platform &p = currentPlatforms[i];
        bool overlapX = player.x + player.width > p.x && player.x < p.x + p.width;
        bool overlapY = player.y + player.height > p.y - p.height && player.y < p.y;

        if (overlapX && overlapY) {
            if (dx > 0) {
                player.x = p.x - player.width;
            } else if (dx < 0) {
                player.x = p.x + p.width;
            }
        }
    }

    // Vertical movement
    if (!player.isGrounded) {
        player.velY += GRAVITY * deltaTime;
    }

    player.y += player.velY * deltaTime;
    player.isGrounded = false;

    // Platform collision (vertical)
    for (int i = 0; i < currentNumPlatforms; i++) {
        Platform &p = currentPlatforms[i];
        if (player.x + player.width > p.x && player.x < p.x + p.width) {
            if (player.velY <= 0.0f && player.y <= p.y && player.y + 3.0f > p.y) {
                player.y = p.y;
                player.velY = 0.0f;
                player.isGrounded = true;
                player.jumpCount = 0;
            }
        }
    }
    lastDx = dx;
}

#endif
