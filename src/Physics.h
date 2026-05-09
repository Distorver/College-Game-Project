#ifndef PHYSICS_H
#define PHYSICS_H

#include <GL/glut.h>
#include "Globals.h"
#include "KeyStates.h"

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;



void calculateDeltaTime() {
    float currentFrameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void updatePhysics() {
    calculateDeltaTime();
    
    // Horizontal Movement
    if (keyStates['a'] || keyStates['A'] || specialKeyStates[GLUT_KEY_LEFT]) {
        square.x -= square.velX * deltaTime;
    }
    if (keyStates['d'] || keyStates['D'] || specialKeyStates[GLUT_KEY_RIGHT]) {
        square.x += square.velX * deltaTime;
    }

    if (!square.isGrounded) {
        square.velY += GRAVITY * deltaTime;
    }

    square.y += square.velY * deltaTime;
    square.isGrounded = false;

    for (int i = 0; i < numPlatforms; i++) {
        Platform p = levels[i];
        
        if (square.x + square.width > p.x && square.x < p.x + p.width) {
            if (square.velY <= 0.0f && square.y <= p.y && square.y + 3.0f > p.y) { 
                square.y = p.y;
                square.velY = 0.0f;
                square.isGrounded = true;
                square.jumpCount = 0; // RESET jump count when touching floor
            }
        }
    }

    glutPostRedisplay();
}

#endif