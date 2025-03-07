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

using namespace std;

class game {
private:
    background Background;
    sound Sound;
    TTF_Font* font;
    SDL_Renderer* renderer;

    Spaceship player;
    asteroids Asteroids;
    bullets Bullets;

    bool gameOver;
    bool isRunning;
    bool spacePressed = 0, thrusting = 0;

    int lives;
public:
    game(SDL_Renderer* renderer, TTF_Font* font);
    ~game();
    void init();
    void resetGame();

    //handle input
    void handleInputHold(const Uint8* keystate);
    void handleInputTap(const SDL_Event& event);

    void update();

    //check collision
    bool checkCollision1(Spaceship& s, Asteroid& a);
    bool checkCollision2(Bullet& b, Asteroid& a);

    //render
    void render();
    void renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player);
    void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score);

    //getter
    bool isOverGame() const {return gameOver;};
    int getScore() const { return player.getScore();};

    //setter
    void setGameOver(bool value) { gameOver = value;};
};

