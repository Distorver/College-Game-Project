#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glut.h>
#include "Globals.h"


// level rendering function
void drawLevel() {
    glColor4f(0.34, 0.25, 0.33, 1.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < currentNumPlatforms; i++) {
        glVertex2f(currentPlatforms[i].x, currentPlatforms[i].y - currentPlatforms[i].height);
        glVertex2f(currentPlatforms[i].x + currentPlatforms[i].width, currentPlatforms[i].y - currentPlatforms[i].height);
        glVertex2f(currentPlatforms[i].x + currentPlatforms[i].width, currentPlatforms[i].y);
        glVertex2f(currentPlatforms[i].x, currentPlatforms[i].y);
    }
    glEnd();
}

// player rendering function
void drawPlayer() {
    glColor4f(0.99, 0.74, 0.40, 1.0);
        glBegin(GL_QUADS);
            glVertex2f(square.x, square.y);
            glVertex2f(square.x + square.width, square.y);
            glVertex2f(square.x + square.width, square.y + square.height);
            glVertex2f(square.x, square.y + square.height);
        glEnd();
}

// Spikes rendering function
void drawSpikes() {
    glColor4f(0.98, 0.49, 0.31, 1.0);
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < currentNumSpikes; i++){
            glVertex2f(currentSpikes[i].x , currentSpikes[i].y);
            glVertex2f(currentSpikes[i].x + currentSpikes[i].width , currentSpikes[i].y);
            glVertex2f(currentSpikes[i].x + currentSpikes[i].width / 2 , currentSpikes[i].y + currentSpikes[i].height);
        }
    glEnd();
}

void drawGoal() {
    glColor4f(0.99, 0.74, 0.40, 1.0);
        glBegin(GL_QUADS);
            glVertex2f(currentGoal.x, currentGoal.y);
            glVertex2f(currentGoal.x + currentGoal.width, currentGoal.y);
            glVertex2f(currentGoal.x + currentGoal.width, currentGoal.y + currentGoal.height);
            glVertex2f(currentGoal.x, currentGoal.y + currentGoal.height);
        glEnd();
}

#endif