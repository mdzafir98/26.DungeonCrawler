#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Wall.h"

struct Background{
public:
    // CONSTRUCTOR
    Background(){
        init();
        std::cout << "Background instance created." << "\n";
    }

    // FUNCTIONS
    void init(){
        this->initPlatform();
        this->initWall();
        this->initStatic();
        std::cout << "Background initialised successfully." << "\n";
    }

    void initPlatform(){
        // init the platform structures
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 8; j++){
                if(DUNGEON_MAP[j][i] == 1){
                    x = rand()%3;
                    Wall* wall = new Wall(i*64, j*64, textArray[x]);
                    wallVector.push_back(wall);
                }
            }
        }
    }

    void initWall(){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 8; j++){
                if(DUNGEON_MAP[j][i] == 0){
                    Wall* wall = new Wall(i*64, j*64, normalBGPtr);
                    bgVector.push_back(wall);
                }
            }
        }
    }

    // init static background for intro screen
    void initStatic(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(STATIC_MAP[j][i] == 0){
                    Wall* wall = new Wall(i*64, j*64, normalBGPtr);
                    staticBGVector.push_back(wall);
                }
            }
        }
    }

    void draw(){
        // draw the platforms
        for(auto& wall : wallVector){
            wall->draw();
        }

        // draw the background
        for(auto& bg : bgVector){
            bg->draw(DARKGRAY);
        }
    }

    void drawStatic(){
        // draw static background
        for(auto& bg : staticBGVector){
            bg->draw(DARKGRAY);
        }
    }

private:
    // VARIABLES
    int x = {0};

    // PLATFORM TEXTURES and POINTERS
    Texture2D normalWall = LoadTexture("resource/BRICK-WALL/02.PNG FILES/BRICK-WALL-ASE1.png");
    Texture2D crackWall = LoadTexture("resource/BRICK-WALL/02.PNG FILES/BRICK-WALL-ASE2.png");
    Texture2D normalWall2 = LoadTexture("resource/BRICK-WALL/02.PNG FILES/BRICK-WALL-ASE1.png");
    Texture2D crackWall2 = LoadTexture("resource/BRICK-WALL/02.PNG FILES/BRICK-WALL-ASE4.png");

    Texture2D* normalWallPtr = &normalWall;
    Texture2D* crackWallPtr = &crackWall;
    Texture2D* normalWallPtr2 = &normalWall2;
    Texture2D* crackWallPtr2 = &crackWall2;
    Texture2D* textArray[4] = {normalWallPtr, crackWallPtr, normalWallPtr2, normalWallPtr};

    // BACKGROUND TEXTURES
    Texture2D normalBG = LoadTexture("resource/BRICK-WALL/02.PNG FILES/GREY-BRICK-WALL-01.png");
    Texture2D* normalBGPtr = &normalBG;

public:
    // vector that contains the platform
    std::vector<Wall*> wallVector;

    // vector that contains the background
    std::vector<Wall*> bgVector;
    std::vector<Wall*> staticBGVector;

private: // MAPS
    int STATIC_MAP[8][8]={
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };

    int TOWER_MAP[16][8]={
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,0,0}
    };

    int DUNGEON_MAP[8][16]={
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
};
