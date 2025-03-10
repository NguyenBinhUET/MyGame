#include<SDL.h>
#include"asteroid.h"
#include"constant.h"


asteroid::asteroid(float start_X, float start_Y, int start_Size, int start_speedLevel)
    :x(start_X), y(start_Y), angle(0.0f), rotationSpeed(rand() % 3 - 1), size(start_Size), speedLevel(start_speedLevel), textureIndex(rand() % 3)  {
    if(size == 3) {
        velocityX = (rand() % 3 - 1) * (0.7f + speedLevel * 0.05f);
        velocityY = (rand() % 3 - 1) * (0.7f + speedLevel * 0.05f);
    }
    else if(size == 2) {
        velocityX = (rand() % 5 - 2) * (0.7f + speedLevel * 0.05f);
        velocityY = (rand() % 5 - 2) * (0.7F + speedLevel * 0.05f);
    }
    else {
        velocityX = (rand() % 7 - 3) * (0.7f + speedLevel * 0.05f);
        velocityY = (rand() % 7 - 3) * (0.7f + speedLevel * 0.05f);
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
