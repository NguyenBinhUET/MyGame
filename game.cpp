#include"game.h"
#include<iostream>
#include<cmath>

game::game(SDL_Renderer* renderer, TTF_Font* font) :player(SCREEN_WIDTH/2,SCREEN_HEIGHT/2),lives(START_LIFE_POINT), renderer(renderer), font(font){};

game::~game() {
    if (font) {
        TTF_CloseFont(font);
    }
}

void game::handleInputHold(const Uint8* keystate) {
    if (!gameOver) {
        if(keystate[SDL_SCANCODE_LEFT]) player.rotateLeft(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_RIGHT]) player.rotateRight(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_UP]) player.moveForward(BASE_SPEED);
    }
    if (keystate[SDL_SCANCODE_SPACE] && gameOver) {
        resetGame();
    }
}

void game::handleInputTap(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN)
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            if(!spacePressed) {
                bullets.push_back(player.spawnBullet());
                spacePressed = 1;
            }
        }
    }
    if(event.type == SDL_KEYUP) {
        if(spacePressed) spacePressed = 0;
    }
}

void game::update() {
    if (!gameOver) {
        player.update();
        for(int i = 0; i < asteroids.size(); i++) {
            //update asteroids
            asteroids[i].update();
            if (checkCollision1(player, asteroids[i])) {
                lives--;
                if (lives <= 0) {
                    gameOver = true;
                } else player.respawn();
                splitAsteroid(asteroids[i]);
                asteroids.erase(asteroids.begin() + i);
            }
        }
        //update bullets
        for(int i = 0; i < bullets.size(); i++) {
            bullets[i].update();
            if(!bullets[i].alive()) bullets.erase(bullets.begin() + i);
        }
        for(int i = 0; i < asteroids.size(); i++) {
            for(int j = 0; j < bullets.size(); j++) {
                if (checkCollision2(bullets[j], asteroids[i])) {
                    splitAsteroid(asteroids[i]);
                    asteroids.erase(asteroids.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    player.addScore(BASE_SCORE);
                }
            }
        }
    }
}

void game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (!gameOver) {
        player.render(renderer);

        for (auto& asteroid : asteroids) {
            asteroid.render(renderer);
        }

        for (auto& bullet : bullets) {
            bullet.render(renderer);
        }

        renderScore(renderer, font, player);
    }
    else renderGameOver(renderer, font, player.getScore());

    SDL_RenderPresent(renderer);
}

void game::spawnAsteroid() {
    Asteroid asteroid = {rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 3 + 1)};
    asteroids.push_back(asteroid);
}

void game::resetGame() {
    gameOver = false;
    lives = 3;
    player.resetScore();
    player = Spaceship(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    asteroids.clear();

    for (int i = 0; i < 5; ++i) {
        spawnAsteroid();
    }
}

bool game::checkCollision1(Spaceship& player, Asteroid& asteroid) {
    float distance = sqrt(pow(player.getX() - asteroid.getX(), 2) + pow(player.getY() - asteroid.getY(), 2));
    return distance < (player.getWidth() / 2 + asteroid.getSize() * BASE_ASTEROID_SIZE);
}

bool game::checkCollision2(Bullet& bullet, Asteroid& asteroid) {
    float distance = sqrt(pow(bullet.getX() - asteroid.getX(), 2) + pow(bullet.getY() - asteroid.getY(), 2));
    return distance < (1 + asteroid.getSize() * BASE_ASTEROID_SIZE);
}

void game::splitAsteroid(Asteroid& asteroid) {
    if (asteroid.getSize() > 1) {
        for (int i = 0; i < 2; ++i) {
            float x = asteroid.getX(), y = asteroid.getY();
            int size = asteroid.getSize();
            Asteroid newAsteroid = {x, y, size - 1};
            asteroids.push_back(newAsteroid);
        }
    }
}

void game::renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player) {
    std::string s = "Score: " + std::to_string(player.getScore());
    const char* scoreToDisplay = s.c_str();
    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreToDisplay, white);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect;
    destRect.x = 10;
    destRect.y = 10;
    destRect.w = surface->w;
    destRect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void game::renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score) {
    std::string gameOverText = "Game Over";
    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(font, gameOverText.c_str(), white);
    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Rect gameOverRect;
    gameOverRect.w = gameOverSurface->w;
    gameOverRect.h = gameOverSurface->h;
    gameOverRect.x = (SCREEN_WIDTH - gameOverRect.w) / 2;
    gameOverRect.y = (SCREEN_HEIGHT - gameOverRect.h) / 2 - 50;

    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect scoreRect;
    scoreRect.w = scoreSurface->w;
    scoreRect.h = scoreSurface->h;
    scoreRect.x = (SCREEN_WIDTH - scoreRect.w) / 2;
    scoreRect.y = (SCREEN_HEIGHT - scoreRect.h) / 2 + 50;

    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

    SDL_DestroyTexture(gameOverTexture);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_FreeSurface(scoreSurface);
}
