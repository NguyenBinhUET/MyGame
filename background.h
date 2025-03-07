#pragma once
#include"helper.h"
#include<SDL.h>

class background {
private:
    SDL_Texture* texture;
    float scrollX;
    float scrollSpeed;
    int backgroundWidth;
    int backgroundHeight;
    SDL_Renderer* renderer;
public:
    background(SDL_Renderer* renderer, const std::string& texturePath);
    ~background();

    void update(float deltaTime);
    void render();

};

