//
//  Head_P2.cpp
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
#include "Head_P2.h"
using namespace std;

//Initialize variables
Head_P2::Head_P2() {
    mPosX = -10;
    mPosY = -1;
    
    headDirection = HEAD_DIRECTION_NONE;
}

//Set head position
void Head_P2::setPos(int x, int y) {
    mPosX = x;
    mPosY = y;
}

//Handle key press events
bool Head_P2::handleEvent(SDL_Event &e) {
    //If presses keyboard
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Change the head direction
        switch (e.key.keysym.sym) {
                //Face up
            case SDLK_w:
                if (headDirection != HEAD_DIRECTION_DOWN) {
                    headDirection = HEAD_DIRECTION_UP;
                    return true;
                }
                break;
                
                //Face down
            case SDLK_s:
                if (headDirection != HEAD_DIRECTION_UP) {
                    headDirection = HEAD_DIRECTION_DOWN;
                    return true;
                }
                break;
                
                //Face left
            case SDLK_a:
                if (headDirection != HEAD_DIRECTION_RIGHT) {
                    headDirection = HEAD_DIRECTION_LEFT;
                    return true;
                }
                break;
                
                //Face right
            case SDLK_d:
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
void Head_P2::move() {
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

void Head_P2::render(LTexture &headTexture, SDL_Renderer* renderer) {
    headTexture.render(renderer, mPosX, mPosY);
}

const int Head_P2::getHeadWidth() {
    return HEAD_WIDTH;
}
const int Head_P2::getHeadHeight() {
    return HEAD_HEIGHT;
}

//Get positions
int Head_P2::getPosX() {
    return mPosX;
}
int Head_P2::getPosY() {
    return mPosY;
}

void Head_P2::resetDirection() {
    headDirection = HEAD_DIRECTION_NONE;
}

