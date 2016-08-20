//
//  Fruit.h
//  
//
//  Created by Shion Fukuzawa on 11/8/15.
//
//

#ifndef ____Fruit__
#define ____Fruit__

#include <stdio.h>

//Fruit class
class Fruit {
public:
    //Dimensions
    static const int FRUIT_WIDTH = 20;
    static const int FRUIT_HEIGHT = 20;
    
    //Initialize variables
    Fruit();
    
    //Render
    void render(LTexture& texture, SDL_Renderer* renderer, int x, int y);
    
    //Get positions
    int getPosX();
    int getPosY();
    
private:
    //Position
    int mPosX;
    int mPosY;
};

#endif /* defined(____Fruit__) */
