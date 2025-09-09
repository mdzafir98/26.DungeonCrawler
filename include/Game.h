#pragma once
#include <raylib.h>
#include <iostream>

#include "../include/Entity.h"
#include "../include/Background.h"
#include "../include/Spawner.h"

enum GAME_STATE{
    INTRO=0,
    LOOP=1,
    GAME_OVER=2
};

class Game{
public:
    Game();
    ~Game();

    // FUNCTIONS
    void init();
    void handleInput();
    void update();
    void draw();

private:
    // CAMERA FUNCTIONS
    void initCamera();
    void updateCameraCentre(Camera2D* camera, float width, float height);
    void updateCameraCentreInWindow(Camera2D* camera, float width, float height, float num);

    void drawBackground();
    void drawGameInstructions();

    // PLAYER FUNCTIONS
    void playerControls();
    void updatePlayerCollision();
    void updateBulletCollision();
    void deleteInactiveBullet();

    // ENEMY FUNCTIONS
    void updateEnemyCollision();
    void updateEnemy();

private:
    // CAMERA
    Camera2D camera={0};

    GAME_STATE GameState=INTRO;
    Entity* player;
    Background background;
    bool lookRight={false};
    bool playerCollided={false};

    // MUSIC
    void initMusic();
    void updateMusic();
    Music introMusic, loopMusic, gameOverMusic;

    // SOUND EFFECT
    Sound shootLaser, jumpSound;
    void initSound();

    // ENEMY TEST
    Spawner* spawner;
};
