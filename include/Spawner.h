#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "Enemy.h"

class Spawner{
public:
    Spawner(Vector2 pos);

    void init();
    void draw();
    void update();
    void spawnEnemy();

    void initTexture();
    void initTimer();

private:
    Vector2 m_pos={0.f,0.f};
    Texture2D m_texture;

    // SPAWN TIMER VARIABLES
    int spawnCount={3};
    std::vector<Enemy*> enemyVector;
    float m_spawnTime={0.f};
    bool canSpawn={false};
    Timer spawnTimer={0};
};