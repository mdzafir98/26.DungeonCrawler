#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "Constants.h"
#include "Timer.h"
#include <stdlib.h>

class Enemy{
public:
    Enemy(Vector2 pos, float speed);
    Enemy() = default;

    void init();
    virtual void draw();
    virtual void update();

    Vector2 getPos() const;
    Rectangle getRect() const;

    // MOVEMENT
    void setPos(Vector2 newPos);
    void setVelocity(Vector2 newVel);
    virtual void moveRight();
    virtual void moveLeft();

    // texture function
    virtual void initTexture();
    void setTexture(Texture2D* texture);
    void getDamaged();

    // animation functions
    virtual void updateAnimation();

private:
    void updateCollision();
    void updateMovement();
    void initTimer();

    void jump();
    void flipLeft();
    void flipRight();
    void checkHealth();

public:
    // BASIC VARIABLES
    Vector2 m_pos;
    float m_speed={100.f};
    float m_width=64.f, m_height=64.f;
    Vector2 m_velocity={0.f,0.f};
    Color m_color={GREEN};
    int m_health=0;
    Color m_shade={LIGHTGRAY};
    bool active={true};

    // ANIMATION VARIABLES
    Texture2D m_texture;
    Rectangle frameRec;
    int currFrame={0};
    int frameCounter={0};
    int frameSpeed={10};
    
private:
    // JUMP VARIABLES
    float m_groundLevel=WORLD_HEIGHT;
    void clampToGround();
    float m_gravity={10.f};
    float jumpHeight={500.f};

    // MOVE VARIABLES
    bool movingRight={false};

    // TIMER
    float jumpLife={0.f};
    bool canJump={false};
    Timer jumpTimer={0};
};