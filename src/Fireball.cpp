#include "../include/Fireball.h"

Fireball::Fireball(Vector2 pos, Vector2 playerPos){
    m_pos = pos;
    m_playerPos = playerPos;
}

void Fireball::draw(){
    DrawCircle(m_pos.x, m_pos.y, m_radius, m_color);
}

void Fireball::update(){
    m_pos.y += m_speed;
}