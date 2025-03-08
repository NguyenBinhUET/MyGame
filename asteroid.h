#pragma once
#include<vector>

using namespace std;

class asteroid {
private:
    float x, y;
    float velocityX, velocityY;
    int size;
    int speedLevel;
public:
    //init
    asteroid(float start_X, float start_Y, int start_Size, int start_speedLevel);

    void update();
    void render(SDL_Renderer* renderer);

    //setter
    void setSpeedLevel();

    //getter
    int getSize() const;
    float getX() const;
    float getY() const;
};
