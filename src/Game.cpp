#include "../include/Game.h"

Game::Game(){
    this->init();
}

Game::~Game(){
    UnloadMusicStream(introMusic);
}

void Game::init(){
    this->initMusic();
    this->initSound();
    this->initCamera();
    player = new Entity({128,384},MAROON);
    spawner = new Spawner({128,256});
    std::cout<<"Game instance initialised."<<"\n";
}

void Game::handleInput(){
    this->playerControls();
}

void Game::update(){
    player->update();
    spawner->update();
    this->updatePlayerCollision();
    this->updateEnemyCollision();
    this->updateBulletCollision();
    this->deleteInactiveBullet();
    this->updateCameraCentre(&camera,GetScreenWidth(),GetScreenHeight());
    this->updateMusic();
}

void Game::draw(){
    BeginMode2D(camera);
        this->drawBackground();
        this->drawGameInstructions();
        player->draw();
        spawner->draw();
    EndMode2D();
}

void Game::initCamera(){
    camera.target=player->getPos();
    camera.offset=(Vector2){GetScreenWidth()/2.f,GetScreenHeight()/2.f};
    camera.rotation=0.0f;
    camera.zoom=1.f;
}

void Game::updateCameraCentre(Camera2D* camera, float width, float height){
    camera->offset=(Vector2){width/2.f,height/2.f};
    camera->target=player->getPos();
}

void Game::updateCameraCentreInWindow(Camera2D* camera, float width, float height, float num){
    camera->target=player->getPos();
    camera->offset=(Vector2){width/2.f,height/2.f};
    float minX=num, minY=num, maxX=-num, maxY=-num;
    Vector2 max=GetWorldToScreen2D((Vector2){maxX,maxY},*camera);
    Vector2 min=GetWorldToScreen2D((Vector2){minX,minY},*camera);

    if(max.x<width){
        camera->offset.x = width-(max.x-width/2);
    }
    if(max.y<height){
        camera->offset.y = height-(max.y-width/2);
    }
    if(min.x>0){
        camera->offset.x = width/2-min.x;
    }
    if(min.y>0){
        camera->offset.y = height/2-min.y;
    }

}

void Game::drawBackground(){
    background.draw();
}

void Game::drawGameInstructions(){
    DrawText("A/D to MOVE",0,300,20,RAYWHITE);
    DrawText("S to SHIELD",0,320,20,RAYWHITE);
    DrawText("LMB to ATK",0,340,20,RAYWHITE);
}

void Game::playerControls(){

    // MOVE CONTROLS
    if(IsKeyDown(KEY_A)){
        player->flipLeft();
        player->setState(WALK);
        player->moveLeft();
    }else if(IsKeyDown(KEY_D)){
        player->flipRight();
        player->setState(WALK);
        player->moveRight();
    }else{
        player->setState(IDLE);
    }

    // JUMP CONTROLS
    if(IsKeyPressed(KEY_SPACE)){
        player->setState(JUMP);
        player->jump();
        PlaySound(jumpSound);
    }

    // SHOOT CONTROLS
    // need to fix sound gliching when holding down fire button
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        player->setState(ATTACK);
        player->attack();
        PlaySound(shootLaser);
    }
}

void Game::updatePlayerCollision(){

    for(auto& wall:background.wallVector){

        // player collision with wall in x-plane
        if(CheckCollisionRecs(player->getRect(),wall->bound.left)){
            player->setPos({wall->getPos().x-64.f,player->getPos().y});
            break;
        }
        else if(CheckCollisionRecs(player->getRect(),wall->bound.right)){
            player->setPos({wall->getPos().x+64.f,player->getPos().y});
            break;
        }

        // player collision with wall in y-plane
        if(CheckCollisionRecs(player->getRect(),wall->bound.top)){
            player->setVelocity({0,0});
            player->setPos({player->getPos().x,wall->getPos().y-64.f});
            break;
        }else if(CheckCollisionRecs(player->getRect(),wall->bound.bot)){
            player->setPos({player->getPos().x,wall->getPos().y+64.f});
            break;
        }
    }
}

void Game::updateEnemyCollision(){
    for(auto& enemy:spawner->enemyVector){
        for(auto& wall:background.wallVector){
   
            if(CheckCollisionRecs(enemy->getRect(),wall->bound.left)){
                enemy->setPos({wall->getPos().x-64.f,enemy->getPos().y});
                break;
            }
            else if(CheckCollisionRecs(enemy->getRect(),wall->bound.right)){
                enemy->setPos({wall->getPos().x+64.f,enemy->getPos().y});
                break;
            }

            if(CheckCollisionRecs(enemy->getRect(),wall->bound.top)){
                enemy->setVelocity({0,0});
                enemy->setPos({enemy->getPos().x,wall->getPos().y-64.f});
                break;
            }else if(CheckCollisionRecs(enemy->getRect(),wall->bound.bot)){
                enemy->setPos({enemy->getPos().x,wall->getPos().y+64.f});
                break;
            }
        }
    }
}

void Game::updateBulletCollision(){
    for(auto& bullet:player->bulletVector){
        for(auto& wall:background.wallVector){
            if(CheckCollisionRecs(bullet.getRect(), wall->getRect())){
                bullet.active={false};
            }
        }
    }
}

void Game::deleteInactiveBullet(){
    for(auto it=player->bulletVector.begin(); it!=player->bulletVector.end();){
        if(!it->active){
            it=player->bulletVector.erase(it);
        }else{
            ++it;
        }
    }
}

void Game::initMusic(){
    introMusic=LoadMusicStream("resource/MUSIC/DARK-FANTASY-MUSIC-02.mp3");
    SetMusicVolume(introMusic,0.5f);
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
    shootLaser=LoadSound("resource/SOUNDS/SHOOT-LASER.ogg");
    jumpSound=LoadSound("resource/SOUNDS/JUMP.ogg");
}
