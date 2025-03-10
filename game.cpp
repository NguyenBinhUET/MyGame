#include"game.h"
#include<iostream>
#include<cmath>

game::game(SDL_Renderer* renderer, TTF_Font* font)
    :player(SCREEN_WIDTH/2 + 0.0f,SCREEN_HEIGHT/2 +0.0f, renderer), Background(renderer, "textures/Blue.png"), font(font), renderer(renderer) {};

game::~game() {
    if (font) {
        TTF_CloseFont(font);
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            SDL_DestroyTexture(asteroidTextures[i][j]);
        }
        asteroidTextures[i].clear();
    }
    asteroidTextures.clear();
    SDL_DestroyTexture(bulletTexture);
}

void game::init() {
    running = 1;
    numOfAsteroids = START_ASTEROIDS;
    speedLevel = 1;

    //load asteroid textures
    for(int i = 0; i < 3; i++) {
        vector<SDL_Texture*> temp;
        for(int j = 0; j < 3; j++) {
            string fileName = "textures/asteroid" + to_string(i + 1) + "-" + to_string(j + 1) + ".png";
            temp.push_back(loadTexture(renderer, fileName.c_str()));
            if(temp[j] == nullptr) cout << "No input for: " << fileName << "\n";
        }
        asteroidTextures.push_back(temp);
        temp.clear();
    }

    //load bullet texture
    bulletTexture = loadTexture(renderer, "textures/beam1.png");

    Sound.loadAllSound();
    Sound.play("space-station.ogg", -1, 8, -1);
}

void game::resetGame() {
    //set timer
    startTime = SDL_GetTicks();
    countedTime = 0.0f;

    numOfAsteroids = START_ASTEROIDS;
    speedLevel = 1;

    gameOver = false;
    lives = START_LIFE_POINT;
    player.resetScore();
    player = Spaceship(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, renderer);

    asteroidsManager.clear();
    bulletsManager.clear();

    spawnAsteroid();
}

void game::handleInputHold(const Uint8* keystate) {
    if(!gameOver) {
        if(keystate[SDL_SCANCODE_LEFT]) player.rotateLeft(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_RIGHT]) player.rotateRight(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_UP]) {
            player.moveForward(BASE_SPEED);
        }
    }
    if(keystate[SDL_SCANCODE_SPACE] && gameOver) {
        resetGame();
    }
    if(keystate[SDL_SCANCODE_UP]) {
        if(!thrusting) {
            Sound.playFadeIn("thrust.ogg", -1, 8, 7, 300);
            thrusting = 1;
        }
    }
    else if(thrusting) {
        Mix_FadeOutChannel(7, 300);
        thrusting = 0;
    }
    if(keystate[SDL_SCANCODE_E] && gameOver) {
        running = 0;
    }
}

void game::handleInputTap(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN)
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            if(!spacePressed) {
                bulletsManager.push_back(player.spawnBullet());
                spacePressed = 1;
                Sound.play("shoot-laser.ogg", 0, 8, -1);
            }
        }
    }
    if(event.type == SDL_KEYUP) {
        if(spacePressed) spacePressed = 0;
    }
}

void game::update() {
    if (!gameOver) {
        //update timer
        Uint32 currentTime = SDL_GetTicks();
        countedTime = (currentTime - startTime) / 1000; // to second

        Background.update(0.016f);
        player.update();
        if(asteroidsManager.size() == 0) {
            numOfAsteroids = min(MAX_ASTEROIDS, START_ASTEROIDS + countedTime / 30);
            speedLevel = min(MAX_SPEED_LEVEL, START_SPEED_LEVEL + countedTime / 15);
            spawnAsteroid();
        }
        for(int i = asteroidsManager.size() - 1; i >= 0; i--) {
            //update asteroids
            asteroidsManager[i].update();
            if (checkCollision1(player, asteroidsManager[i])) {
                lives--;
                Sound.play("ship-explosion.ogg", 0, 32, -1);
                if (lives <= 0) {
                    gameOver = true;
                } else player.respawn();
                splitAsteroid(i);
                asteroidsManager.erase(asteroidsManager.begin() + i);
            }
        }
        //update bullets
        for(int i = bulletsManager.size() - 1; i >= 0; i--) {
            bulletsManager[i].update();
            if(!bulletsManager[i].alive()) bulletsManager.erase(bulletsManager.begin() + i);
        }

        for(int i = asteroidsManager.size() - 1; i >= 0 ; i--) {
            for(int j = bulletsManager.size() - 1; j >= 0; j--) {
                if (checkCollision2(bulletsManager[j], asteroidsManager[i])) {
                    splitAsteroid(i);
                    Sound.play("asteroids-explosion.ogg", 0, 32, -1);
                    player.addScore(asteroidsManager[i].getSize() * BASE_SCORE);
                    asteroidsManager.erase(asteroidsManager.begin() + i);
                    bulletsManager.erase(bulletsManager.begin() + j);
                    break;
                }
            }
        }
    }
}

