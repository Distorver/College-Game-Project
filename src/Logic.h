#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>

#include "Globals.h"
#include "Physics.h"

void trapPlat(){
    float cropSpeed = 80 * deltaTime ;
    for (auto &p : levels){
        if(p.isTrap && square.x + square.width> p.triggerX){
            if(p.width > 0){
                p.x += cropSpeed;    
                p.width -= cropSpeed;  
            }
            if (p.width < 0) {
                p.width = 0;
            }
        }
    }

    if(square.y < -15) currentState = DIED;
}

void trapSpikes() {
    float hideSpeed = 40 * deltaTime;
    for(auto &s: spikes){
        if (square.x > s.triggerX) {
            if (s.x >= 71 && s.x <= 79) {
                s.isHidden = true;
                s.y -= hideSpeed;
            } else {
                s.isHidden = false;
                s.y += hideSpeed;
            }
        } else {
            if (s.x >= 71 && s.x <= 79) {
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

#endif