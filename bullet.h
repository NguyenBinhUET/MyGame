#pragma once
#include<SDL.h>
#include"constant.h"
#include"helper.h"

using namespace std;

class bullet {
private:
    float x, y;
    float velocityX = 0, velocityY = 0, angle;
    int lifeTime = BULLET_LIFE_TIME;
    bool isAlive = 1;
public:
    //init
    bullet(float startX, float startY, float startAngle, float playerVx, float playerVy);

    void update();

    void kill();

    //getter
    bool alive() const {return isAlive;};
    float getX() const {return x;};
    float getY() const {return y;};
    float getAngle() const {return angle;};
};
