#pragma once
#include<SDL.h>

class button {
private:
    float x, y, w, h;
    bool clicked, hover;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    SDL_Texture* clickedTexture;
    SDL_Renderer* renderer;
public:
    button(const float x, const float y);
    ~button();

    //getter
    bool isClicked() const {return clicked;};
    bool isHover() const {return hover;};

    //setter
    void setClicked(const bool value) {clicked = value;};
    void setHover(const bool value) {hover = value;};

    void render();
};
