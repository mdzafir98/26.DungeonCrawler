#pragma once
#include <raylib.h>
#include <iostream>

#include "../include/Entity.h"
#include "../include/Background.h"
#include "../include/Spawner.h"
#include "../include/Boss.h"

enum GAME_STATE{
    INTRO = 0,
    LOOP = 1,
    GAME_OVER = 2,
    BOSS_FIGHT = 3
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
    // GAME DRAW FUNCTIONS
    void drawIntroBackground();
    void drawIntroMenu();
    void drawGameLoop();
    void drawGameOver();

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
    void updatePlayerEnemyCollision();

    // ENEMY FUNCTIONS
    void updateEnemyCollision();
    void updateEnemy();

    // BOSS FUNCTIONS
    void updateBoss();

private:
    // GAME LOOP BOOL FLAGS
    bool introLoop={true};
    bool gameLoop={false};

    // CAMERA
    Camera2D camera={0};

    GAME_STATE GameState={INTRO};
    Entity* player;
    Background background;
    bool lookRight={false};
    bool playerCollided={false};

    // MUSIC
    void initMusic();
    void updateMusic();
    Music introMusic, loopMusic, gameOverMusic;
    Music currMusic;

    // SOUND EFFECT
    Sound shootLaser, jumpSound;
    void initSound();

    // ENEMY
    Spawner* spawner;
    Boss* boss;
};
