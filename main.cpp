#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<SDL.h>
#include<SDL_image.h>

#include"constant.h"
#include"player.h"
#include"asteroid.h"
#include"game.h"

bool isRunning = 1;

void gameLoop() {
    SDL_Event event;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Spawn initial asteroids
    for (int i = 0; i < 10 ; i++) spawnAsteroid();

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
            handlePlayerTap(event);
        }
        int k = asteroids.size();
        for(int i = 0; i < k; i++) {
            if(checkCollision1(player, asteroids[i])) {
                player.respawn();
                int currentLifePoint = player.getLifePoint();
                player.changeLifePoint(currentLifePoint - 1);
                if(currentLifePoint == 0) isRunning = 0;

                splitASteroid(asteroids[i]);
                asteroids.erase(asteroids.begin() + i);
            }
            for(auto& bullet : bullets) {
                if(checkCollision2(bullet, asteroids[i])) {
                    splitASteroid(asteroids[i]);
                    asteroids.erase(asteroids.begin() + i);
                }
            }
        }

        handlePlayerHold(keystate);
        player.update();
        updateAsteroids();
        updateBullets();

        // Render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        player.render(renderer);
        renderAsteroids();
        renderBullets();
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }
}


int main(int argc, char* argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "SDL_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(SDL_Init(IMG_INIT_PNG) > 0) std::cout << "IMG_Init failed. ERROR: " << SDL_GetError() << "\n";

    window = SDL_CreateWindow("Astroids Destroyer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));
    gameLoop();
    return 0;
}
