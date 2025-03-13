#pragma once
#include"constant.h"
#include"bullet.h"
#include<SDL.h>

class Spaceship {
private:
    float x, y;
    float angle;
    float velocityX, velocityY;
    int width = 40, height = 40;
    int shield;
    int score;
    SDL_Texture* texture;
    SDL_Texture* fireTexture;
    SDL_Texture* shieldTexture;
    SDL_Renderer* renderer;
public:
    //init
    Spaceship(float start_x, float start_y, SDL_Renderer* renderer);

    void update();
    void render(SDL_Renderer* renderer, const bool& thrusting);
    void renderLives(SDL_Renderer* renderer, const int lives);

    //movements
    void rotateLeft(float degree);
    void rotateRight(float degree);
    void moveForward(float moveAmount);

    //getter
    float getX() const {return x;};
    float getY() const {return y;};
    int getWidth() const {return width;};
    int getScore() const {return score;};
    bool hasShield() {return shield;};


    void respawn();


    bullet spawnBullet();

    void resetScore();
    void addScore(const int amount);
};
