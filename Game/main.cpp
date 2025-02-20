#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<SDL.h>
#include<SDL_image.h>

#include"constant.h"
#include"player.h"
#include"astroid.h"
#include"game.h"

bool isRunning = 1;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Spaceship player = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

void handlePlayerInput(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_LEFT]) player.rotateLeft(5.0f); // Rotate left
    if (keystate[SDL_SCANCODE_RIGHT]) player.rotateRight(5.0f); // Rotate right
    if (keystate[SDL_SCANCODE_UP]) {
        // Apply thrust in the direction of the angle
        player.moveForward(BASE_SPEED);
    }
}

std::vector<Asteroid> asteroids;

void spawnAsteroid() {
    Asteroid asteroid = {rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 3 + 1)};
    asteroids.push_back(asteroid);
}

void updateAsteroids() {
    for (auto& asteroid : asteroids) {
        asteroid.update();
    }
}

void renderAsteroids() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (auto& asteroid : asteroids) {
       asteroid.render(renderer);
    }
}


void gameLoop() {
    SDL_Event event;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Spawn initial asteroids
    for (int i = 0; i < 5; i++) spawnAsteroid();

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        for(auto& asteroid : asteroids) {
            if(checkCollision(player, asteroid)) {
                isRunning = 0;
            }
        }

        handlePlayerInput(keystate);
        player.update();
        updateAsteroids();

        // Render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        player.render(renderer);
        renderAsteroids();
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }
}


int main(int argc, char* argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(!SDL_Init(IMG_INIT_PNG)) std::cout << "IMG_Init failed. ERROR: " << SDL_GetError() << "\n";

    window = SDL_CreateWindow("AStroids Destroyer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));
    gameLoop();
    return 0;
}
