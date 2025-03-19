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
#include"UFO.h"
#include"explosion.h"
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

    vector<UFO> ufosManager;
    SDL_Texture* ufoTexture;

    vector<asteroid> asteroidsManager;
    vector<vector<SDL_Texture*>> asteroidTextures;
    int numOfAsteroids;
    int speedLevel;

    vector<bullet> bulletsManager;
    SDL_Texture* bulletTexture;

    vector<bullet> ufoBulletsManager;
    SDL_Texture* ufoBulletTexture;

    vector<explosion> explosionsManager;
    SDL_Texture* explosionFrames;

    bool gameOver;
    bool running;
    bool inMenu;
    bool paused;
    bool spacePressed = 0, thrusting = 0;
    bool hasUFO;

    unsigned long highestScore;
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
    void spawnUFO();
    void splitAsteroid(const int i);

    //handle input
    void handleInputHold(const Uint8* keystate);
    void handleInputTap(const SDL_Event& event);

    void update();

    //check collision
    bool checkCollision1(Spaceship& player, asteroid& Asteroid);
    bool checkCollision2(bullet& Bullet, asteroid& Asteroid);
    bool checkCollision3(UFO& ufo, bullet& Bullet);
    bool checkCollision4(Spaceship& player, bullet& Bullet);

    //render
    void render();
    void renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player);
    void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score);
    void renderTimer(SDL_Renderer* renderer, TTF_Font* font);
    void renderDarkBackground();
    void renderStartMenu();
    void renderPaused();

    //getter
    bool isOverGame() const {return gameOver;};
    int getScore() const { return player.getScore();};
    bool isRunning() const {return running;};
    bool isInMenu() const {return inMenu;};

    //setter
    void setGameOver(const bool value) {gameOver = value;};
    void setRunning(const bool value) {running = value;};
};

