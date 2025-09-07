#ifdef __cplusplus
    extern "C" { // Tell the C++ compiler to link against C functions
#endif
    #include "raylib.h"
#ifdef __cplusplus
    }
#endif

#include <iostream>
#include "../include/Game.h"

const int SCREEN_WIDTH=512;
const int SCREEN_HEIGHT=512;
Color BACKGROUND_COLOR={29,27,27,255};

/*
HOW TO OPEN THE WEB GAME
    1) bash web-build.bash
    2) python3 -m http.server
    3) open browser -> http://127.0.0.0:8000
    4) opent a.html
    5) CTRL-SHIFT-I to open console
    6) check PRINTF statements
*/

void drawIntructions();
void startAudioDevice();

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DUNGEON CRAWLER");
    InitAudioDevice();

    SetTargetFPS(60);
    bool startMusic={false};
    Game game;

    while (!WindowShouldClose()){
        // if(IsKeyDown(KEY_ENTER) && !startMusic){
        //     startAudioDevice();
        //     startMusic=true;
        // }
        game.handleInput();
        game.update();
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            game.draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
}

void drawIntructions(){
    // DrawText("THIS IS A SIMPLE WEB GAME!",0,0,25,RAYWHITE);
    DrawText("A/D to MOVE",0,300,20,RAYWHITE);
    DrawText("S to SHIELD",0,320,20,RAYWHITE);
    DrawText("LMB to ATK",0,340,20,RAYWHITE);
}

void startAudioDevice(){
    InitAudioDevice();
    std::cout<<"Audio device is enabled in browser!"<<"\n";
}

