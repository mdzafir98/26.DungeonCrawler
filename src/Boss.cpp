#include "../include/Boss.h"

Boss::Boss(Vector2 pos){
    m_pos = pos;
    init();
}

void Boss::init(){
    this->initTexture();
}

// TODO: assign the correct texture
void Boss::initTexture(){
    m_texture = LoadTexture("resource/BOSS/03.SPRITE SHEET/IDLE.png");
    frameRec = {0.f,0.f,128.f,128.f};
}

void Boss::update(){
    if(active){
        this->updateAnimation();
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
        frameRec.x = (float)currFrame*(float)m_texture.width/4;
    }
}

void Boss::shootFireball(Vector2 playerPos){

}
