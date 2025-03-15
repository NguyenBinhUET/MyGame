#pragma once
#include<SDL.h>
#include<vector>

using namespace std;

class explosion {
private:
    float x, y;
    int size;
    int currentFrame;
    int totalFrames;
    float frameDuration;
    float timer;
    bool alive;
public:
    explosion(float _x, float _y, int _size);

    void update();

    //getter
    bool isAlive() const {return alive;};
    float getX() const {return x;};
    float getY() const {return y;};
    int getSize() const {return size;};
    int getCurrentFrame() const {return currentFrame;};
};
