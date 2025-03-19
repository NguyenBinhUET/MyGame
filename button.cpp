#include"button.h"
#include"helper.h"

button::button(float _x, float _y, float _w, float _h, string _text)
    :x(_x), y(_y), w(_w), h(_h), text(_text), clicked(0), hover(0) {
    texture = loadTexture(renderer, "");
    hoverTexture = loadTexture(renderer, "");
    clickedTexture = loadTexture(renderer, "");
}

button::~button() {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(hoverTexture);
    SDL_DestroyTexture(clickedTexture);
}
/*
void button::render() {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,  text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect destRect = {x, y, w, h};

    SDL_RenderCopy(renderer, textTexture, NULL, destRect);
    if(clicked) {
        //SDL_RenderCopy(renderer, clickedTexture, NULL, &destRect);
    }
    else if(hover) {
        //SDL_RenderCopy(renderer, hoverTexture, NULL, &destRect);
    }
    else {
        //SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
}
*/
