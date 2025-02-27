#pragma once

class Asteroid {
private:
    float x, y;
    float velocityX, velocityY;
    int size;
public:
    Asteroid(float start_X, float start_Y, int start_Size);

    void update();

    void render(SDL_Renderer* renderer);

    void split();

    int getSize() const;

    float getX() const;

    float getY() const;
};
