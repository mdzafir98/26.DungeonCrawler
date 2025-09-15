#include "../include/Bullet.h"

Bullet::Bullet(Vector2 pos, int direction){
    m_pos = pos;
    m_direction = direction;
}

Bullet::~Bullet(){

}

void Bullet::draw(){
    if(active){
        DrawRectangle(m_pos.x, m_pos.y, 10.f, 10.f, m_color);
    }
}

void Bullet::update(){
    // CHECK IF BULLET ESCAPE THE SCREEN BOUNDS
    if(m_pos.x > WORLD_WIDTH || m_pos.x < 0){
        active = {false};
    }
    if(active){
        m_pos.x += m_bulletSpeed * m_direction;
    }
}

Rectangle Bullet::getRect(){
    return {m_pos.x, m_pos.y, 10.f, 10.f};
}

void Bullet::setSpeed(int speed){
    m_bulletSpeed = speed;
}
