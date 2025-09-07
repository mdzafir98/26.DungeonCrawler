#include "../include/Spawner.h"

Spawner::Spawner(Vector2 pos){
    m_pos=pos;
    this->init();
}

void Spawner::init(){
    this->initTimer();
    this->initTexture();
}

void Spawner::initTexture(){

}

void Spawner::initTimer(){
    m_spawnTime={15.f};
}

void Spawner::draw(){
    DrawRectangle(m_pos.x,m_pos.y,64,64,GREEN);

    // draw enemy in vector
    for(auto& i:enemyVector){
        i->draw();
    }
}

void Spawner::update(){

    // spawn enemy function every few seconds
    if(spawnCount>0){
        if(canSpawn==false){
        startTimer(&spawnTimer,m_spawnTime);
        canSpawn=true; 
        }
        updateTimer(&spawnTimer);
        stateLifetime(&spawnTimer);
        if(timerDone(&spawnTimer)){
            this->spawnEnemy();
            canSpawn={false};
        }
    }

    // update enemy in vector
    for(auto& i:enemyVector){
        i->update();
    }
}

void Spawner::spawnEnemy(){
    spawnCount--;
    Enemy* enemy = new Enemy(this->m_pos,100.f);
    enemyVector.push_back(enemy);
    std::cout<<"Enemy entity spawn."<<"\n";
}