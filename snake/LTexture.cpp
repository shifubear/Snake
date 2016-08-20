//
//  LTexture.cpp
//  
//
//  Created by Shion Fukuzawa on 11/7/15.
//
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
using namespace std;

//Initialize variables
LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

//Deallocate memory
LTexture::~LTexture() {
    free();
}

//Load image to the texture and find dimensions
bool LTexture::loadFromFile(string path, SDL_Renderer* renderer) {
    //Free preexisting texture
    free();
    
    //Load image to surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Could not load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Set color key
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (mTexture == NULL) {
            printf("Could not create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Free old surface
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
    
    return mTexture != NULL;
}

//Load rendered text as texture
bool LTexture::loadRenderedText(TTF_Font* font, string textureText, SDL_Color textColor, SDL_Renderer* renderer) {
    //Free preexisting texture
    free();
    
    //Load text to surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Could not load _%s_ to surface! SDL_ttf Error: %s\n", textureText.c_str(), TTF_GetError());
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == NULL) {
            printf("Could not load _%s_ to surface! SDL_ttf Error: %s\n", textureText.c_str(), TTF_GetError());
        } else {
            //Get texture dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Free old surface
        SDL_FreeSurface(textSurface);
        textSurface = NULL;
    }
    
    return mTexture != NULL;
}

//Free the texture
void LTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

//Set color modulation
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

//Set blend mode
void LTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

//Set alpha modulation
void LTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

//Render image at position
void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    //Set rendering space
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Clip if needed
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render!!
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

//Get image dimensions
int LTexture::getWidth() {
    return mWidth;
}
int LTexture::getHeight() {
    return mHeight;
}











































