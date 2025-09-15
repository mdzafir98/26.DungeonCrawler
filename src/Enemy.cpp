#include "../include/Enemy.h"

Enemy::Enemy(Vector2 pos, float speed){
    m_pos = pos;
    m_speed = speed;
    this->init();
}

void Enemy::init(){
    m_health = 5;
    this->initTexture();
    this->initTimer();
}

void Enemy::initTexture(){
    // m_texture=LoadTexture("resource/GREEN-GHOST-RESRC/03.SPRITE SHEET/PURPLE-IDLE.png");
    frameRec={0.f, 0.f, 64.f, 64.f};
}

void Enemy::initTimer(){
    // generate random number between 2 and 4
    srand((unsigned int)time(NULL));
    jumpLife = rand() % 3 + 2;
    movingRight = rand() % 2;
    std::cout << "Enemy entity jump life: " << jumpLife << "\n";
    std::cout << "Enemy direction: " << movingRight << "\n";
}

void Enemy::draw(){
    // draw animation cycle
    if(active){
        DrawTextureRec(m_texture, frameRec, m_pos, m_shade);
    }
}

void Enemy::update(){
    this->checkHealth();
    if(active){
        m_pos = Vector2Add(m_pos, m_velocity);
        this->clampToGround();
        this->updateCollision();
        this->updateMovement();
        this->updateAnimation();
    }
}

void Enemy::updateAnimation(){
    frameCounter++;
    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currFrame++;
        if(currFrame > 4){
            currFrame = 0;
        }
        frameRec.x = (float)currFrame*(float)m_texture.width/4;
    }
}

Vector2 Enemy::getPos() const{
    return m_pos;
}

Rectangle Enemy::getRect() const{
    return {m_pos.x, m_pos.y, 64.f, 64.f};
}

void Enemy::updateCollision(){
    // COLLIDES WITH LEFT BOUND
    if(m_pos.x < 0){
        this->setPos({0.f, m_pos.y});
    }

    // COLLIDES WITH RIGHT BOUND
    if(m_pos.x + m_width > WORLD_WIDTH){
        this->setPos({WORLD_WIDTH-m_width, m_pos.y});
    }

    // ENTITY COLLIDES WITH TOP-BOUND SCREEN
    if(this->m_pos.y < 0){
        this->setPos({this->m_pos.x, 0});
    }
}

void Enemy::updateMovement(){
    // SIMPLE LEFT TO RIGHT MOVEMENT BOUNCING OFF WALL
    if(movingRight == true){
        this->flipRight();
        if(m_pos.x + m_width < WORLD_WIDTH){
            this->moveRight();
        }else{
            movingRight =  {false};
        }
    }
    if(movingRight == false){
        this->flipLeft();
        if(m_pos.x > 0){
            this->moveLeft();
        }else{
            movingRight = {true};
        }
    }

    // JUMP FUNCTION
    if(canJump == false){
        startTimer(&jumpTimer, jumpLife);
        canJump = true;
    }
    updateTimer(&jumpTimer);
    if(timerDone(&jumpTimer)){
        this->jump();
        canJump = {false};
    }
}

void Enemy::setPos(Vector2 newPos){
    m_pos = newPos;
}

void Enemy::setVelocity(Vector2 newVel){
    m_velocity = newVel;
}

void Enemy::setTexture(Texture2D* texture){
    m_texture = *texture;
}

void Enemy::getDamaged(){
    m_health--;
}

void Enemy::moveRight(){
    m_pos.x += m_speed * GetFrameTime();
}

void Enemy::moveLeft(){
    m_pos.x -= m_speed * GetFrameTime();
}

void Enemy::flipLeft(){
    if(frameRec.width > 0){
        frameRec.width = -frameRec.width;
    }
}

void Enemy::flipRight(){
    if(frameRec.width < 0){
        frameRec.width = -frameRec.width;
    }
}

void Enemy::jump(){
    m_velocity.y = -jumpHeight * GetFrameTime();
}

void Enemy::clampToGround(){
    if(m_pos.y + m_height < m_groundLevel){
        m_velocity.y += m_gravity * GetFrameTime();
    }else{
        m_pos.y = m_groundLevel - m_height;
        m_velocity.y = 0;
    }
}

void Enemy::checkHealth(){
    if(m_health <= 0){
        active = false;
    }
}