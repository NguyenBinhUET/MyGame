#include<SDL.h>
#include"asteroid.h"
#include"constant.h"


Asteroid::Asteroid(float start_X, float start_Y, int start_Size) :x(start_X), y(start_Y), size(start_Size) {
        velocityX = (rand() % 5 - 2) / 2.0f + 0.1f;
        velocityY = (rand() % 5 - 2) / 2.0f + 0.1f;
};
void Asteroid::update()  {

    x += velocityX;
    y += velocityY;

    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;
}

void Asteroid::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { (int)x - size * BASE_ASTEROID_SIZE, (int)y - size * BASE_ASTEROID_SIZE, size * 2 * BASE_ASTEROID_SIZE, size * 2 * BASE_ASTEROID_SIZE };
    SDL_RenderDrawRect(renderer, &rect);
}

int Asteroid::getSize() const {
    return size;
}

float Asteroid::getX() const {
    return x;
}

float Asteroid::getY() const {
    return y;
}
