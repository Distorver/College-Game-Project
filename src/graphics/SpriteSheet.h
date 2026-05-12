#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct SpriteSheet {
    GLuint textureID = 0;
    int sheetW = 0, sheetH = 0;
    int frameW = 0, frameH = 0;
    int cols = 0, rows = 0;
};

SpriteSheet loadSprite(const char* path, int cols, int rows) {
    SpriteSheet s;
    s.cols = cols; s.rows = rows;
    int channels;
    unsigned char* data = stbi_load(path, &s.sheetW, &s.sheetH, &channels, 4);
    if (!data) return s;

    s.frameW = s.sheetW / cols;
    s.frameH = s.sheetH / rows;

    glGenTextures(1, &s.textureID);
    glBindTexture(GL_TEXTURE_2D, s.textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // pixel-perfect
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s.sheetW, s.sheetH, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return s;
}

void drawFrame(const SpriteSheet& s, int col, int row,
    float x, float y, float w, float h, bool flipX = false) {
    float u0 = (float)col / s.cols;
    float u1 = (float)(col + 1) / s.cols;
    float v0 = (float)row / s.rows;
    float v1 = (float)(row + 1) / s.rows;

    if (flipX) { float tmp = u0; u0 = u1; u1 = tmp; }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, s.textureID);
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(u0, v1); glVertex2f(x,     y);
        glTexCoord2f(u1, v1); glVertex2f(x + w, y);
        glTexCoord2f(u1, v0); glVertex2f(x + w, y + h);
        glTexCoord2f(u0, v0); glVertex2f(x,     y + h);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

#endif