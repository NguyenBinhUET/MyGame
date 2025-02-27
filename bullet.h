#pragma once
#include<SDL.h>
#include"constant.h"

class Bullet {
private:
    float x, y;
    float velocityX = 0, velocityY = 0, angle;
    int lifeTime = BULLET_LIFE_TIME;
    bool isAlive = 1;
public:
    Bullet(float startX, float startY, float startAngle, float playerVx, float playerVy);

    void update();

    void render(SDL_Renderer* renderer);

    bool alive() const;
    void kill();
    float getX() const;
    float getY() const;
};
