#pragma once
#include <raylib.h>

typedef struct Fireball{
public:
    Fireball(Vector2 pos, Vector2 playerPos);
    void draw();
    void update();

public:
    Vector2 m_pos = {0,0};
    float m_speed = 10.f;
    float m_radius = 10.f;
    Color m_color = {GREEN};
    Vector2 m_playerPos;
};