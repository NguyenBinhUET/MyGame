#include"player.h"
#include"constant.h"
#include"helper.h"
#include<cmath>

Spaceship::Spaceship(float start_x, float start_y, SDL_Renderer* renderer)
    :x(start_x), y(start_y), angle(-90), velocityX(0), velocityY(0), shield(0), score(0), renderer(renderer) {
        texture = loadTexture(renderer,"textures/Ship_1.png");
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

void Spaceship::render(SDL_Renderer* renderer) {
    renderTextureSpin(renderer, texture, x - width / 2, y - height / 2, width + 5, height + 5, angle + 90);
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
