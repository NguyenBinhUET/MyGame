#include"constant.h"
#include"bullet.h"
#include<cmath>

bullet::bullet(float startX, float startY, float startAngle, float playerVx, float playerVy) :x(startX), y(startY), angle(startAngle) {
    float radian = angle * M_PI / 180.0f;
    velocityX = cos(radian) * BULLET_SPEED + playerVx;
    velocityY = sin(radian) * BULLET_SPEED + playerVy;
}

void bullet::update() {
    x += velocityX;
    y += velocityY;


    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
    lifeTime--;
    if(lifeTime == 0) isAlive = 0;
}

void bullet::render(SDL_Renderer* renderer) {
    float radian = angle * M_PI / 180.0f;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x, y, cos(radian) * BULLET_SIZE + x, sin(radian) * BULLET_SIZE + y);
}

bool bullet::alive() const {
    return isAlive;
}

void bullet::kill() {
    isAlive = 0;
}

float bullet::getX() const {
    return x;
}
float bullet::getY() const {
    return y;
}
