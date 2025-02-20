#pragma once
#include<SDL.h>

class Spaceship {
private:
    float x, y;
    float angle;
    float velocityX, velocityY;
    int width = 30, height = 30;
    float lifePoint = START_LIFE_POINT;
public:
    Spaceship(float start_x, float start_y) :x(start_x), y(start_y), angle(0), velocityX(0), velocityY(0) {}

    void update() {

        velocityX *= (1.0f - FRICTION);
        velocityY *= (1.0f - FRICTION);

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

    void render(SDL_Renderer* renderer) {
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

    void setAngle(float newAngle) {
        angle = newAngle;
    }

    void rotateLeft(float degree) {
        setAngle(angle - degree);
    }

    void rotateRight(float degree) {
        setAngle(angle + degree);
    }

    void moveForward(float moveAmount) {
        float radians = angle * M_PI/ 180.0f;
        velocityX += cos(radians) * moveAmount;
        velocityY += sin(radians) * moveAmount;
    }

    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
    int getWidth() const {
        return width;
    }
};
