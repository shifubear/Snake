//
//  main.cpp
//  snake
//
//  Created by Shion Fukuzawa on 11/7/15.
//  Copyright (c) 2015 Shion Fukuzawa. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <cstdlib> // Random
#include <time.h> // Time
#include <string>
#include "LTexture.h"
#include "Head_P1.h"
#include "Head_P2.h"
#include "Tail.h"
#include "Fruit.h"
using namespace std;

//Window size constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
//Tile size constants
const int TILE_SIZE = 20;

//Game mode enumeration
enum gameMode {
    GAME_NOT_STARTED,
    GAME_MODE_SINGLE_PLAY,
    GAME_MODE_PVP,
    GAME_MODE_ADVENTURE
};

//Basic functions
//  Initializes SDL and creates window
bool init();
//  Loads media
bool loadMedia();
//  Loads media that needs final data
bool loadFinalMedia(int finalLength);
//  Frees media, destroys window, and quits SDL
void close();
//  Checks if position is in screen
bool P1IsNotInBox(Head_P1 head);
void CheckP1HitWall();
void CheckP2HitWall();
//  Title screen loop
void titleScreen(SDL_Event e, bool& quit, gameMode& gameMode);
//  Game loop
void gameLoop();
//  Results screen loop
void results();

//Variables
//  Window
SDL_Window* gWindow = NULL;
//  Renderer
SDL_Renderer* gRenderer = NULL;
//  Fonts
TTF_Font* gAbductionFontTitle = NULL;
TTF_Font* gMenuFont = NULL;
TTF_Font* gFinalFont = NULL;
//  Textures
//    Title texture
LTexture gTitleTexture;
//    Menu textures
LTexture gMenuSoloTexture;
LTexture gMenuPvPTexture;
LTexture gMenuAdventureTexture;
//    Game over textures
LTexture gGameOverTexture;
LTexture gFinalScoreTexture;
LTexture gPlayer1WinTexture;
LTexture gPlayer2WinTexture;
//    Head textures
LTexture gHeadTexture;
LTexture gHeadTexture2;
//    Tail textures
LTexture gTailTexture;
LTexture gTailTexture2;
//    Fruit texture
LTexture gFruitTexture;
//  Objects
//    Player 1
//      Head
Head_P1 head_p1;
//      Tail
Tail    tail_p1;
//    Player 2
//      Head
Head_P2 head_p2;
//      Tail
Tail    tail_p2;
//    Fruit
Fruit gFruitObject;

