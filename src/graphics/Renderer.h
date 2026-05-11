#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include "../core/GameManager.h"

extern int currentFPS;

void renderLevel() {
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

void renderPlayer() {
    glColor4f(0.99, 0.74, 0.40, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + player.width, player.y);
    glVertex2f(player.x + player.width, player.y + player.height);
    glVertex2f(player.x, player.y + player.height);
    glEnd();
}

void renderSpikes() {
    glColor4f(0.98, 0.49, 0.31, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < currentNumSpikes; i++) {
        glVertex2f(currentSpikes[i].x, currentSpikes[i].y);
        glVertex2f(currentSpikes[i].x + currentSpikes[i].width, currentSpikes[i].y);
        glVertex2f(currentSpikes[i].x + currentSpikes[i].width / 2, currentSpikes[i].y + currentSpikes[i].height);
    }
    glEnd();
}

void renderGoal() {
    glColor4f(0.99, 0.74, 0.40, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(goal.x, goal.y);
    glVertex2f(goal.x + goal.width, goal.y);
    glVertex2f(goal.x + goal.width, goal.y + goal.height);
    glVertex2f(goal.x, goal.y + goal.height);
    glEnd();
}

void renderFPS() {
    // Save current matrix mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1920, 1080, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render FPS text
    char fpsText[32];
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", currentFPS);

    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glRasterPos2f(10.0f, 30.0f);    // Top-left position

    for (const char *c = fpsText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // Restore matrix
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    renderSpikes();
    renderLevel();
    renderGoal();
    if (gameState == PLAYING)
        renderPlayer();
    
    // Render FPS counter
    renderFPS();
    
    glutSwapBuffers();
}

#endif