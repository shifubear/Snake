//
//  Head.cpp
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Head_P1.h"
using namespace std;

//Initialize variables
Head_P1::Head_P1() {
    mPosX = -1;
    mPosY = -1;
    
    headDirection = HEAD_DIRECTION_NONE;
}

//Set head position
void Head_P1::setPos(int x, int y) {
    mPosX = x;
    mPosY = y;
}


//Handle key press events, Returns true if moved
bool Head_P1::handleEvent(SDL_Event &e) {
    //If presses keyboard
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Change the head direction
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                if (headDirection != HEAD_DIRECTION_DOWN) {
                    headDirection = HEAD_DIRECTION_UP;
                    return true;
                }
                break;
                
            case SDLK_DOWN:
                if (headDirection != HEAD_DIRECTION_UP) {
                    headDirection = HEAD_DIRECTION_DOWN;
                    return true;
                }
                break;
                
            case SDLK_LEFT:
                if (headDirection != HEAD_DIRECTION_RIGHT) {
                    headDirection = HEAD_DIRECTION_LEFT;
                    return true;
                }
                break;
                
            case SDLK_RIGHT:
                if (headDirection != HEAD_DIRECTION_LEFT) {
                    headDirection = HEAD_DIRECTION_RIGHT;
                    return true;
                }
                break;
        }
    }
    return false;
}

//Move head position
void Head_P1::move() {
    //Move the head position based on the direction
    switch (headDirection) {
        case HEAD_DIRECTION_NONE:
            //Do nothing
            break;
            
        case HEAD_DIRECTION_UP:
            mPosY -= HEAD_MOVE_VALUE;
            break;
            
        case HEAD_DIRECTION_DOWN:
            mPosY += HEAD_MOVE_VALUE;
            break;
            
        case HEAD_DIRECTION_LEFT:
            mPosX -= HEAD_MOVE_VALUE;
            break;
            
        case HEAD_DIRECTION_RIGHT:
            mPosX += HEAD_MOVE_VALUE;
            break;
    }
}

void Head_P1::render(LTexture &headTexture, SDL_Renderer* renderer) {
    headTexture.render(renderer, mPosX, mPosY);
}

const int Head_P1::getHeadWidth() {
    return HEAD_WIDTH;
}
const int Head_P1::getHeadHeight() {
    return HEAD_HEIGHT;
}

//Get positions
int Head_P1::getPosX() {
    return mPosX;
}
int Head_P1::getPosY() {
    return mPosY;
}

void Head_P1::resetDirection() {
    headDirection = HEAD_DIRECTION_NONE;
}












