#pragma once
#include <raylib.h>
#include "Constants.h"
#include <iostream>
#include <math.h>

struct Fireball{
public:
    Fireball(Vector2 pos, Vector2 playerPos);
    void draw();
    void update();
    Rectangle getRect() const;

private:
    void initTexture();
    void updateCollision();

public:
    bool active = {true};

private:
    Vector2 m_direction = {0, 0};
    Vector2 m_pos = {0, 0};
    float m_speed = 10.f;
    float m_spriteSize = 16.f;
    Color m_color = {GREEN};
    Vector2 m_playerPos;
};