int main() {
    //Initialize
    if (!init()) {
        printf("Could not initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Could not load media!\n");
        } else {
            //Game loop flag
            bool quit = false;
            
            //Game over flag
            bool dead = false;
            bool p2dead = false;
            
            //Event handler
            SDL_Event e;
            
            //Game start flag
            gameMode gameMode = GAME_NOT_STARTED;
            
            //Max tail length
            int maxTailLen = 1000;
            
            //Current tail length
            int currentTailLen1 = 0;
            int currentTailLen2 = 0;
            
            //Initial fruit position
            int fruitX = (rand() % (WINDOW_WIDTH / TILE_SIZE)) * TILE_SIZE;
            int fruitY = (rand() % (WINDOW_HEIGHT / TILE_SIZE)) * TILE_SIZE;
            
            //Last head x positions
            int lastHeadPosX[ maxTailLen ];
            //Last head y positions
            int lastHeadPosY[ maxTailLen ];
            
            //Last head x positions (P2)
            int lastHeadPosX2[ maxTailLen ];
            //Last head y positions (P2)
            int lastHeadPosY2[ maxTailLen ];
            
            //Current frame
            int frame = 0;
            
            bool moved = false;
            
            //Start game
            while (!quit) {
                
                //Title screen
                while (gameMode == GAME_NOT_STARTED && !quit) {
                    titleScreen(e, quit, gameMode);
                }
                
                //Position heads
                if (gameMode == GAME_MODE_SINGLE_PLAY) {
                    head_p1.setPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );
                } else if (gameMode == GAME_MODE_PVP) {
                    head_p1.setPos( 3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
                    head_p2.setPos( WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
                }
                
                //Initialize head direction
                head_p1.resetDirection();
                head_p2.resetDirection();
                
                //Initialize tail number
                for (int a = 0; a < maxTailLen; a++) {
                    lastHeadPosX[a] = -1;
                    lastHeadPosY[a] = -1;
                    lastHeadPosX2[a] = -1;
                    lastHeadPosY2[a] = -1;
                }
                currentTailLen1 = 0;
                currentTailLen2 = 0;
                
                //Game loop
                while (!dead && !p2dead && !quit) {
                
                    //Check polled events
                    while (SDL_PollEvent(&e) != 0 && !moved) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    
                        if (head_p1.handleEvent(e)) {
                            moved = true;
                        }
                        if (gameMode == GAME_MODE_PVP) {
                            if (head_p2.handleEvent(e)) {
                                moved = true;
                            }
                        }
                    }
                
                    //Fruit eat event (Player 1)
                    if (head_p1.getPosX() == fruitX && head_p1.getPosY() == fruitY) {
                        //Grow
                        currentTailLen1 = currentTailLen1 + 1;
                        //Spawn new fruit
                        fruitX = (rand() % (WINDOW_WIDTH / TILE_SIZE)) * TILE_SIZE;
                        fruitY = (rand() % (WINDOW_HEIGHT / TILE_SIZE)) * TILE_SIZE;
                    }
                    //Fruit eat event (Player 2)
                    else if (gameMode == GAME_MODE_PVP && head_p2.getPosX() == fruitX && head_p2.getPosY() == fruitY) {
                        //Grow
                        currentTailLen2 = currentTailLen2 + 1;
                        //Spawn new fruit
                        fruitX = (rand() % (WINDOW_WIDTH / TILE_SIZE)) * TILE_SIZE;
                        fruitY = (rand() % (WINDOW_HEIGHT / TILE_SIZE)) * TILE_SIZE;
                    }
                
                    //Every 5 frames
                    if (frame % 8 == 0) {
                    
                        //Set new positions
                        // P1
                        //   tail
                        if (currentTailLen1 > 1) {
                            for (int j = currentTailLen1; j > 0; j--) {
                                lastHeadPosX[j - 1] = lastHeadPosX[j - 2];
                                lastHeadPosY[j - 1] = lastHeadPosY[j - 2];
                            }
                        }
                        lastHeadPosX[0] = head_p1.getPosX();
                        lastHeadPosY[0] = head_p1.getPosY();
                        //Move Player 1 head
                        head_p1.move();

                        // P2
                        //   tail
                        if (gameMode == GAME_MODE_PVP && currentTailLen2 > 1) {
                            for (int j = currentTailLen2; j > 0; j--) {
                                lastHeadPosX2[j - 1] = lastHeadPosX2[j - 2];
                                lastHeadPosY2[j - 1] = lastHeadPosY2[j - 2];
                            }
                        }
                        lastHeadPosX2[0] = head_p2.getPosX();
                        lastHeadPosY2[0] = head_p2.getPosY();
                        //Move Player 2 head
                        head_p2.move();

                        //Death event
                        //  In single play (out or eat self)
                        if (gameMode == GAME_MODE_SINGLE_PLAY) {
                            //Hits wall
                            if (P1IsNotInBox(head_p1)) {
                                dead = true;
                            }
                        
                            //Eats self
                            for (int k = currentTailLen1; k > 0; k--) {
                                if (head_p1.getPosX() == lastHeadPosX[k - 1] && head_p1.getPosY() == lastHeadPosY[k - 1]) {
                                    dead = true;
                                }
                            }
                        }
                        //  In battle (hit enemy)
                        if (gameMode == GAME_MODE_PVP) {
                            //Hits wall and warps to other end P1
                            CheckP1HitWall();
                            //Hits wall and warps to other end P2
                            CheckP2HitWall();
                        
                            //Hits enemy
                            for (int k = currentTailLen2; k > 0; k--) {
                                if (head_p1.getPosX() == lastHeadPosX2[k - 1] && head_p1.getPosY() == lastHeadPosY2[k - 1]) {
                                    dead = true;
                                }
                            }
                            for (int k = currentTailLen1; k > 0; k--) {
                                if (head_p2.getPosX() == lastHeadPosX[k - 1] && head_p2.getPosY() == lastHeadPosY[k - 1]) {
                                    p2dead = true;
                                }
                            }
                        }
                    }
                
                    //Clear screen
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                
                    //Render fruit
                    gFruitObject.render(gFruitTexture, gRenderer, fruitX, fruitY);
                
                    //Render tails
                    for (int i = currentTailLen1; i > 0; i--) {
                        tail_p1.render(gTailTexture, gRenderer, lastHeadPosX[i - 1], lastHeadPosY[i - 1]);
                    }
                    for (int i = currentTailLen2; i > 0; i--) {
                        tail_p2.render(gTailTexture2, gRenderer, lastHeadPosX2[i - 1], lastHeadPosY2[i - 1]);
                    }
                
                    //Render head
                    head_p1.render(gHeadTexture, gRenderer);
                    if (gameMode == GAME_MODE_PVP) {
                        head_p2.render(gHeadTexture2, gRenderer);
                    }
                
                    //Update screen
                    SDL_RenderPresent(gRenderer);
                
                    moved = false;
                    frame++;
                
                }
            
                if (!loadFinalMedia(currentTailLen1)) {
                    printf("Could not load final media!\n");
                }
                else {
                //Game over screen (Single player)
                    if (gameMode == GAME_MODE_SINGLE_PLAY) {
                        if (dead && !quit) {
                            //Clear screen
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                    
                            //Render text
                            gGameOverTexture.render(gRenderer, (WINDOW_WIDTH - gGameOverTexture.getWidth()) / 2, 50);
                            gFinalScoreTexture.render(gRenderer, (WINDOW_WIDTH - gFinalScoreTexture.getWidth()) / 2, 150);
                        
                            //Update screen
                            SDL_RenderPresent(gRenderer);
                            
                            bool input = false;
                            while (!input) {
                                while (SDL_PollEvent(&e) != 0) {
                                    if (e.type == SDL_QUIT) {
                                        quit = true;
                                        input = true;
                                    } else if (e.type == SDL_KEYDOWN) {
                                        if (e.key.keysym.sym == SDLK_RETURN) {
                                            gameMode = GAME_NOT_STARTED;
                                            dead = false;
                                            p2dead = false;
                                            input = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //Game over screen (Battle)
                    else if (gameMode == GAME_MODE_PVP) {
                        if ((dead || p2dead) && !quit) {
                            //Clear screen
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                    
                            //Render text
                            gGameOverTexture.render(gRenderer, (WINDOW_WIDTH - gGameOverTexture.getWidth()) / 2, 50);
                            if (dead) {
                                gPlayer2WinTexture.render(gRenderer, (WINDOW_WIDTH - gPlayer2WinTexture.getWidth()) / 2, 150);
                            } else if (p2dead) {
                                gPlayer1WinTexture.render(gRenderer, (WINDOW_WIDTH - gPlayer1WinTexture.getWidth()) / 2, 150);
                            }
                        
                            //Update screen
                            SDL_RenderPresent(gRenderer);
                            
                            bool input = false;
                            while (!input) {
                                while (SDL_PollEvent(&e) != 0) {
                                    if (e.type == SDL_QUIT) {
                                        quit = true;
                                        input = true;
                                    } else if (e.type == SDL_KEYDOWN) {
                                        if (e.key.keysym.sym == SDLK_RETURN) {
                                            gameMode = GAME_NOT_STARTED;
                                            dead = false;
                                            p2dead = false;
                                            input = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    //Clean up
    close();
    
    return 0;
}


bool init() {
    //Initializer flag
    bool success = true;
    
    //Initialize time seed
    srand((int)time(NULL));
    
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        //Failed to load SDL
        printf("Could not initialize SDL! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!\n");
        }
        
        //Create window
        gWindow = SDL_CreateWindow("shifubear", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Could not create window! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Could not create renderer! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Set initial renderer draw color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("Could not initialize SDL_image! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                
                //Initialize TTF
                if (TTF_Init() == -1) {
                    printf("Could not initialize SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia() {
    //Load media flag
    bool success = true;
    
    //Open Title font
    gAbductionFontTitle = TTF_OpenFont("Abduction.ttf", 60);
    if (gAbductionFontTitle == NULL) {
        printf("Could not open title font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    } else {
        //Load rendered text
        //Title
        SDL_Color titleColor = { 0, 0, 0 };
        if ( !gTitleTexture.loadRenderedText(gAbductionFontTitle, "snake", titleColor, gRenderer)) {
            printf("Could not load title texture!\n");
            success = false;
        }
        
        //Game over
        if ( !gGameOverTexture.loadRenderedText(gAbductionFontTitle, "GAME OVER", titleColor, gRenderer)) {
            printf("Could not load game over texture!\n");
            success = false;
        }
    }
    
    //Open menu font
    gMenuFont = TTF_OpenFont("Abduction.ttf", 35);
    if (gMenuFont == NULL) {
        printf("Could not open menu font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    } else {
        //Load rendered text
        SDL_Color menuColor = { 0, 0, 0 };
        
        //Menu solo
        if ( !gMenuSoloTexture.loadRenderedText(gMenuFont, "1: Solo", menuColor, gRenderer)) {
            printf("Could not load menu solo texture!\n");
            success = false;
        }
        
        //Menu PVP
        if ( !gMenuPvPTexture.loadRenderedText(gMenuFont, "2: Battle", menuColor, gRenderer)) {
            printf("Could not load menu battle texture!\n");
            success = false;
        }
        
        //Player 1 win
        if ( !gPlayer1WinTexture.loadRenderedText(gMenuFont, "Player black wins!", menuColor, gRenderer)) {
            printf("Could not load menu battle texture!\n");
            success = false;
        }
        
        //Player 2 win
        if ( !gPlayer2WinTexture.loadRenderedText(gMenuFont, "Player orange wins!", menuColor, gRenderer)) {
            printf("Could not load menu battle texture!\n");
            success = false;
        }
        
        
    }
    
    //Load head texture (Player 1)
    if (!gHeadTexture.loadFromFile("head.png", gRenderer)) {
        printf("Could not load head image!\n");
        success = false;
    }
    
    //Load tail texture (Player 1)
    if (!gTailTexture.loadFromFile("tail.png", gRenderer)) {
        printf("Could not load tail image!\n");
        success = false;
    }
    
    //Load head texture (Player 2)
    if (!gHeadTexture2.loadFromFile("head_orange.png", gRenderer)) {
        printf("Could not load orange head image!\n");
        success = false;
    }
    
    //Load tail texture (Player 2)
    if (!gTailTexture2.loadFromFile("tail_orange.png", gRenderer)) {
        printf("Could not load orange tail image!\n");
        success = false;
    }
    
    //Load fruit texture
    if (!gFruitTexture.loadFromFile("fruit.bmp", gRenderer)) {
        printf("Could not load fruit image!\n");
        success = false;
    }
    
    return success;
}

bool loadFinalMedia(int finalLength) {
    //Final flag
    bool success = true;
    
    //Open font
    gFinalFont = TTF_OpenFont("Abduction.ttf", 40);
    if (gFinalFont == NULL) {
        printf("Could not open final font!\n");
        success = false;
    } else {
        //Set color
        SDL_Color scoreColor = { 0, 0, 0 };
        
        //Score
        string finalScore = "Poop count: ";
        finalScore += to_string(finalLength);
        if (!gFinalScoreTexture.loadRenderedText(gFinalFont, finalScore, scoreColor, gRenderer)) {
            printf("Could not load final score!\n");
            success = false;
        }
    }
    
    return success;
}

void close() {
    //Destroy textures
    gHeadTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    
}

//Member function?
bool P1IsNotInBox(Head_P1 head) {
    return head.getPosX() < 0 || head.getPosX() > (WINDOW_WIDTH - head.getHeadWidth()) ||
    head.getPosY() < 0 || head.getPosY() > (WINDOW_HEIGHT - head.getHeadHeight());
}

bool P2IsInBox(Head_P2 head) {
    return head.getPosX() < 0 || head.getPosX() > (WINDOW_WIDTH - head.getHeadWidth()) ||
    head.getPosY() < 0 || head.getPosY() > (WINDOW_HEIGHT - head.getHeadHeight());
}

//Member function?
void CheckP1HitWall() {
    //Hits wall and warps to other end P1
    //Goes too far left
    if (head_p1.getPosX() < 0) {
        head_p1.setPos(WINDOW_WIDTH - head_p1.getHeadWidth(), head_p1.getPosY());
    }
    //Goes too far right
    else if (head_p1.getPosX() > WINDOW_WIDTH - head_p1.getHeadWidth()) {
        head_p1.setPos(0, head_p1.getPosY());
    }
    //Goes too far up
    else if (head_p1.getPosY() < 0) {
        head_p1.setPos(head_p1.getPosX(), WINDOW_HEIGHT - head_p1.getHeadHeight());
    }
    //Goes too far down
    else if (head_p1.getPosY() > WINDOW_HEIGHT - head_p1.getHeadHeight()) {
        head_p1.setPos(head_p1.getPosX(), 0);
    }
}

void CheckP2HitWall() {
    //Hits wall and warps to other end P2
    //Goes too far left
    if (head_p2.getPosX() < 0) {
        head_p2.setPos(WINDOW_WIDTH - head_p2.getHeadWidth(), head_p2.getPosY());
    }
    //Goes too far right
    else if (head_p2.getPosX() > WINDOW_WIDTH - head_p2.getHeadWidth()) {
        head_p2.setPos(0, head_p2.getPosY());
    }
    //Goes too far up
    else if (head_p2.getPosY() < 0) {
        head_p2.setPos(head_p2.getPosX(), WINDOW_HEIGHT - head_p2.getHeadHeight());
    }
    //Goes too far down
    else if (head_p2.getPosY() > WINDOW_HEIGHT - head_p2.getHeadHeight()) {
        head_p2.setPos(head_p2.getPosX(), 0);
    }
}

//  Title screen loop
void titleScreen(SDL_Event e, bool& quit, gameMode& gameMode) {
    //Check if game has been started
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    gameMode = GAME_MODE_SINGLE_PLAY;
                    break;
                    
                case SDLK_2:
                    gameMode = GAME_MODE_PVP;
                    break;
            }
            
        }
    }
    
    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    
    //Draw title
    gTitleTexture.render(gRenderer, (WINDOW_WIDTH - gTitleTexture.getWidth()) / 2, 50);
    
    //Draw menu
    gMenuSoloTexture.render(gRenderer, (WINDOW_WIDTH - gMenuSoloTexture.getWidth()) / 2, 200);
    gMenuPvPTexture.render(gRenderer, (WINDOW_WIDTH - gMenuPvPTexture.getWidth()) / 2, 250);
    
    //Update screen
    SDL_RenderPresent(gRenderer);
}






























