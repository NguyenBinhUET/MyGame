#pragma once
#include"helper.h"
#include<SDL.h>

using namespace std;

class background {
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    float scrollX;
    float scrollSpeed;
    int backgroundWidth;
    int backgroundHeight;
public:
    background(SDL_Renderer* renderer, const string& texturePath);
    ~background();

    void update();
    void render();

};

