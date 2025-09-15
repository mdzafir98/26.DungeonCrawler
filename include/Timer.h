#pragma once
#include <raylib.h>
#include <iostream>

typedef struct{
    float m_lifetime;
}Timer;

// start or restart a timer with a specific lifetime
inline void startTimer(Timer* timer, float lifetime){
    if(timer != nullptr){
        timer->m_lifetime = lifetime;
    }
}

// update a timer with current frame time
inline void updateTimer(Timer* timer){
    if(timer != nullptr && timer->m_lifetime>0){
        timer->m_lifetime -= GetFrameTime();
    }
}

// check if the timer is done, return false if timer<=0
inline bool timerDone(Timer* timer){
    if(timer != nullptr){
        return (timer->m_lifetime<=0);
    }
    return (timer->m_lifetime<=0);
}

inline void stateLifetime(Timer* timer){
    std::cout << "LIFETIME: " << timer->m_lifetime<< "\n";
}