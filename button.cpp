#include"button.h"
#include"helper.h"

button::button(const float x, const float y)
    :clicked(0), hover(0) {
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
button::render(const float x, const float y, const int w, const int h) {
    SDL_Rect destRect = {x, y, w, h};
    if(clicked) {
        SDL_RenderCopy(renderer, clickedTexture, NULL, &destRect);
    }
    else if(hover) {
        SDL_RenderCopy(renderer, hoverTexture, NULL, &destRect);
    }
    else {
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
}
*/
