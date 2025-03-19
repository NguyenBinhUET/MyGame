#pragma once
#include<SDL.h>
#include<string>

using namespace std;

class button {
private:
    float x, y, w, h;
    string text;
    bool clicked, hover;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    SDL_Texture* clickedTexture;
    SDL_Renderer* renderer;
public:
    button(float _x, float _y, float _w, float _h, string _text);
    ~button();

    //getter
    bool isClicked() const {return clicked;};
    bool isHover() const {return hover;};

    //setter
    void setClicked(const bool value) {clicked = value;};
    void setHover(const bool value) {hover = value;};

    void render();
};
