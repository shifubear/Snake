//
//  Tail_P1.cpp
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Tail.h"
using namespace std;

Tail::Tail() {
    mPosX = -98;
    mPosY = -98;
}

void Tail::render(LTexture& texture, SDL_Renderer* renderer, int x, int y) {
    texture.render(renderer, x, y);
}

//Get positions
int Tail::getPosX() {
    return mPosX;
}
int Tail::getPosY() {
    return mPosY;
}
