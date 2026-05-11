#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../common/Structs.h"
#include "../common/Constants.h"
#include "../core/GameManager.h"
#include "../physics/PhysicsEngine.h"

// Level 1 trap logic: moving platforms that shrink
void updateTrapPlatformsLevel1() {
    float cropSpeed = 100 * deltaTime;
    for (int i = 0; i < NUM_PLATFORMS_L1; i++) {
        Platform &p = level1_platforms[i];
        if (p.isTrap && (player.x + player.width > p.triggerX || p.trigger)) {
            p.trigger = true;
            if (p.width > 0) {
                p.x += cropSpeed;
                p.width -= cropSpeed;
            }
            if (p.width < 0) {
                p.width = 0;
            }
        }
    }
}

// Level 2 trap logic: moving platform with complex path
void updateTrapPlatformsLevel2() {
    float moveSpeed = 40 * deltaTime;
    Platform &p = level2_platforms[2];
    float oldX = p.x;
    float oldY = p.y;

    if (p.isTrap && (player.x + player.width > p.triggerX || p.trigger)) {
        p.trigger = true;
        if (p.y < 45 && p.x >= 100) {
            p.y += moveSpeed;
            if (p.y > 45) p.y = 45;
        } else if (p.y >= 45 && p.x > 85) {
            p.x -= moveSpeed;
            if (p.x < 85) p.x = 85;
        } else if (p.x <= 85 && p.y > 30) {
            p.y -= moveSpeed;
            if (p.y < 30) p.y = 30;
        }
    }

    float dx = p.x - oldX;
    float dy = p.y - oldY;

    // Push player along with platform movement
    if (dx != 0.0f && player.y + player.height > p.y - p.height && player.y < p.y) {
        if (player.x + player.width > p.x && player.x < p.x + p.width) {
            player.x += dx;
        }
    }

    if (dy != 0.0f && player.x + player.width > p.x && player.x < p.x + p.width) {
        if (player.y + player.height > p.y - p.height && player.y < p.y) {
            player.y += dy;
        }
    }
}

// Level 3 trap logic: momentum-based platforms
void updateTrapPlatformsLevel3() {
    for(auto &p : level3_platforms) {
        // 1. Skip this entire loop if it's not a trap
        if(!p.isTrap) {
            continue; 
        }

        float dx = 0;

        // 2. Check if the player crossed the trigger line
        // (Changed to '>' so it triggers when the player gets close)
        if(!p.trigger && (player.x + player.width < p.triggerX)) {
            p.trigger = true; // The trap is sprung!
        }

        // 3. Set the speed based on whether it is triggered or not
        if(p.trigger) {
            dx = 15.0f * deltaTime;  // Move Right after triggering
        } else {
            dx = -15.0f * deltaTime; // Move Left before triggering
        }

        // 4. Move the platform
        p.x += dx;

        // 5. Move the player ONLY if they are standing on THIS platform
        // We check if they are grounded AND within the left/right edges of this platform
        if(player.isGrounded) {
            bool isOverlappingX = (player.x + player.width > p.x) && (player.x < p.x + p.width);
            
            // Note: If you have platforms at different heights, you should also check 
            // if the player's Y position matches this platform's Y position here!
            if(isOverlappingX) {
                player.x += dx;
            }
        }
    }
}

void updateTrapPlatforms() {
    if (currentLevel == 1) {
        updateTrapPlatformsLevel1();
    } else if (currentLevel == 2) {
        updateTrapPlatformsLevel2();
    } else if (currentLevel == 3) {
        updateTrapPlatformsLevel3();
    }

    // Falling death
    if (player.y < -15) gameState = DIED;
}

// Spike logic (Level 1 only)
void updateSpikes() {
    if (currentLevel != 1) return;

    float hideSpeed = 40 * deltaTime;
    for (int i = 0; i < NUM_SPIKES_L1; i++) {
        Spike &s = level1_spikes[i];
        if (player.x + player.width > s.triggerX) {
            if (s.x >= 73 && s.x <= 81) {
                s.isHidden = true;
                s.y -= hideSpeed;
            } else {
                s.isHidden = false;
                s.y += hideSpeed;
            }
        } else {
            if (s.x >= 73 && s.x <= 81) {
                s.isHidden = false;
            } else {
                s.isHidden = true;
            }
        }

        if (s.y >= 30) s.y = 30;
        else if (s.y <= 25) s.y = 25;

        // Spike collision
        if (!s.isHidden) {
            if (player.x + player.width > s.x && player.x < s.x + s.width &&
                player.y + player.height > s.y && player.y < s.y + s.height) {
                gameState = DIED;
            }
        }
    }
}

void checkGoalReached() {
    if (player.x + player.width > goal.x && player.x < goal.x + goal.width &&
        player.y + player.height > goal.y && player.y < goal.y + goal.height) {
        loadNextLevel();
    }
}

#endif
