#pragma once
#include<vector>

using namespace std;

class Asteroid {
private:
    float x, y;
    float velocityX, velocityY;
    int size;
    int speedLevel;
public:
    //init
    Asteroid(float start_X, float start_Y, int start_Size, int start_speedLevel);
    //destruct
    ~Asteroid();

    void update();
    void render(SDL_Renderer* renderer);

    //setter
    void setSpeedLevel();

    //getter
    int getSize() const;
    float getX() const;
    float getY() const;
};

class asteroids {
private:
    vector<Asteroid> asteroidsManager;
    int numOfAsteroids;
    int speedLevel;
public:
    //destruct
    ~asteroids();

    void splitAsteroid(Asteroid& asteroid);
    void spawnAsteroid();

    void render(SDL_Renderer* renderer);
};
