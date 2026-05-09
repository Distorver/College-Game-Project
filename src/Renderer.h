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

#endif