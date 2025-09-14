#pragma once
#include "Enemy.h"
#include "Fireball.h"
#include <vector>

class Boss : public Enemy{
public:
    Boss(Vector2 pos);
    void init();
    void initTexture() override;
    void initTimer();
    void draw() override;
    void update(Vector2 playerPos);

    void moveRight() override;
    void moveLeft() override;

    void updateAnimation() override;
    void shootFireball(Vector2 playerPos);

public:
    float spriteSize = 128.f;
    std::vector<Fireball> fireballVector;

    // TIMER
    float m_shootLifetime = {0.f};
    bool canShoot = {true};
    Timer shootTimer = {0};
};
