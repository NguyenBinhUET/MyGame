#pragma once
#include<SDL.h>
#include"constant.h"
#include<vector>

class Bullet {
private:
    float x, y;
    float velocityX = 0, velocityY = 0, angle;
    int lifeTime = BULLET_LIFE_TIME;
    bool isAlive = 1;
public:
    //init
    Bullet(float startX, float startY, float startAngle, float playerVx, float playerVy);

    void update();
    void render(SDL_Renderer* renderer);

    void kill();

    //getter
    bool alive() const;
    float getX() const;
    float getY() const;
};

class bullets {
private:
    vector<Bullet> bulletsManager;
public:
    //destruct
    ~bullets()

    void addBullet(Bullet bullet);


    void render() const;
};
