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
    inMenu = 1;
    gameOver = 0;

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
    Sound.play("space-station.ogg", -1, 16, -1);
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
    if(!gameOver && !inMenu) {
        if(keystate[SDL_SCANCODE_LEFT]) player.rotateLeft(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_RIGHT]) player.rotateRight(BASE_ROTATE);
        if(keystate[SDL_SCANCODE_UP]) {
            player.moveForward(BASE_SPEED);
        }
        if(keystate[SDL_SCANCODE_UP]) {
            if(!thrusting && !gameOver) {
                Sound.playFadeIn("thrust.ogg", -1, 16, 7, 300);
                thrusting = 1;
            }
        }
        else if(thrusting || gameOver) {
            Mix_FadeOutChannel(7, 300);
            thrusting = 0;
        }
    }
    else if(gameOver) {
        if(keystate[SDL_SCANCODE_TAB]) {
            resetGame();
        }
        if(keystate[SDL_SCANCODE_E]) {
            running = 0;
        }
    }

}

void game::handleInputTap(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN)
    switch(event.key.keysym.sym) {
        case SDLK_SPACE:
            if(!spacePressed && !gameOver && !inMenu) {
                bulletsManager.push_back(player.spawnBullet());
                spacePressed = 1;
                Sound.play("shoot-laser.ogg", 0, 16, -1);
            }
            break;
        case SDLK_RETURN:
            if(inMenu) resetGame();
            inMenu = 0;
            break;
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
            if (!player.hasShield() && checkCollision1(player, asteroidsManager[i]) && !inMenu) {
                lives--;
                Sound.play("ship-explosion.ogg", 0, 48, -1);
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
            asteroid newAsteroid = {0, rand() % SCREEN_HEIGHT + 0.0f, (rand() % 2 + 2), speedLevel};
            asteroidsManager.push_back(newAsteroid);
        }
        else {
            asteroid newAsteroid = {rand() % SCREEN_WIDTH + 0.0f, 0, (rand() % 2 + 2), speedLevel};
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


    Background.render();
    if(inMenu) {
        renderStartMenu();
    }
    if (!gameOver) {
        if(!inMenu) {
            player.render(renderer, thrusting);
            renderScore(renderer, font, player);
            renderTimer(renderer, font);
            player.renderLives(renderer, lives);
        }
        //render asteroids
        for(auto& asteroid : asteroidsManager) {
            int size = asteroid.getSize(), x = asteroid.getX() - size * BASE_ASTEROID_SIZE , y = asteroid.getY() -  size * BASE_ASTEROID_SIZE;
            renderTextureSpin(renderer, asteroidTextures[size - 1][asteroid.getIndex()], x, y, 2 * size * BASE_ASTEROID_SIZE, 2 * size * BASE_ASTEROID_SIZE, asteroid.getAngle());
        }

        //render bullets
        for(auto& bullet : bulletsManager) {
            renderTextureSpin(renderer, bulletTexture, bullet.getX() - 9, bullet.getY() - 18, 22, 40, bullet.getAngle() + 90);
        }

    }
    else {
        renderDarkBackground();
        renderGameOver(renderer, font, player.getScore());
    }

    SDL_RenderPresent(renderer);
}


void game::renderScore(SDL_Renderer* renderer, TTF_Font* font, Spaceship& player) {
    std::string s = "Score: " + std::to_string(player.getScore());
    const char* scoreToDisplay = s.c_str();
    //render outline
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* outlineSurface = TTF_RenderText_Solid(font, scoreToDisplay, black);
    SDL_Texture* outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
    SDL_Rect outlineDestRect = {10, 10, (int)(outlineSurface->w * 1.5f) + 5, (int)(outlineSurface->h * 1.5f) + 5};
    SDL_RenderCopy(renderer, outlineTexture, NULL, &outlineDestRect);

    //render score
    SDL_Color white = {255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreToDisplay, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {10, 10, (int)(surface->w * 1.5f), (int)(surface->h * 1.5f)};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);





    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(outlineTexture);
    SDL_FreeSurface(outlineSurface);
}

void game::renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int score) {
    std::string gameOverText = "Game Over";
    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Color white = { 255, 255, 255, 255 };

    //render game over text
    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(font, gameOverText.c_str(), white);
    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Rect gameOverRect;
    gameOverRect.w = gameOverSurface->w * 2;
    gameOverRect.h = gameOverSurface->h * 2;
    gameOverRect.x = (SCREEN_WIDTH - gameOverRect.w) / 2;
    gameOverRect.y = (SCREEN_HEIGHT - gameOverRect.h) / 2 - 50;

    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);

    //render score
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect scoreRect;
    scoreRect.w = scoreSurface->w;
    scoreRect.h = scoreSurface->h;
    scoreRect.x = (SCREEN_WIDTH - scoreRect.w) / 2;
    scoreRect.y = (SCREEN_HEIGHT - scoreRect.h) / 2 + 50;

    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

    //render button
    string buttonText = "Press [E] to exit or [TAB] to play again.";

    SDL_Surface* buttonSurface = TTF_RenderText_Solid(font, buttonText.c_str(), white);
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);

    SDL_Rect buttonRect;
    buttonRect.w = buttonSurface->w;
    buttonRect.h = buttonSurface->h;
    buttonRect.x = (SCREEN_WIDTH - buttonRect.w) / 2;
    buttonRect.y = (SCREEN_HEIGHT - buttonRect.h) / 2 + 200;

    SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

    //render time survived
    string minute = to_string(countedTime / 60), second = to_string(countedTime % 60);
    if(minute.size() < 2) minute = "0" + minute;
    if(second.size() < 2) second = "0" + second;
    string timeSurvived = "Time: " + minute + ":" + second;

    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, timeSurvived.c_str(), white);
    SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);

    SDL_Rect timeRect;
    timeRect.w = timeSurface->w;
    timeRect.h = buttonSurface->h;
    timeRect.x = (SCREEN_WIDTH - timeRect.w) / 2;
    timeRect.y = (SCREEN_HEIGHT - timeRect.h) / 2 + 100;

    SDL_RenderCopy(renderer, timeTexture, NULL, &timeRect);

    SDL_DestroyTexture(gameOverTexture);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(buttonTexture);
    SDL_FreeSurface(buttonSurface);
    SDL_DestroyTexture(timeTexture);
    SDL_FreeSurface(timeSurface);

}

