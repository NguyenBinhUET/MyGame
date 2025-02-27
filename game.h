#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include"player.h"
#include"bullet.h"
#include"asteroid.h"

class game {
private:
    Spaceship player;
    TTF_Font* font;
    SDL_Renderer* renderer;

    bool gameOver;
    int lives;
    void spawnAsteroid();
public:
    bool spacePressed = 0;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    game(SDL_Renderer* renderer, TTF_Font* font);
    ~game();
    void resetGame();
    void handleInputHold(const Uint8* keystate);
    void handleInputTap(const SDL_Event& event);
    void render();
    void update();

    bool isOverGame() const {return gameOver;};
    void setGameOver(bool value) { gameOver = value;};
    int getScore() const { return player.getScore();};

    bool checkCollision1(Spaceship& s, Asteroid& a);
    bool checkCollision2(Bullet& b, Asteroid& a);

    void splitAsteroid(Asteroid& asteroid);

    void renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player);
    void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score);
};

