#pragma once
#include "Enemy.h"
#include <vector>

class Boss : public Enemy{
public:
    Boss(Vector2 pos);
    void init();
    void initTexture() override;
    void update() override;

    void moveRight() override;
    void moveLeft() override;

    void updateAnimation() override;
    void shootFireball(Vector2 playerPos);

private:
    float spriteSize = 128.f;
    std::vector<Circle> fireballVector;
};
