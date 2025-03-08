#include<SDL.h>
#include"asteroid.h"
#include"constant.h"


asteroid::asteroid(float start_X, float start_Y, int start_Size, int start_speedLevel) :x(start_X), y(start_Y), size(start_Size), speedLevel(start_speedLevel) {
    if(size == 3) {
        velocityX = (rand() % 3 - 1) / 2.0f + speedLevel * 0.1f;
        velocityY = (rand() % 3 - 1) / 2.0f + speedLevel * 0.1f;
    }
    else if(size == 2) {
        velocityX = (rand() % 5 - 2) / 2.0f + speedLevel * 0.1f;
        velocityY = (rand() % 5 - 2) / 2.0f + speedLevel * 0.1f;
    }
    else {
        velocityX = (rand() % 7 - 3) / 2.0f + speedLevel * 0.1f;
        velocityY = (rand() % 7 - 3) / 2.0f + speedLevel * 0.1f;
    }
};
void asteroid::update()  {

    x += velocityX;
    y += velocityY;

    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
}

void asteroid::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { (int)x - size * BASE_ASTEROID_SIZE, (int)y - size * BASE_ASTEROID_SIZE, size * 2 * BASE_ASTEROID_SIZE, size * 2 * BASE_ASTEROID_SIZE };
    SDL_RenderDrawRect(renderer, &rect);
}

int asteroid::getSize() const {
    return size;
}

float asteroid::getX() const {
    return x;
}

float asteroid::getY() const {
    return y;
}
