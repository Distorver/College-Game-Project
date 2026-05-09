#ifndef KEYSTATES_H
#define KEYSTATES_H

#include <GL/glut.h>
#include "Globals.h"

bool keyStates[256]; 
bool specialKeyStates[256]; 

void initKeys() {
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
        specialKeyStates[i] = false;
    }
}

void keyPressed(unsigned char key, int x, int y) {
    // if (currentState == DIED){
    //     resetLevel();
    //     currentState = PLAYING;
    //     return;
    // }

    keyStates[key] = true;

    // JUMP LOGIC
    if (key == ' ' || key == 'w' || key == 'W') {
        if (square.isGrounded || square.jumpCount < 2) {
            square.velY = JUMP_FORCE;
            square.isGrounded = false;
            square.jumpCount++;
        }
    }

    if (key == 27) exit(0); 
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;

    // Jump cut
    if ((key == ' ' || key == 'w' || key == 'W') && square.velY > 0.0f) {
        square.velY *= JUMP_CUT_MULTIPLIER;
    }
}

void specialKeyPressed(int key, int x, int y) {
    specialKeyStates[key] = true;

    if (key == GLUT_KEY_UP) {
        if (square.isGrounded || square.jumpCount < 2) {
            square.velY = JUMP_FORCE;
            square.isGrounded = false;
            square.jumpCount++;
        }
    }
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;

    if (key == GLUT_KEY_UP && square.velY > 0.0f) {
        square.velY *= JUMP_CUT_MULTIPLIER;
    }
}

#endif