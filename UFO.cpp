#include"UFO.h"
#include<cmath>

UFO::UFO(float _x, float _y)
    :x(_x), y(_y), velocityX(BASE_UFO_SPEED), velocityY(BASE_UFO_SPEED), size(BASE_UFO_SIZE), timer(0.0f), shooting(0) {
    velocityX = (rand() % 5 - 2);
    velocityY = sqrt(pow(BASE_UFO_SPEED, 2) + pow(velocityX, 2)) * pow(-1, rand() % 2);
};

void UFO::update() {
    x += velocityX;
    y += velocityY;

    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;

    timer += 0.016f;
    if(shooting) shooting = 0;
    if(timer >= SHOOT_TIMER) {
        timer -= SHOOT_TIMER;
        shooting = 1;
    }
}

bullet UFO::spawnBullet(float tarX, float tarY) {
    float angle = atan2(double(tarY - y), double(tarX - x)) * 180 / M_PI;
    bullet newBullet(x, y, angle, 0, 0);
    return newBullet;
}
