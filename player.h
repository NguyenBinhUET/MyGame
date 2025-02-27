#pragma once
#include"constant.h"
#include"bullet.h"
#include<SDL.h>

class Spaceship {
private:
    float x, y;
    float angle;
    float velocityX, velocityY;
    int width = 30, height = 30;
    int lifePoint = START_LIFE_POINT;
    int shield;
public:
    Spaceship(float start_x, float start_y);

    void update();

    void render(SDL_Renderer* renderer);

    void setAngle(float newAngle);

    void rotateLeft(float degree);

    void rotateRight(float degree);

    void moveForward(float moveAmount);

    float getX() const;

    float getY() const;

    int getWidth() const;

    int getLifePoint() const;

    void changeLifePoint(int newLifePoint);

    void respawn();

    bool hasShield();

    Bullet spawnBullet();
};
