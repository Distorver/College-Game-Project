#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include "../core/GameManager.h"
#include "PlayerAnimator.h"

extern int currentFPS;

void renderLevel() {
    glColor4f(0.07, 0.10, 0.15, 1.0);
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
    renderPlayerSprite(player);
}

void renderSpikes() {
    glColor4f(0.83, 0.85, 0.85, 1.0);
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

float getTextWidth(const char *text, void *font) {
    float width = 0.0f;
    for (const char *c = text; *c != '\0'; c++) {
        width += glutBitmapWidth(font, *c);
    }
    return width;
}

void renderText(const char *text, float x, float y, void *font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char *c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void renderCenteredText(const char *text, float y, void *font = GLUT_BITMAP_HELVETICA_18) {
    float width = getTextWidth(text, font);
    renderText(text, 960.0f - width * 0.5f, y, font);
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

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 30.0f);

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
    // renderPlayer();
    
    // Render FPS counter
    renderFPS();

    if (gameState == DIED) {
        renderPlayer();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 1920, 1080, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(1.0f, 0.2f, 0.2f);
        renderCenteredText("YOU DIED! PRESS ANY KEY TO START", 520.0f, GLUT_BITMAP_HELVETICA_18);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } else if(gameState == WON){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 1920, 1080, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(0.2f, 1.0f, 0.2f);
        renderCenteredText("Congrats! YOU HAVE FINISHED THE GAME\n PRESS ESC TO EXIT", 520.0f, GLUT_BITMAP_HELVETICA_18);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } else {renderPlayer();}
    
    glutSwapBuffers();
}

#endif