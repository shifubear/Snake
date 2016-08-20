//
//  Fruit.cpp
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "LTexture.h"
#include "Fruit.h"

Fruit::Fruit() {
    mPosX = -100;
    mPosY = -100;
}

void Fruit::render(LTexture& texture, SDL_Renderer* renderer, int x, int y) {
    texture.render(renderer, x, y);
}

//Get positions
int Fruit::getPosX() {
    return mPosX;
}
int Fruit::getPosY() {
    return mPosY;
}
