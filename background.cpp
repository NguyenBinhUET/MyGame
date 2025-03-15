#include"background.h"
#include"constant.h"
#include<SDL_image.h>
#include<iostream>
#include<cmath>


background::background(SDL_Renderer* renderer, const std::string& texturePath)
    :renderer(renderer), scrollX(0.0f), scrollSpeed(SCROLL_SPEED) {
    texture = loadTexture(renderer, texturePath);
}

background::~background() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void background::update() {
    scrollX -= scrollSpeed * 0.016f;

    SDL_QueryTexture(texture, NULL, NULL, &backgroundWidth, &backgroundHeight);

    if (scrollX < -backgroundWidth) {
        scrollX += backgroundWidth;
    }
}

void background::render() {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = (int)-scrollX;
    srcRect.y = 0;
    srcRect.w = SCREEN_WIDTH + (int)scrollX;
    srcRect.h = backgroundHeight;

    destRect.x = 0;
    destRect.y = 0;
    destRect.w = SCREEN_WIDTH + (int)scrollX;
    destRect.h = backgroundHeight;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

    // Second part for wrapping

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = backgroundWidth - (int)scrollX;
    srcRect.h = backgroundHeight;

    destRect.x = SCREEN_WIDTH + (int)scrollX;
    destRect.y = 0;
    destRect.w = backgroundWidth;
    destRect.h = backgroundHeight;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
