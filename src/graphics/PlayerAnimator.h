#ifndef PLAYER_ANIMATOR_H
#define PLAYER_ANIMATOR_H

#include "SpriteSheet.h"
#include "../common/Structs.h"
#include "../core/GameManager.h"

// Animation states
enum AnimState { ANIM_IDLE, ANIM_FROM_IDLE, ANIM_WALK, ANIM_JUMP, ANIM_DEAD };

SpriteSheet sprIdle;       // 6 cols, 1 row
SpriteSheet sprFromIdle;   // 2 cols, 1 row
SpriteSheet sprWalk;       // 4 cols, 6 rows
SpriteSheet sprJump;
SpriteSheet sprDeath;      // 1 col, 1 row

AnimState animState    = ANIM_IDLE;
float     animTimer    = 0.0f;
int       animFrame    = 0;
bool      facingRight  = true;

// Frame durations (seconds)
const float IDLE_FPS      = 4.0f;
const float FROM_IDLE_FPS = 10.0f;
const float WALK_FPS      = 6.0f;
const float JUMP_FPS      = 2.0f;
const float DEATH_FPS     = 12.0f;

void initSprites() {
    sprIdle     = loadSprite("assets/Character/Idle.png",      4, 1);
    sprWalk     = loadSprite("assets/Character/Run.png",      6, 1);
    sprJump     = loadSprite("assets/Character/Jump.png",    8, 1);
    sprDeath    = loadSprite("assets/Character/death.png",    8, 1);
}

void updateAnimation(const Player& p, float dx, float dt) {
    // Determine facing direction
    if (dx > 0) facingRight = true;
    else if (dx < 0) facingRight = false;

    // Determine state
    AnimState newState;
    if (gameState == DIED) {
        newState = ANIM_DEAD;
    } else if (dx != 0.0f) {
        newState = ANIM_WALK;
    } else if (player.velY > 0) {
        newState = ANIM_JUMP;
    } else {
        newState = ANIM_IDLE;
    }

    // Reset frame on state change
    if (newState != animState) {
        animState = newState;
        animFrame = 0;
        animTimer = 0.0f;
    }

    // Advance frame
    float fps = (animState == ANIM_WALK)      ? WALK_FPS
              : (animState == ANIM_FROM_IDLE) ? FROM_IDLE_FPS
              : (animState == ANIM_JUMP)      ? JUMP_FPS
              : (animState == ANIM_DEAD)      ? DEATH_FPS
              :                                  IDLE_FPS;

    animTimer += dt;
    if (animTimer >= 1.0f / fps) {
        animTimer = 0.0f;

        int totalFrames = (animState == ANIM_WALK)      ? 6 // 4*6
                        : (animState == ANIM_FROM_IDLE) ? 4
                        : (animState == ANIM_JUMP)      ? 8
                        : (animState == ANIM_DEAD)      ? 8
                        :                                 6;

        if (animState == ANIM_DEAD) {
            if (animFrame < totalFrames - 1) {
                animFrame++;
            }
        } else {
            animFrame++;
            if (animState == ANIM_FROM_IDLE && animFrame >= totalFrames) {
                // Snap to idle after transition completes
                animState = ANIM_IDLE;
                animFrame = 0;
            } else {
                animFrame %= totalFrames;
            }
        }
    }
}

void renderPlayerSprite(const Player& p) {
    int col, row;
    const SpriteSheet* sheet;

    if (animState == ANIM_WALK) {
        sheet = &sprWalk;
        col   = animFrame % 4;
        row   = animFrame / 4;
    } else if (animState == ANIM_JUMP) {
        sheet = &sprJump;
        col   = animFrame % 4;
        row   = animFrame / 4;
    } else if (animState == ANIM_DEAD) {
        sheet = &sprDeath;
        col   = animFrame;
        row   = 0;
    } else {
        sheet = &sprIdle;
        col   = animFrame;
        row   = 0;
    }

    // Draw slightly larger than the hitbox so the sprite looks good
    float sprW = p.width  * 2.5f;
    float sprH = p.height * 2.5f;
    float offX = (sprW - p.width)  / 2.0f;
    float offY = 0.0f; // anchor to feet

    drawFrame(*sheet, col, row,
              p.x - offX, p.y - offY,
              sprW, sprH,
              !facingRight); // flip when moving left
}

#endif