#pragma once
#include <raylib.h>

struct Bounds{
    Rectangle left,right,top,bot;
};

class Wall{
public:
    // CONSTRUCTOR
    Wall(int x,int y,Texture2D* texture){
        m_x=x;
        m_y=y;
        float b_y=m_y+10;
        m_texture=*texture;
        bound.left={(m_x),(m_y+32),32,1};
        bound.right={(m_x+32),(m_y+32),32,1};
        bound.top={(m_x+32),(m_y),1,32};
        bound.bot={(m_x+32),(m_y+32),1,32};
    }


    // OVERLOADED CONSTUCTOR
    Wall(int x,int y,Texture2D* texture, Color shade){
        m_x=x;
        m_y=y;
        m_texture=*texture;
    }

    // FUNCTIONS
    void draw(){
        DrawTexture(m_texture,m_x,m_y,LIGHTGRAY);
        // this->drawBoundingLines();
    }

    void draw(Color shade){
        DrawTexture(m_texture,m_x,m_y,shade);
    }

    Rectangle getRect() const{
        return {m_x,m_y,64,64};
    }

    Vector2 getPos() const{
        return {m_x,m_y};
    }

    float* getPosYPtr(){
        return m_yPtr;
    }

    void drawBoundingLines(){
        DrawRectangleRec(bound.left,BLUE);
        DrawRectangleRec(bound.right,RED);
        DrawRectangleRec(bound.top,GREEN);
        DrawRectangleRec(bound.bot,YELLOW);
    }

public:
    float m_x={0};
    float m_y={0};
    float* m_xPtr=&m_x;
    float* m_yPtr=&m_y;
    Texture2D m_texture;
    Bounds bound;
};
