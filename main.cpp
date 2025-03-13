#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"constant.h"
#include"player.h"
#include"asteroid.h"
#include"game.h"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

void gameLoop(game Game) {
    Game.init();
    SDL_Event event;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    while(Game.isRunning()) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) Game.setRunning(0);
            Game.handleInputTap(event);
        }
        Game.handleInputHold(keystate);
        Game.update();
        // Render everything
        Game.render();
        SDL_Delay(16); // ~60 FPS
    }
}


int main(int argc, char* argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) cout << "SDL_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(IMG_Init(IMG_INIT_PNG) == 0) cout << "IMG_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(TTF_Init() == -1) cout << "TTF_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(SDL_Init(SDL_INIT_AUDIO) < 0) cout << "SDL_Init failed. ERROR: " << SDL_GetError() << "\n";
    if(Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) cout << "SDL_Mixer failed. ERROR: " << SDL_GetError() << "\n";

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not open audio: " <<  Mix_GetError();
        return 1;
    }

    window = SDL_CreateWindow("Astroids Destroyer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("fonts/Nasa21.ttf", SCORE_FONT_SIZE);
    if(!font) cout << "TTF_OpenFont failed. ERROR: " << TTF_GetError() << "\n";

    game Game(renderer, font);
    srand(time(0));
    gameLoop(Game);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
