#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<vector>
#include<string>
#include"player.h"
#include"constant.h"
#include"bullet.h"
#include"asteroid.h"
#include"background.h"
#include"sound.h"
#include"helper.h"

using namespace std;

class game {
private:
    Spaceship player;
    background Background;
    sound Sound;
    TTF_Font* font;
    SDL_Renderer* renderer;

    vector<asteroid> asteroidsManager;
    vector<vector<SDL_Texture*>> asteroidTextures;
    int numOfAsteroids;
    int speedLevel;

    vector<bullet> bulletsManager;
    SDL_Texture* bulletTexture;

    bool gameOver;
    bool running;
    bool spacePressed = 0, thrusting = 0;

    int lives;

    //timer
    Uint32 startTime;
    int countedTime;

public:
    game(SDL_Renderer* renderer, TTF_Font* font);
    ~game();
    void init();
    void resetGame();

    void spawnAsteroid();
    void splitAsteroid(const int i);

    //handle input
    void handleInputHold(const Uint8* keystate);
    void handleInputTap(const SDL_Event& event);

    void update();

    //check collision
    bool checkCollision1(Spaceship& player, asteroid& Asteroid);
    bool checkCollision2(bullet& Bullet, asteroid& Asteroid);

    //render
    void render();
    void renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player);
    void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score);
    void renderTimer(SDL_Renderer* renderer, TTF_Font* font);

    //getter
    bool isOverGame() const {return gameOver;};
    int getScore() const { return player.getScore();};
    bool isRunning() const {return running;};

    //setter
    void setGameOver(const bool value) {gameOver = value;};
    void setRunning(const bool value) {running = value;};
};

