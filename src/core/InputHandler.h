#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GL/glut.h>
#include "../common/Structs.h"
#include "../common/Constants.h"
#include "GameManager.h"
#include "../graphics/PlayerAnimator.h"

bool keyStates[MAX_KEYS];
bool specialKeyStates[MAX_KEYS];

void initInput() {
    for (int i = 0; i < MAX_KEYS; i++) {
        keyStates[i] = false;
        specialKeyStates[i] = false;
    }
}

void handleJump() {
    animState = ANIM_JUMP;
    if (currentLevel == 1) {
        if (player.isGrounded) {
            player.velY = JUMP_FORCE;
            player.isGrounded = false;
            player.jumpCount++;
        } else if (player.jumpCount == 1) {
            player.velY = JUMP_FORCE;
            player.jumpCount++;
        }
    } else {
        if (player.isGrounded) {
            player.velY = JUMP_FORCE;
            player.isGrounded = false;
            player.jumpCount++;
        }
    }
}

void onKeyPressed(unsigned char key, int x, int y) {
    if (gameState == DIED) {
        resetLevel();
        gameState = PLAYING;
        return;
    }

    keyStates[key] = true;

    if (key == 'r' || key == 'R') {
        resetLevel();
        return;
    }

    if (key == ' ' || key == 'w' || key == 'W') {
        handleJump();
    }

    if (key == 27) exit(0);
}

void onKeyReleased(unsigned char key, int x, int y) {
    keyStates[key] = false;

    if ((key == ' ' || key == 'w' || key == 'W') && player.velY > 0.0f) {
        player.velY *= JUMP_CUT_MULTIPLIER;
    }
}

void onSpecialKeyPressed(int key, int x, int y) {
    if (gameState == DIED) {
        resetLevel();
        gameState = PLAYING;
        return;
    }

    specialKeyStates[key] = true;

    if (key == GLUT_KEY_UP) {
        handleJump();
    }
}

void onSpecialKeyReleased(int key, int x, int y) {
    specialKeyStates[key] = false;

    if (key == GLUT_KEY_UP && player.velY > 0.0f) {
        player.velY *= JUMP_CUT_MULTIPLIER;
    }
}

#endif
