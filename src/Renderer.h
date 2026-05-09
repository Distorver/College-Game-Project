#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glut.h>
#include "Globals.h"


// level rendering function
void drawLevel() {
    glColor4f(0.34, 0.25, 0.33, 1.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < numPlatforms; i++) {
        glVertex2f(levels[i].x, levels[i].y - levels[i].height);
        glVertex2f(levels[i].x + levels[i].width, levels[i].y - levels[i].height);
        glVertex2f(levels[i].x + levels[i].width, levels[i].y);
        glVertex2f(levels[i].x, levels[i].y);
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
        for(int i = 0; i < numSpikes; i++){
            glVertex2f(spikes[i].x , spikes[i].y);
            glVertex2f(spikes[i].x + spikes[i].width , spikes[i].y);
            glVertex2f(spikes[i].x + spikes[i].width / 2 , spikes[i].y + spikes[i].height);
        }
    glEnd();
}

#endif