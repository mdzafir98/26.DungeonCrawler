#include "../include/Entity.h"

Entity::Entity(Vector2 pos, Color color){
    m_pos = pos;
    m_color = color;
    this->init();
    std::cout << "Entity instance created successfully." << "\n";
}

Entity::~Entity(){
    std::cout<<"Entity instance deleted."<<"\n";
}

void Entity::init(){
    this->initTexture();
    m_entityState = {IDLE};
    std::cout << "Entity initialised successfully." << "\n";
}

void Entity::initTexture(){
    idleTexture = LoadTexture("resource/RED-GUNNER-RESRC/03.SPRITE SHEET/IDLE.png");
    walkTexture = LoadTexture("resource/RED-GUNNER-RESRC/03.SPRITE SHEET/WALK.png");
    attackTexture = LoadTexture("resource/RED-GUNNER-RESRC/03.SPRITE SHEET/ATTACK.png");
    jumpTexture = LoadTexture("resource/RED-GUNNER-RESRC/03.SPRITE SHEET/JUMP.png");
    fallTexture = LoadTexture("resource/RED-GUNNER-RESRC/03.SPRITE SHEET/FALL.png");

    frameRec={0.f, 0.f, (float)spriteSize.x, (float)spriteSize.y};
}

void Entity::setTexture(std::string filepath){
    
}

void Entity::update(){

    // UPDATE ENTITY STATE
    this->updateEntityDirection();
    this->updateEntityCollision();
    switch(m_entityState)
    {
        case IDLE:
            updateIdleAnimation();
            break;
        case WALK:
            updateWalkAnimation();
            break;
        case ATTACK:
            updateAttackAnimation();
            break;
        case JUMP:
            break;
        case FALL:
            break;
    }

    // UPDATE BULLET
    this->updateBullet();

    // UPDATE GRAVITY
    m_pos=Vector2Add(m_pos, m_velocity);
    this->clampToGround();
    // std::cout<<"PLAYER Y-VELOCITY: "<<this->m_velocity.y<<"\n";
}

void Entity::updateIdleAnimation(){
    frameCounter++;
    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currFrame++;
        if(currFrame > 5){
            currFrame = 0;
        }
        frameRec.x = (float)currFrame*(float)idleTexture.width/6;
    }
}

void Entity::updateWalkAnimation(){
    frameCounter++;
    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currFrame++;
        if(currFrame > 5){
            currFrame = 0;
        }
        frameRec.x = (float)currFrame*(float)walkTexture.width/6;
    }
}

void Entity::updateAttackAnimation(){
    frameCounter++;
    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currFrame++;
        if(currFrame > 5){
            currFrame = 0;
        }
        frameRec.x = (float)currFrame*(float)attackTexture.width/6;
    }
}

void Entity::updateJumpAnimation(){

}

void Entity::updateFallAnimation(){

}

void Entity::updateEntityDirection(){
    mousePos=GetMousePosition();
    if(getPos().x + 32.f > 512.f){
        mousePos.x = mousePos.x + 515;
    }
    if(mousePos.x > this->getPos().x + this->spriteSize.x/2){
        lookingRight = true;
        this->flipRight();
    }
    if(mousePos.x < this->getPos().x + this->spriteSize.x/2){
        lookingRight = false;
        this->flipLeft();
    }
    // std::cout<<"DATA: "<<"\n";
    // std::cout<<"mouse-x: "<<mousePos.x<<"\n";
    // std::cout<<"pos-x: "<<(getPos().x+32)<<"\n";
}

Rectangle Entity::getRect() const{
    return {m_pos.x, m_pos.y, 64.f, 64.f};
}

void Entity::draw(){

    // DRAW ENTITY
    switch(m_entityState)
    {
        case IDLE:
            drawIdleAnimation();
            break;
        case WALK:
            drawWalkAnimation();
            break;
        case ATTACK:
            drawAttackAnimation();
            break;
        case JUMP:
            drawJumpAnimation();
            break;
        case FALL:
            drawFallAnimation();
            break;
    }

    // DRAW BULLET
    this->drawBullet();
}

void Entity::drawIdleAnimation(){
    DrawTextureRec(idleTexture, frameRec, m_pos, m_shade);
}

void Entity::drawWalkAnimation(){
    DrawTextureRec(walkTexture, frameRec, m_pos, m_shade);
}

void Entity::drawAttackAnimation(){
    DrawTextureRec(attackTexture, frameRec, m_pos, m_shade);
}

