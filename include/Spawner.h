#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Enemy.h"

enum SpawnerState{
    WAIT = 0,
    SPAWNING = 1,
    SLEEP = 2
};

class Spawner{
public:
    Spawner(Vector2 pos);

    void init();
    void draw();
    void update();
    void spawnEnemy();

private:
    void initTexture();
    void initTimer();

    // UPDATE FUNCTIONS
    void updateIdleAnimation();
    void updateSpawnAnimation();
    void updateAttackAnimation();

    // DRAW FUNCTIONS
    void drawIdleAnimation();
    void drawSpawnAnimation();
    void drawAttackAnimation();

public:
    // enemy variables
    std::vector<Enemy*> enemyVector;
    Texture2D enemyTexture = LoadTexture("resource/GREEN-GHOST-RESRC/03.SPRITE SHEET/PURPLE-IDLE.png");

private:
    Vector2 m_pos = {0.f, 0.f};
    Color m_shade = {LIGHTGRAY};

    // ANIMATION VARIABLES
    Texture2D idleTexture, spawnTexture, attackTexture;
    Rectangle frameRec;
    int currFrame = {0};
    int frameCounter = {0};
    int frameSpeed = {10};
    SpawnerState m_state;

    // SPAWN TIMER VARIABLES
    int spawnCount = {3};
    float m_spawnTime = {0.f};
    bool canSpawn = {false};
    Timer spawnTimer = {0};
};