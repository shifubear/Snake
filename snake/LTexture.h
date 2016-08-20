//
//  LTexture.h
//  Texture wrapper class
//
//  Created by Shion Fukuzawa on 11/7/15.
//
//

#ifndef ____LTexture__
#define ____LTexture__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
using namespace std;

class LTexture {
public:
    //Initialize variables
    LTexture();
    //Deallocate memory
    ~LTexture();
    
    //Load image to the texture
    bool loadFromFile(string path, SDL_Renderer* renderer);
    
    //Load rendered text as texture
    bool loadRenderedText(TTF_Font* font, string textureText, SDL_Color textColor, SDL_Renderer* renderer);
    
    //Free the texture
    void free();
    
    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    
    //Set blend mode
    void setBlendMode(SDL_BlendMode blending);
    
    //Set alpha modulation
    void setAlpha(Uint8 alpha);
    
    //Render image at position
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    //Get image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The texture
    SDL_Texture* mTexture;
    //The texture's dimensions
    int mWidth;
    int mHeight;
};

#endif /* defined(____LTexture__) */
