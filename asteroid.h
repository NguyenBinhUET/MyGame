#pragma once
#include<vector>

using namespace std;

class asteroid {
private:
    float x, y;
    float angle, rotationSpeed;
    float velocityX, velocityY;
    int size;
    int speedLevel;
    int textureIndex;
public:
    //init
    asteroid(float _x, float _y, int _size, int _speedLevel);

    void update();
    void render(SDL_Renderer* renderer);

    //setter
    void setSpeedLevel();

    //getter
    int getSize() const {return size;};
    float getX() const {return x;};
    float getY() const {return y;};
    int getIndex() const {return textureIndex;};
    float getAngle() const {return angle;};
};
