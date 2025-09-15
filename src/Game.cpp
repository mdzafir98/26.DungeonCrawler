#include "../include/Game.h"

Game::Game(){
    this->init();
}

Game::~Game(){
    UnloadMusicStream(introMusic);
    UnloadMusicStream(loopMusic);
}

void Game::init(){
    this->initMusic();
    this->initSound();
    this->initCamera();
    player = new Entity({128, 384}, MAROON);
    spawner = new Spawner({448, 64});
    boss = new Boss({512, 0});
    std::cout << "Game instance initialised." << "\n";
}

void Game::handleInput(){
    // handle game state logic
    if(IsKeyPressed(KEY_ENTER) && GameState == INTRO){
        GameState = LOOP;
        introLoop = {false};
        gameLoop = {true};

        // play game loop music
        SetMusicVolume(loopMusic, 0.75f);
        PlayMusicStream(loopMusic);
    }
    if(GameState == LOOP){
        this->playerControls();
    }
}

void Game::update(){
    this->updateMusic();

    switch(GameState)
    {
        case INTRO:
            break;
        case LOOP:
            this->updateBoss();
            player->update();
            spawner->update();
            this->updatePlayerCollision();
            this->updateEnemyCollision();
            this->updatePlayerEnemyCollision();
            this->updateEnemy();
            this->updateBulletCollision();
            this->deleteInactiveBullet();
            this->updateCameraCentre(&camera,GetScreenWidth(), GetScreenHeight());
            break;
        case GAME_OVER:
            break;
    }
}

void Game::draw(){
    switch(GameState)
    {
        case INTRO:
            this->drawIntroBackground();
            this->drawIntroMenu();
            break;
        case LOOP:
            this->drawGameLoop();
            break;
        case GAME_OVER:
            this->drawGameOver();
            break;
    }
}

// draw function for the main game loop
void Game::drawGameLoop(){
    BeginMode2D(camera);
        this->drawBackground();
        this->drawGameInstructions();
        boss->draw();
        spawner->draw();
        player->draw();
    EndMode2D();
}

// TODO: add game over logic
void Game::drawGameOver(){
    
}

// TODO: add static background image
void Game::drawIntroBackground(){
    background.drawStatic();
}

void Game::drawIntroMenu(){
    DrawText("DUNGEON CRAWLER v1.0", 50, 100, 30, MAROON);
    DrawText("Press ENTER to \nenter the DUNGEON!", 50, 130, 25, RAYWHITE);
}

void Game::initCamera(){
    camera.target = player->getPos();
    camera.offset = (Vector2){GetScreenWidth()/2.f, GetScreenHeight()/2.f};
    camera.rotation = 0.0f;
    camera.zoom = 1.f;
}

void Game::updateCameraCentre(Camera2D* camera, float width, float height){
    camera->offset = (Vector2){width/2.f, height/2.f};
    camera->target = player->getPos();
}

// FUNCTION not in use -> can delete
void Game::updateCameraCentreInWindow(Camera2D* camera, float width, float height, float num){
    camera->target = player->getPos();
    camera->offset = (Vector2){width/2.f, height/2.f};
    float minX = num, minY = num, maxX = -num, maxY = -num;
    Vector2 max = GetWorldToScreen2D((Vector2){maxX, maxY}, *camera);
    Vector2 min = GetWorldToScreen2D((Vector2){minX, minY}, *camera);

    if(max.x < width){
        camera->offset.x = width-(max.x-width/2);
    }
    if(max.y < height){
        camera->offset.y = height-(max.y-width/2);
    }
    if(min.x > 0){
        camera->offset.x = width/2-min.x;
    }
    if(min.y > 0){
        camera->offset.y = height/2-min.y;
    }
}

void Game::drawBackground(){
    background.draw();
}

void Game::drawGameInstructions(){
    DrawText("A/D to MOVE", 0, 300, 20, RAYWHITE);
    DrawText("SPACEBAR to JUMP", 0, 320, 20, RAYWHITE);
    DrawText("LMB to ATK", 0, 340, 20, RAYWHITE);
}

void Game::playerControls(){

    // MOVE CONTROLS
    if(IsKeyDown(KEY_A)){
        player->flipLeft();
        player->setState(State::WALK);
        player->moveLeft();
    }else if(IsKeyDown(KEY_D)){
        player->flipRight();
        player->setState(State::WALK);
        player->moveRight();
    }else{
        player->setState(State::IDLE);
    }

    // JUMP CONTROLS
    if(IsKeyPressed(KEY_SPACE)){
        player->setState(State::JUMP);
        player->jump();
        PlaySound(jumpSound);
    }

    // SHOOT CONTROLS
    // need to fix sound gliching when holding down fire button
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        player->setState(State::ATTACK);
        player->attack();
        PlaySound(shootLaser);
    }
}

