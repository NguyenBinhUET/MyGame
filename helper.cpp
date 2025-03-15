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

void renderTexturePart(SDL_Renderer* renderer, SDL_Texture* texture, int xSrc, int ySrc, int wSrc, int hSrc, int xDest, int yDest, int wDest, int hDest) {
    SDL_Rect src;
    src.x = xSrc;
    src.y = ySrc;
    src.w = wSrc;
    src.h = hSrc;

    SDL_Rect dest;
    dest.x = xDest;
    dest.y = yDest;
    dest.w = wDest;
    dest.h = hDest;

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

/*
void renderText(SDL_Renderer* renderer, const string& s, const int& x, const int& y, const float& size, TTF_Font* font, SDL_Color* color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,  s.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect;
    textRect.w = textSurface->w * size;
    textRect.h = textSurface->h * size;
    textRect.x = x;
    textRect.y = y;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}
*/
