#pragma once
#include <raylib.h>
#include <raymath.h>
#include "Bullet.h"
#include "Timer.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum State{
    IDLE = 0,
    WALK = 1,
    ATTACK = 2,
    JUMP = 3,
    FALL = 4
};

class Entity{
public:
    Entity(Vector2 pos, Color color);
    ~Entity();

    // TEXTURE FUNCTIONS
    Vector2 spriteSize = {64.f, 64.f};
    void init();
    virtual void initTexture();
    void setTexture(std::string filepath);

    // UPDATE FUNCTIONS
    void update();
    void updateIdleAnimation();
    void updateWalkAnimation();
    void updateAttackAnimation();
    void updateJumpAnimation();
    void updateFallAnimation();
    void updateEntityDirection();
    Rectangle getRect() const;

    // // DRAW FUNCTIONS
    void draw();
    void drawIdleAnimation();
    void drawWalkAnimation();
    void drawAttackAnimation();
    void drawJumpAnimation();
    void drawFallAnimation();

    // STATE FUNCTIONS
    State getState() const;
    void setState(State state);

    // MOVE FUNCTIONS
    void moveRight();
    void moveLeft();
    void lookRight();
    void lookLeft();
    void slamDown();
    void jump();
    Vector2 getPos() const;
    void setPos(Vector2 newPos);
    void flipRight();
    void flipLeft();
    void updateGravity();
    void setVelocity(Vector2 velocity);
    float getGroundLevel() const;
    void setGroundLevel(float y);

    // ATTACK FUNCTIONS
    void attack();
    void getDamaged(int dmg);
    int getHealth();
    void drawBullet();
    void updateBullet();
    std::vector<Bullet> bulletVector;

private:
    virtual void updateEntityCollision();
    void getKnockedBack();
    void deductEntityHealth(int damage);

public:
    float m_groundLevel={(float)(GetScreenHeight())};
    float* m_groundLevelPtr=&m_groundLevel; // pointer to the groundLevel

private:
    // BASIC VARIABLES
    float deltaTime = GetFrameTime();
    Vector2 m_pos = {100, 100};
    Color m_shade = {LIGHTGRAY};
    Color m_color = {GREEN};
    Vector2 m_velocity = {0.f, 0.f};
    float m_speed = {200.f};
    Vector2 mousePos = {0.f, 0.f};
    bool canShoot = {true};
    bool lookingRight = {false};
    int m_health = {10};

    // JUMP VARIABLES
    bool canJump = {true};
    bool grounded = {true};
    void clampToGround();
    float m_gravity = {10.f};
    float jumpHeight = {500.f};
    float slamSpeed = {100.f};
    double lastJumpTime = {0.f};
    float m_jumpRate = {0.5f};

    // ANIMATION VARIABLES
    Texture2D idleTexture, walkTexture, attackTexture, jumpTexture, fallTexture;
    Rectangle frameRec;
    int currFrame = {0};
    int frameCounter = {0};
    int frameSpeed = {10};
    State m_entityState = {IDLE};

    // ATTACK VARIABLES
    double lastFireTime = {0.f};
    float m_fireRate = {0.35f};
    float knockedDistance = {100.f};

    // TIMER
    Timer getDamagedTimer = {0};
    float canGetDamagedLife = {0.25f};
    bool canGetDamaged = {true};
};
