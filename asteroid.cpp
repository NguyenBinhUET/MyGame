#include<SDL.h>
#include"asteroid.h"
#include"constant.h"


asteroid::asteroid(float _x, float _y, int _size, int _speedLevel)
    :x(_x), y(_y), angle(0.0f), rotationSpeed(rand() % 3 - 1), size(_size), speedLevel(_speedLevel), textureIndex(rand() % 3)  {
    if(size == 3) {
        velocityX = (rand() % 3 - 1) * (1.0f + speedLevel * 0.1f);
        velocityY = (rand() % 3 - 1) * (1.0f + speedLevel * 0.1f);
    }
    else if(size == 2) {
        velocityX = (rand() % 5 - 2) * (1.0f + speedLevel * 0.1f);
        velocityY = (rand() % 5 - 2) * (1.0F + speedLevel * 0.1f);
    }
    else {
        velocityX = (rand() % 5 - 2) * (1.5f + speedLevel * 0.1f);
        velocityY = (rand() % 5 - 2) * (1.5f + speedLevel * 0.1f);
    }
    if(velocityX == 0 && velocityY == 0) {
        velocityX = rand() % 5 + 1;
        velocityY = rand() % 5 + 1;
    }
};
void asteroid::update()  {

    //move
    angle += rotationSpeed;
    if(angle > 360) angle -= 360;
    x += velocityX;
    y += velocityY;

    //wrap
    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
}
