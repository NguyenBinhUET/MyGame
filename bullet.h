#pragma once
#include<SDL.h>
#include"constant.h"
#include"helper.h"

using namespace std;

class bullet {
private:
    float x, y;
    float velocityX, velocityY, angle;
    int lifeTime = BULLET_LIFE_TIME;
    bool alive;
public:
    //init
    bullet(float _x, float _y, float _angle, float playerVx, float playerVy);

    void update();

    //getter
    bool isAlive() const {return alive;};
    float getX() const {return x;};
    float getY() const {return y;};
    float getAngle() const {return angle;};
};