void game::renderTimer(SDL_Renderer* renderer, TTF_Font* font) {
    string minute = to_string(countedTime / 60), second = to_string(countedTime % 60);
    if(minute.size() < 2) minute = "0" + minute;
    if(second.size() < 2) second = "0" + second;
    string timerToRender = minute + ":" + second;

    //render outline
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* outlineSurface = TTF_RenderText_Solid(font, timerToRender.c_str(), black);
    SDL_Texture* outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
    SDL_Rect outlineDestRect;
    outlineDestRect.w = outlineSurface->w * 1.5f - 5;
    outlineDestRect.h = outlineSurface->h * 1.5f + 5;
    outlineDestRect.x = SCREEN_WIDTH - outlineDestRect.w - 10;
    outlineDestRect.y = 10;
    SDL_RenderCopy(renderer, outlineTexture, NULL, &outlineDestRect);


    //render timer
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* timerSurface = TTF_RenderText_Solid(font, timerToRender.c_str(), white);
    SDL_Texture* timerTexture = SDL_CreateTextureFromSurface(renderer, timerSurface);

    SDL_Rect timerRect;
    timerRect.w = timerSurface->w * 1.5f;
    timerRect.h = timerSurface->h * 1.5f;
    timerRect.x = SCREEN_WIDTH - timerRect.w - 10;
    timerRect.y = 10;
    SDL_RenderCopy(renderer, timerTexture, NULL, &timerRect);

    SDL_DestroyTexture(timerTexture);
    SDL_FreeSurface(timerSurface);
    SDL_DestroyTexture(outlineTexture);
    SDL_FreeSurface(outlineSurface);

}

void game::renderDarkBackground() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &screenRect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void game::renderStartMenu() {
    SDL_Color white = { 255, 255, 255, 255 };

    string nameText = "ASTEROIDS DESTROYER";

    SDL_Surface* nameSurface = TTF_RenderText_Solid(font, nameText.c_str(), white);
    SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);

    SDL_Rect nameRect;
    nameRect.w = nameSurface->w * 2;
    nameRect.h = nameSurface->h * 2;
    nameRect.x = (SCREEN_WIDTH - nameRect.w) / 2;
    nameRect.y = (SCREEN_HEIGHT - nameRect.h) / 2 - 100;

    SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);

    string buttonText = "Press [SPACE] to shoot, move with [LEFT] [UP] [RIGHT]";

    SDL_Surface* buttonSurface = TTF_RenderText_Solid(font, buttonText.c_str(), white);
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);

    SDL_Rect buttonRect;
    buttonRect.w = buttonSurface->w;
    buttonRect.h = buttonSurface->h;
    buttonRect.x = (SCREEN_WIDTH - buttonRect.w) / 2;
    buttonRect.y = (SCREEN_HEIGHT - buttonRect.h) / 2 + 100;

    SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

    string playText = "Press [ENTER] to play!";

    SDL_Surface* playSurface = TTF_RenderText_Solid(font, playText.c_str(), white);
    SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);

    SDL_Rect playRect;
    playRect.w = playSurface->w;
    playRect.h = playSurface->h;
    playRect.x = (SCREEN_WIDTH - playRect.w) / 2;
    playRect.y = (SCREEN_HEIGHT - playRect.h) / 2 + 200;

    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);

    SDL_DestroyTexture(nameTexture);
    SDL_FreeSurface(nameSurface);
    SDL_DestroyTexture(playTexture);
    SDL_FreeSurface(playSurface);
    SDL_DestroyTexture(buttonTexture);
    SDL_FreeSurface(buttonSurface);
}