void Game::updatePlayerCollision(){

    for(auto& wall : background.wallVector){

        // player collision with wall in x-plane
        if(CheckCollisionRecs(player->getRect(), wall->bound.left)){
            player->setPos({wall->getPos().x-64.f, player->getPos().y});
            break;
        }else if(CheckCollisionRecs(player->getRect(), wall->bound.right)){
            player->setPos({wall->getPos().x+64.f, player->getPos().y});
            break;
        }

        // player collision with wall in y-plane
        if(CheckCollisionRecs(player->getRect(), wall->bound.top)){
            player->setVelocity({0, 0});
            player->setPos({player->getPos().x, wall->getPos().y-64.f});
            break;
        }else if(CheckCollisionRecs(player->getRect(), wall->bound.bot)){
            player->setPos({player->getPos().x, wall->getPos().y+64.f});
            break;
        }
    }
}

void Game::updateEnemyCollision(){
    for(auto& enemy : spawner->enemyVector){
        for(auto& wall : background.wallVector){
   
            if(CheckCollisionRecs(enemy->getRect(), wall->bound.left)){
                enemy->setPos({wall->getPos().x-64.f, enemy->getPos().y});
                break;
            }
            else if(CheckCollisionRecs(enemy->getRect(), wall->bound.right)){
                enemy->setPos({wall->getPos().x+64.f, enemy->getPos().y});
                break;
            }

            if(CheckCollisionRecs(enemy->getRect(), wall->bound.top)){
                enemy->setVelocity({0, 0});
                enemy->setPos({enemy->getPos().x, wall->getPos().y-64.f});
                break;
            }else if(CheckCollisionRecs(enemy->getRect(), wall->bound.bot)){
                enemy->setPos({enemy->getPos().x, wall->getPos().y+64.f});
                break;
            }
        }
    }
}

void Game::updatePlayerEnemyCollision(){
    for(auto& enemy : spawner->enemyVector){
        if(CheckCollisionRecs(enemy->getRect(), player->getRect())){
            player->getDamaged(1);
            std::cout<<"PLAYER HP: "<<player->getHealth()<<"\n";
        }
    }
}

void Game::updateEnemy(){
    // delete the enemy that got killed and remove from std::vector
    unsigned counter = 0;
    for(auto& enemy : spawner->enemyVector){
        if(enemy->active == false){
            delete spawner->enemyVector.at(counter);
            spawner->enemyVector.erase(spawner->enemyVector.begin()+counter);
            --counter;
            std::cout << "Enemy vector: "<< spawner->enemyVector.size()<< "\n";
        }
        ++counter;
    }
}

void Game::updateBulletCollision(){
    // bullet-wall collision
    for(auto& bullet : player->bulletVector){
        for(auto& wall : background.wallVector){
            if(CheckCollisionRecs(bullet.getRect(), wall->getRect())){
                bullet.active = {false};
            }
        }
    }

    // bullet-enemy collision
    for(auto& bullet : player->bulletVector){
        for(auto& enemy : spawner->enemyVector){
            if(CheckCollisionRecs(bullet.getRect(), enemy->getRect())){
                bullet.active = {false};
                enemy->getDamaged();
            }
        }
    }
}

// remove inactive projectiles shot by BOSS and PLAYER entity
void Game::deleteInactiveBullet(){
    for(auto it = player->bulletVector.begin(); it != player->bulletVector.end();){
        if(!it->active){
            it = player->bulletVector.erase(it);
        }else{
            ++it;
        }
    }

    for(auto it = boss->fireballVector.begin(); it != boss->fireballVector.end();){
        if(!it->active){
            it = boss->fireballVector.erase(it);
        }else{
            ++it;
        }
    }
}

void Game::initMusic(){
    introMusic = LoadMusicStream("resource/MUSIC/DARK-FANTASY-MUSIC-01.mp3");
    loopMusic = LoadMusicStream("resource/MUSIC/DARK-FANTASY-MUSIC-02.mp3");
    gameOverMusic = LoadMusicStream("resource/MUSIC/DARK-FANTASY-GAME-OVER.mp3");

    SetMusicVolume(introMusic, 0.75f);
    PlayMusicStream(introMusic);
}

void Game::updateMusic(){
    switch(GameState)
    {
        case INTRO:
            UpdateMusicStream(introMusic);
            break;
        case LOOP:
            UpdateMusicStream(loopMusic);
            break;
        case GAME_OVER:
            UpdateMusicStream(gameOverMusic);
            break;
    }
}

void Game::initSound(){
    shootLaser = LoadSound("resource/SOUNDS/SHOOT-LASER.ogg");
    jumpSound = LoadSound("resource/SOUNDS/JUMP.ogg");
    fireballSound = LoadSound("resource/SOUNDS/FIREBALL.ogg");
}

void Game::updateBoss(){
    boss->update(player->getPos());
    // shooting fireball mechanic
    // shoot fireball every few seconds
    if(boss->canShoot == true){
        startTimer(&boss->shootTimer, boss->m_shootLifetime);
        std::cout << "Fireball vector: " << boss->fireballVector.size() << "\n";
        boss->canShoot = false;
    }
    updateTimer(&boss->shootTimer);
    if(timerDone(&boss->shootTimer)){
        PlaySound(fireballSound);
        boss->fireballVector.push_back(Fireball({boss->m_pos.x + boss->spriteSize/2, boss->m_pos.y + boss->spriteSize/2}, 
            {player->getPos().x + 32.f, player->getPos().y + 32.f}));
        boss->canShoot = true;
    }
}
