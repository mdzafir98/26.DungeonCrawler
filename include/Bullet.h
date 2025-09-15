#pragma once
#include <raylib.h>
#include "Constants.h"

class Bullet{
public:
    Bullet(Vector2 pos, int direction);
    ~Bullet();

    // FUNCTIONS
    void draw();
    void update();
    Rectangle getRect();

    void setSpeed(int speed);

public:
    bool active={true};

private:
    Vector2 m_pos;
    int m_bulletSpeed = {10};
    int m_direction = {1};
    Color m_color = {GREEN};
};
