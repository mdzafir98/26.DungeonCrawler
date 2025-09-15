#include "../include/Boss.h"

Boss::Boss(Vector2 pos){
    m_pos = pos;
    this->init();
}

void Boss::init(){
    this->initTexture();
    this->initTimer();
}

void Boss::initTimer(){
    m_shootLifetime = 2.f;
}

void Boss::draw(){
    // draw animation cycle
    if(active){
        DrawTextureRec(m_texture, frameRec, m_pos, m_shade);
    }

    // draw fireballs shot by BOSS entity
    for(auto& i : fireballVector){
        i.draw();
    }
}

void Boss::initTexture(){
    m_texture = LoadTexture("resource/BOSS/03.SPRITE SHEET/IDLE.png");
    frameRec = {0.f, 0.f, 128.f, 128.f};
}

void Boss::update(Vector2 playerPos){
    if(active){
        this->updateAnimation();
    }

    for(auto& i : fireballVector){
        i.update();
    }
}

void Boss::moveLeft(){
    
}

void Boss::moveRight(){
    
}

void Boss::updateAnimation(){
    frameCounter++;
    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currFrame++;
        if(currFrame > 4){
            currFrame = 0;
        }
        frameRec.x = (float)currFrame * (float)m_texture.width/4;
    }
}

void Boss::shootFireball(Vector2 playerPos){
    std::cout << "Player pos: " << playerPos.x << ", " << playerPos.y << "\n";
}
