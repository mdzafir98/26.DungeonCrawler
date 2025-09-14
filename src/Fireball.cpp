#include "../include/Fireball.h"

Fireball::Fireball(Vector2 pos, Vector2 playerPos){
    this->initTexture();
    m_pos = pos;
    m_playerPos = playerPos;
    m_direction.x = playerPos.x - m_pos.x;
    m_direction.y = playerPos.y - m_pos.y;
    float length = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
    if(length > 0){
        m_direction.x /= length;
        m_direction.y /= length;
    }
}

// TODO: make texture for fireball entity
void Fireball::initTexture(){

}

void Fireball::draw(){
    while(active){
        DrawRectangle(m_pos.x, m_pos.y, m_spriteSize, m_spriteSize, m_color);
        break;
    }
}

void Fireball::update(){
    this->updateCollision();
    while(active){
        m_pos.y += m_direction.y * m_speed;
        m_pos.x += m_direction.x * m_speed;
        break;
    }
}

void Fireball::updateCollision(){
    if(m_pos.y + m_spriteSize/2 > WORLD_HEIGHT || m_pos.x < 0 || m_pos.x + m_spriteSize > WORLD_WIDTH){
        std::cout << "Fireball is inactive." << "\n";
        active = false;
    }
}

Rectangle Fireball::getRect() const{
    return {m_pos.x, m_pos.y, m_spriteSize, m_spriteSize};
}