//
//  Head_P2.h
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#ifndef ____Head_P2__
#define ____Head_P2__


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
using namespace std;

class Head_P2 {
public:
    //Head dimensions
    static const int HEAD_WIDTH = 20;
    static const int HEAD_HEIGHT = 20;
    
    //Head movement rate
    static const int HEAD_MOVE_VALUE = 20;
    
    //Initialize variables
    Head_P2();
    
    //Set head position
    void setPos(int x, int y);
    
    //Handle events
    bool handleEvent( SDL_Event& e );
    
    //Move head position
    void move();
    
    //Render
    void render(LTexture &headTexture, SDL_Renderer* renderer);
    
    //Get head dimensions
    const int getHeadWidth();
    const int getHeadHeight();
    
    //Get positions
    int getPosX();
    int getPosY();
    
    void resetDirection();
    
private:
    //Position coordinates
    int mPosX;
    int mPosY;
    
    //Direction enumeration
    enum HEADDIRECTION {
        HEAD_DIRECTION_NONE,
        HEAD_DIRECTION_UP,
        HEAD_DIRECTION_DOWN,
        HEAD_DIRECTION_LEFT,
        HEAD_DIRECTION_RIGHT
    };
    //Direction head is facing
    HEADDIRECTION headDirection;
    
};

#endif /* defined(____Head_P2__) */
