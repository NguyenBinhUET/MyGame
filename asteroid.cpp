#include<SDL.h>
#include"asteroid.h"
#include"constant.h"


Asteroid::Asteroid(float start_X, float start_Y, int start_Size, int start_speedLevel) :x(start_X), y(start_Y), size(start_Size), speedLevel(start_speedLevel) {
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

void asteroids::spawnAsteroid() {
    for(int i = 0; i < numOfAsteroids; i++) {
        Asteroid asteroid = {rand() % SCREEN_WIDTH + 0.0f, rand() % SCREEN_HEIGHT + 0.0f, (rand() % 2 + 2), 1};
        asteroidsManager.push_back(asteroid);
    }
}

void asteroids::splitAsteroid(Asteroid& asteroid) {
    if (asteroid.getSize() > 1) {
        for (int i = 0; i < 2; ++i) {
            float x = asteroid.getX(), y = asteroid.getY();
            int size = asteroid.getSize();
            Asteroid newAsteroids = {x, y, size - 1, 2};
            asteroidsManager.push_back(newAsteroids);
        }
    }
}

void asteroids::render(SDL_Renderer* renderer) {
    for(auto& asteroid : asteroidsManager) {
        asteroid.render(renderer);
    }
}

void asteroids::~Asteroids() {
    asteroidsManager.clear();
}
