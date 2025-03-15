#include"constant.h"
#include"bullet.h"
#include<cmath>

bullet::bullet(float _x, float _y, float _angle, float playerVx, float playerVy)
    :x(_x), y(_y), velocityX(0.0f), velocityY(0.0f), angle(_angle), alive(1) {
    float radian = angle * M_PI / 180.0f;
    velocityX = cos(radian) * BULLET_SPEED + playerVx;
    velocityY = sin(radian) * BULLET_SPEED + playerVy;
}

void bullet::update() {
    //move
    x += velocityX;
    y += velocityY;

    //wrap
    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
    lifeTime--;
    if(lifeTime == 0) alive = 0;
}

