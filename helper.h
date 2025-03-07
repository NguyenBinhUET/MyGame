#pragma once
#include<string>
#include<SDL.h>
#include<SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath);
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height);