void game::splitAsteroid(const int i) {
    int size = asteroidsManager[i].getSize();
    float x = asteroidsManager[i].getX(), y = asteroidsManager[i].getY();
    if (size > 1) {
        for (int j = 0; j < 2; ++j) {
            asteroid newAsteroids = {x, y, size - 1, 2};
            asteroidsManager.push_back(newAsteroids);
        }
    }
}

void game::spawnAsteroid() {
    for(int i = 0; i < numOfAsteroids; i++) {
        int f = rand() % 2;
        if(f) {
            asteroid newAsteroid = {0, rand() % SCREEN_HEIGHT + 0.0f, (rand() % 2 + 2), 1};
            asteroidsManager.push_back(newAsteroid);
        }
        else {
            asteroid newAsteroid = {rand() % SCREEN_WIDTH + 0.0f, 0, (rand() % 2 + 2), 1};
            asteroidsManager.push_back(newAsteroid);
        }
    }
}

bool game::checkCollision1(Spaceship& player, asteroid& Asteroid) {
    float distance = sqrt(pow(player.getX() - Asteroid.getX(), 2) + pow(player.getY() - Asteroid.getY(), 2));
    return distance < (player.getWidth() / 2 + Asteroid.getSize() * BASE_ASTEROID_SIZE);
}

bool game::checkCollision2(bullet& Bullet, asteroid& Asteroid) {
    float distance = sqrt(pow(Bullet.getX() - Asteroid.getX(), 2) + pow(Bullet.getY() - Asteroid.getY(), 2));
    return distance < (1 + Asteroid.getSize() * BASE_ASTEROID_SIZE);
}

void game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (!gameOver) {
        Background.render();
        player.render(renderer);
        //render asteroids
        for(auto& asteroid : asteroidsManager) {
            int size = asteroid.getSize(), x = asteroid.getX() - size * BASE_ASTEROID_SIZE , y = asteroid.getY() -  size * BASE_ASTEROID_SIZE;
            renderTextureSpin(renderer, asteroidTextures[size - 1][asteroid.getIndex()], x, y, 2 * size * BASE_ASTEROID_SIZE, 2 * size * BASE_ASTEROID_SIZE, asteroid.getAngle());
        }

        //render bullets
        for(auto& bullet : bulletsManager) {
            renderTextureSpin(renderer, bulletTexture, bullet.getX() - 9, bullet.getY() - 18, 22, 40, bullet.getAngle() + 90);
        }

        renderScore(renderer, font, player);
        renderTimer(renderer, font);
    }
    else renderGameOver(renderer, font, player.getScore());

    SDL_RenderPresent(renderer);
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

void game::renderTimer(SDL_Renderer* renderer, TTF_Font* font) {
    string minute = to_string(countedTime / 60), second = to_string(countedTime % 60);
    if(minute.size() < 2) minute = "0" + minute;
    if(second.size() < 2) second = "0" + second;
    string timerToRender = minute + ":" + second;
    SDL_Color red = {255, 0, 0, 255};
    SDL_Surface* timerSurface = TTF_RenderText_Solid(font, timerToRender.c_str(), red);
    SDL_Texture* timerTexture = SDL_CreateTextureFromSurface(renderer, timerSurface);

    SDL_Rect timerRect;
    timerRect.w = timerSurface->w;
    timerRect.h = timerSurface->h;
    timerRect.x = (SCREEN_WIDTH - timerRect.w - 10);
    timerRect.y = 10;

    SDL_RenderCopy(renderer, timerTexture, NULL, &timerRect);

    SDL_DestroyTexture(timerTexture);
    SDL_FreeSurface(timerSurface);

}
