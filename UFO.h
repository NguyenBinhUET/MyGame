#pragma once
#include"constant.h"
#include"bullet.h"
#include<SDL.h>

class UFO {
private:
    float x, y;
    float velocityX, velocityY;
    int size;
    float timer;
    bool shooting;
public:
    //init
    UFO(float _x, float _y);

    void update();

    //getter
    float getX() const {return x;};
    float getY() const {return y;};
    float shoot() const {return shooting;};
    int getSize() const {return size;};

    bullet spawnBullet(float tarX, float tarY);
};
