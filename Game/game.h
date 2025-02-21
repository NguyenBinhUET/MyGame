#pragma once
#include<cmath>


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

//player
Spaceship player = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

//Bullet
std::vector<Bullet> bullets;

void updateBullets() {
    int n = bullets.size();
    for(int i = 0; i < n; i++) {
        bullets[i].update();
        if(!bullets[i].alive()) bullets.erase(bullets.begin() + i);
    }
}

void renderBullets() {
    for(auto& bullet : bullets) {
        bullet.render(renderer);
    }
}

//Asteroid
std::vector<Asteroid> asteroids;

void spawnAsteroid() {
    Asteroid asteroid = {rand() % SCREEN_WIDTH + 0.0f, rand() % SCREEN_HEIGHT + 0.0f, (rand() % 3 + 1)};
    asteroids.push_back(asteroid);
}

void splitASteroid(Asteroid& asteroid) {
    if(asteroid.getSize() == 1) return;
    float x = asteroid.getX(), y = asteroid.getY();
    int size = asteroid.getSize();
    Asteroid asteroid1 = {x, y, size - 1}, asteroid2 = {x, y, size - 1};
    asteroids.push_back(asteroid1);
    asteroids.push_back(asteroid2);
}

void updateAsteroids() {
    for (auto& asteroid : asteroids) {
        asteroid.update();
    }
}

void renderAsteroids() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (auto& asteroid : asteroids) {
       asteroid.render(renderer);
    }
}

//Handle input
bool spacePressed = 0;
void handlePlayerTap(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN)
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            if(!spacePressed) {
                bullets.push_back(player.spawnBullet());
                spacePressed = 1;
            }
        }
    }
    if(event.type == SDL_KEYUP) {
        if(spacePressed) spacePressed = 0;
    }
}

void handlePlayerHold(const Uint8* keystate) {
    if(keystate[SDL_SCANCODE_LEFT]) player.rotateLeft(5.0f);
    if(keystate[SDL_SCANCODE_RIGHT]) player.rotateRight(5.0f);
    if(keystate[SDL_SCANCODE_UP]) player.moveForward(BASE_SPEED);
}

//Handle collision
bool checkCollision1(Spaceship& s, Asteroid& a) {
    if(s.hasShield()) return 0;
    float sX = s.getX(), sY = s.getY(), aX = a.getX(), aY = a.getY();
    float sW = s.getWidth(), aW = a.getSize();

    float distance = sqrt((sX - aX) * (sX - aX) + (sY - aY) * (sY - aY));
    return distance < (sW / 2) + aW * 10;
}

bool checkCollision2(Bullet& b, Asteroid& a) {
    float bX = b.getX(), bY = b.getY(), aX = a.getX(), aY = a.getY();

    float aW = a.getSize();

    float distance = sqrt((bX - aX) * (bX - aX) + (bY - aY) * (bY - aY));

    return distance < aW * 10;
}
