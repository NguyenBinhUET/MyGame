#include"player.h"
#include"constant.h"
#include<cmath>

Spaceship::Spaceship(float start_x, float start_y)
    :x(start_x), y(start_y), angle(0), velocityX(0), velocityY(0), shield(0), score(0) {}

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
// Draw spaceship as a triangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    float radians = angle * M_PI / 180.0f;

    SDL_Point points[4];
    points[0] = { (int)(x + cos(radians) * width / 2),
                  (int)(y + sin(radians) * height / 2) }; // Nose
    points[1] = { (int)(x + cos(radians + BASE_PLAYER_ANGLE) * width / 2),
                  (int)(y + sin(radians + BASE_PLAYER_ANGLE) * height / 2) }; // Left wing
    points[2] = { (int)(x + cos(radians - BASE_PLAYER_ANGLE) * width / 2),
                  (int)(y + sin(radians - BASE_PLAYER_ANGLE) * height / 2) }; // Right wing
    points[3] = points[0];

    SDL_RenderDrawLines(renderer, points, 4);
}

void Spaceship::setAngle(float newAngle) {
    angle = newAngle;
}

void Spaceship::rotateLeft(float degree) {
    setAngle(angle - degree);
}

void Spaceship::rotateRight(float degree) {
    setAngle(angle + degree);
}

void Spaceship::moveForward(float moveAmount) {
    float radians = angle * M_PI/ 180.0f;
    velocityX += cos(radians) * moveAmount;
    velocityY += sin(radians) * moveAmount;
}

float Spaceship::getX() const {
    return x;
}

float Spaceship::getY() const {
    return y;
}

int Spaceship::getWidth() const {
    return width;
}

void Spaceship::respawn() {
    x = SCREEN_WIDTH / 2, y = SCREEN_HEIGHT / 2;
    velocityX = 0, velocityY = 0;
    shield = SHIELD_TIME;
}

bool Spaceship::hasShield() {
    return shield;
}

Bullet Spaceship::spawnBullet() {
    Bullet bullet = {x, y, angle, velocityX, velocityY};
    return bullet;
}

void Spaceship::resetScore() {
    score = 0;
}

int Spaceship::getScore() const {
    return score;
}

void Spaceship::addScore(const int amount) {
    score += amount;
}
