#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>

#include "Globals.h"
#include "Physics.h"

void trapPlat_2(){
    float moveSpeed = 40 * deltaTime;
    Platform &p = level_2[2];
    float oldX = p.x;
    float oldY = p.y;

    if (p.isTrap && square.x + square.width > p.triggerX || p.trigger) {
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

    if (dx != 0.0f &&
        square.y + square.height > p.y - p.height &&
        square.y < p.y) {
        if (square.x + square.width > p.x && square.x < p.x + p.width) {
            square.x += dx;
        }
    }

    if (dy != 0.0f &&
        square.x + square.width > p.x &&
        square.x < p.x + p.width) {
        if (square.y + square.height > p.y - p.height && square.y < p.y) {
            square.y += dy;
        }
    }
}

void trapPlat(){
    if(currentLevel == 1){    
        float cropSpeed = 100 * deltaTime ;
        for (int i = 0; i < numPlatforms_1; i++) {
            Platform &p = level_1[i];
            if(p.isTrap && square.x + square.width > p.triggerX || p.trigger){
                p.trigger = true;
                if(p.width > 0){
                    p.x += cropSpeed;    
                    p.width -= cropSpeed;  
                }
                if (p.width < 0) {
                    p.width = 0;
                }
            }
        }
    } else if (currentLevel == 2) trapPlat_2();

    if(square.y < -15) currentState = DIED;
}

void trapSpikes() {
    if(currentLevel == 1) {    
        float hideSpeed = 40 * deltaTime;
        for (int i = 0; i < currentNumSpikes; i++) {
            Spikes &s = currentSpikes[i];
            if (square.x + square.width > s.triggerX) {
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

            if(s.y >= 30) s.y = 30;
            else if(s.y <= 25) s.y = 25;

            if (!s.isHidden) {
                if (square.x + square.width > s.x && 
                    square.x < s.x + s.width &&
                    square.y + square.height > s.y && 
                    square.y < s.y + s.height) {
                    currentState = DIED;
                }
            }
        }
    }
}

void checkGoal() {
    if (square.x + square.width > currentGoal.x &&
        square.x < currentGoal.x + currentGoal.width &&
        square.y + square.height > currentGoal.y &&
        square.y < currentGoal.y + currentGoal.height) {
        loadNextLevel();
    }
}

#endif