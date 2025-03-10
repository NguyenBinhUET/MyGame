#include"helper.h"
#include<SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void renderTextureSpin(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, float angle) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    SDL_Point center;
    center.x = w / 2;
    center.y = h / 2;

    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);
}
