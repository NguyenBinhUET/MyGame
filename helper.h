#pragma once
#include<string>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& filePath);
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height);
void renderTextureSpin(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, float angle);
void renderTexturePart(SDL_Renderer* renderer, SDL_Texture* textur, int xSrt, int ySrt, int wSrt, int hSrt, int xDest, int yDest, int wDest, int hDest);
//void renderText(SDL_Renderer* renderer, const string& s, const int& x, const int& y, const float& size, TTF_Font* font);
