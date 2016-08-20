//
//  Tail_P1.h
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#ifndef ____Tail_P1__
#define ____Tail_P1__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
using namespace std;

class Tail {
public:
    //Dimensions of the tail
    static const int TAIL_WIDTH = 20;
    static const int TAIL_HEIGHT = 20;
    
    //Initialize variables
    Tail();
    
    //Render
    void render(LTexture& texture, SDL_Renderer* renderer, int x, int y);
    
    //Get positions
    int getPosX();
    int getPosY();
    
private:
    //Position of tail
    int mPosX;
    int mPosY;
    
};

#endif /* defined(____Tail_P1__) */
