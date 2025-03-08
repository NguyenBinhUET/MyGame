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
    int shield;
    int score;
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
    int getScore() const;


    void respawn();

    bool hasShield();

    bullet spawnBullet();

    void resetScore();
    void addScore(const int amount);
};
