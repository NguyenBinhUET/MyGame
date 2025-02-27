#include"constant.h"
#include"bullet.h"
#include<cmath>

Bullet::Bullet(float startX, float startY, float startAngle, float playerVx, float playerVy) :x(startX), y(startY), angle(startAngle) {
    float radian = angle * M_PI / 180.0f;
    velocityX = cos(radian) * BULLET_SPEED + playerVx;
    velocityY = sin(radian) * BULLET_SPEED + playerVy;
}

void Bullet::update() {
    x += velocityX;
    y += velocityY;


    /*if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
    lifeTime--;
    if(lifeTime == 0) isAlive = 0;
        */
}

void Bullet::render(SDL_Renderer* renderer) {
    float radian = angle * M_PI / 180.0f;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x, y, cos(radian) * BULLET_SIZE + x, sin(radian) * BULLET_SIZE + y);
}

bool Bullet::alive() const {
    return isAlive;
}

float Bullet::getX() const {
    return x;
}
float Bullet::getY() const {
    return y;
}