void Entity::drawJumpAnimation(){
    DrawTextureRec(jumpTexture, frameRec, m_pos, m_shade);
}

void Entity::drawFallAnimation(){
    DrawTextureRec(fallTexture, frameRec, m_pos, m_shade);
}

State Entity::getState() const{
    return m_entityState;
}

void Entity::setState(State state){
    m_entityState = state;
}

void Entity::moveRight(){
    m_pos.x += m_speed * GetFrameTime();
}

void Entity::moveLeft(){
    m_pos.x -= m_speed * GetFrameTime();
}

void Entity::lookRight(){
    this->flipRight();
    lookingRight = {true};
}

void Entity::lookLeft(){
    this->flipLeft();
    lookingRight = {false};
}

void Entity::slamDown(){
    if(grounded == false){
        m_velocity.y += slamSpeed * GetFrameTime();
    }
}

void Entity::jump(){

    // THIS FUNCTION WILL RUN WHEN PLAYER IS ON GROUND LVL
    if((GetTime()-lastJumpTime >= m_jumpRate) && canJump){
        m_velocity.y = -jumpHeight * GetFrameTime();
        lastJumpTime = GetTime();
        std::cout << "Entity jump." << "\n";
    }
}

Vector2 Entity::getPos() const{
    return m_pos;
}

void Entity::setPos(Vector2 newPos){
    m_pos = newPos;
}

void Entity::flipRight(){
    if(frameRec.width < 0){
        frameRec.width = -frameRec.width;
    }
}

void Entity::flipLeft(){
    if(frameRec.width > 0){
        frameRec.width = -frameRec.width;
    }
}

void Entity::updateGravity(){
    if(m_pos.y + spriteSize.y < 400.f){
        m_pos.y += m_gravity * GetFrameTime();
    }
}

void Entity::setVelocity(Vector2 velocity){
    m_velocity = velocity;
}

float Entity::getGroundLevel() const{
    return m_groundLevel;
}

void Entity::setGroundLevel(float y){
    m_groundLevel = y;
}

void Entity::attack(){
    if (GetTime()-lastFireTime >= m_fireRate && canShoot){
        int dirn = (lookingRight) ? 1 : -1;
        bulletVector.push_back(Bullet({this->getPos().x+56.f, this->getPos().y+40.f}, dirn));
        lastFireTime = GetTime();
        std::cout << "Entity attack." << "\n";
        canShoot = false;
    }
    canShoot = true;
}

// TODO: get this function to run once
void Entity::getDamaged(int dmg){
    if(canGetDamaged == true){
        startTimer(&getDamagedTimer, canGetDamagedLife);
        this->deductEntityHealth(dmg);
        canGetDamaged = false;
    }
    updateTimer(&getDamagedTimer);
    stateLifetime(&getDamagedTimer);
    if(timerDone(&getDamagedTimer)){
        canGetDamaged = true;
    }
}

void Entity::deductEntityHealth(int damage){
    if(m_health > 0){
            m_health = m_health - damage;
            this->getKnockedBack();
        }else if(m_health < 0){
            m_health = 0;
        }
}

// TODO: work on knockback function
void Entity::getKnockedBack(){
    m_pos.x += 10.f;
}

int Entity::getHealth(){
    return m_health;
}

void Entity::updateBullet(){
    for(auto& bullet : bulletVector){
        bullet.update();
    }
}

void Entity::drawBullet(){
    for(auto& bullet : bulletVector){
        bullet.draw();
    }
}

void Entity::clampToGround(){
    if(m_pos.y + spriteSize.y < *m_groundLevelPtr){
        m_velocity.y += m_gravity * GetFrameTime();
    }else{
        m_pos.y = *m_groundLevelPtr - spriteSize.y;
        m_velocity.y = 0;
    }
}

void Entity::updateEntityCollision(){

    // ENTITY COLLIDES WITH LEFT-BOUND SCREEN
    if(this->m_pos.x < 0){
        this->setPos({0, this->m_pos.y});
    }
    // ENTITY COLLIDES WITH RIGHT-BOUND SCREEN
    if(this->m_pos.x + 64.f > WORLD_WIDTH){
        this->setPos({WORLD_WIDTH-64.f, this->m_pos.y});
    }

    // ENTITY COLLIDES WITH TOP-BOUND SCREEN
    if(this->m_pos.y < 0){
        this->setPos({this->m_pos.x,0});
    }
}
