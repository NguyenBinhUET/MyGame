#include"player.h"
#include"constant.h"
#include"helper.h"
#include<cmath>

Spaceship::Spaceship( SDL_Renderer* renderer, float _x, float _y)
    :x(_x), y(_y), angle(-90), velocityX(0), velocityY(0), shield(0), score(0), renderer(renderer) {
        texture = loadTexture(renderer, "textures/Ship_1.png");
        fireTexture = loadTexture(renderer, "textures/fire.png");
        shieldTexture = loadTexture(renderer, "textures/shield1.png");
    }

void Spaceship::update() {

    velocityX *= (1.0f - FRICTION);
    velocityY *= (1.0f - FRICTION);

    if(shield != 0) shield--;

    float speed = sqrt(velocityX * velocityX + velocityY * velocityY);
    if(speed > MAX_SPEED) {
        velocityX = velocityX * (MAX_SPEED / speed);
        velocityY = velocityY * (MAX_SPEED / speed);
    }

    x += velocityX;
    y += velocityY;

    if(x < 0) x = SCREEN_WIDTH;
    if(x > SCREEN_WIDTH) x = 0;
    if(y < 0) y = SCREEN_HEIGHT;
    if(y > SCREEN_HEIGHT) y = 0;

}

void Spaceship::render(SDL_Renderer* renderer, const bool& thrusting) {
    //render thrust
    if(thrusting) {
        float radians = angle * M_PI / 180.0f;
        float backX = x - cos(radians) * (height / 2);
        float backY = y - sin(radians) * (height / 2);
        SDL_Rect fireRect = {(int)backX - 5, (int)backY - 14, 14, 28};
        SDL_RenderCopyEx(renderer, fireTexture, NULL, &fireRect, angle + 90, NULL, SDL_FLIP_NONE);
    }
    //render player
    renderTextureSpin(renderer, texture, x - width / 2, y - height / 2, width + 5, height + 5, angle + 90);
    //render shield
    if(shield) renderTexture(renderer, shieldTexture, x - width / 2 - 10, y - height / 2 - 10, width + 25, height + 25);
}

void Spaceship::renderLives(SDL_Renderer* renderer, const int lives) {
    for(int i = 0; i < lives; i++) {
        renderTexture(renderer, texture, 10 + i * 40, 50, 35, 35);
    }
}


void Spaceship::rotateLeft(float degree) {
    angle -= degree;
}

void Spaceship::rotateRight(float degree) {
    angle += degree;
}

void Spaceship::moveForward(float moveAmount) {
    float radians = angle * M_PI/ 180.0f;
    velocityX += cos(radians) * moveAmount;
    velocityY += sin(radians) * moveAmount;
}

void Spaceship::respawn() {
    x = SCREEN_WIDTH / 2, y = SCREEN_HEIGHT / 2;
    velocityX = 0, velocityY = 0;
    shield = SHIELD_TIME;
}

bullet Spaceship::spawnBullet() {
    bullet Bullet = {x, y, angle, velocityX, velocityY};
    return Bullet;
}

void Spaceship::resetScore() {
    score = 0;
}

void Spaceship::addScore(const int amount) {
    score += amount;
}
