#pragma once

class Asteroid {
private:
    float x, y;
    float velocityX, velocityY;
    int size;
public:
    Asteroid(float start_X, float start_Y, int start_Size) :x(start_X), y(start_Y), size(start_Size) {
        x = rand() % SCREEN_WIDTH;
        y = rand() % SCREEN_HEIGHT;
        size = rand() % 3 + 1;
        velocityX = (rand() % 5 - 2) / 2.0f + 0.1f;
        velocityY = (rand() % 5 - 2) / 2.0f + 0.1f;
    };
    void update() {
        x += velocityX;
        y += velocityY;

        if(x < 0) x = SCREEN_WIDTH;
        if(x > SCREEN_WIDTH) x = 0;
        if(y < 0) y = SCREEN_HEIGHT;
        if(y > SCREEN_HEIGHT) y = 0;
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect = { (int)x - size * 10, (int)y - size * 10, size * 20, size * 20 };
        SDL_RenderDrawRect(renderer, &rect);
    }

    int getSize() const {
        return size;
    }
    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
};
