#include "../include/Spawner.h"

Spawner::Spawner(Vector2 pos){
    m_pos=pos;
    this->init();
}

void Spawner::init(){
    this->initTimer();
    this->initTexture();
    m_state={WAIT};
    std::cout<<"Spawner entity init successfully."<<"\n";
}

void Spawner::initTexture(){
    idleTexture=LoadTexture("resource/SPAWNER/03.SPRITE SHEET/IDLE-01.png");
    spawnTexture=LoadTexture("resource/SPAWNER/03.SPRITE SHEET/SPAWNING.png");
    attackTexture=LoadTexture("resource/SPAWNER/03.SPRITE SHEET/IDLE-02.png");
    frameRec={0.f,0.f,64.f,64.f};
}

void Spawner::initTimer(){
    m_spawnTime={10.f};
}

void Spawner::draw(){
    // draw entity according to state
    switch(m_state)
    {
        case WAIT:
            drawIdleAnimation();
            break;
        case SPAWNING:
            drawSpawnAnimation();
            break;
        case SLEEP:
            drawAttackAnimation();
            break;
    }

    // draw enemy in vector
    for(auto& i:enemyVector){
        i->draw();
    }
}

void Spawner::update(){

    switch(m_state)
    {
        case WAIT:
            updateIdleAnimation();
            break;
        case SPAWNING:
            updateSpawnAnimation();
            break;
        case SLEEP:
            updateAttackAnimation();
            break;
    }

    // spawn enemy function every few seconds
    if(spawnCount>0){
        if(canSpawn==false){
        startTimer(&spawnTimer,m_spawnTime);
        canSpawn=true; 
        }
        updateTimer(&spawnTimer);
        // stateLifetime(&spawnTimer);
        if(spawnTimer.m_lifetime<5.f){
            m_state={SPAWNING};
        }else{
            m_state={WAIT};
        }
        if(timerDone(&spawnTimer)){
            this->spawnEnemy();
            canSpawn={false};
        }
    }else{
        m_state={SLEEP};
    }

    // update enemy in vector
    for(auto& i:enemyVector){
        i->update();
    }
}

void Spawner::updateIdleAnimation(){
    frameCounter++;
    if(frameCounter>=(60/frameSpeed)){
        frameCounter=0;
        currFrame++;
        if(currFrame>3){
            currFrame=0;
        }
        frameRec.x=(float)currFrame*(float)idleTexture.width/4;
    }
}

void Spawner::updateSpawnAnimation(){
    frameCounter++;
    if(frameCounter>=(60/frameSpeed)){
        frameCounter=0;
        currFrame++;
        if(currFrame>9){
            currFrame=0;
        }
        frameRec.x=(float)currFrame*(float)spawnTexture.width/10;
    }
}

void Spawner::updateAttackAnimation(){
    frameCounter++;
    if(frameCounter>=(60/frameSpeed)){
        frameCounter=0;
        currFrame++;
        if(currFrame>7){
            currFrame=0;
        }
        frameRec.x=(float)currFrame*(float)attackTexture.width/8;
    }
}

void Spawner::drawIdleAnimation(){
    DrawTextureRec(idleTexture,frameRec,m_pos,m_shade);
}

void Spawner::drawSpawnAnimation(){
    DrawTextureRec(spawnTexture,frameRec,m_pos,RAYWHITE);
}

void Spawner::drawAttackAnimation(){
    DrawTextureRec(attackTexture,frameRec,m_pos,m_shade);
}

void Spawner::spawnEnemy(){
    spawnCount--;
    Enemy* enemy = new Enemy(this->m_pos,100.f);
    enemyVector.push_back(enemy);
    std::cout<<"Enemy entity spawn."<<"\n";
}