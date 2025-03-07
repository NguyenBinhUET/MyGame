#include"sound.h"
#include<map>
#include<string>
#include<SDL.h>
#include<iostream>

using namespace std;

void sound::loadSound(const string& filePath) {
    string fileName = filePath.substr(7);
    soundManager[fileName] = Mix_LoadMUS(filePath.c_str());
}

void sound::loadAllSound() {
    loadSound("sounds/thrust.ogg");
    loadSound("sounds/ship-explosion.ogg");
    loadSound("sounds/asteroids-explosion.ogg");
    loadSound("sounds/shoot-laser.ogg");
    loadSound("sounds/space-station.ogg");
}

sound::~sound() {
    for (auto& pair : soundManager) {
        if (pair.second != nullptr) {
            Mix_FreeMusic(pair.second);
        }
    }
    soundManager.clear();
    Mix_CloseAudio();
}

void sound::play(const string& file, const int& loops, const int& volume, const int& channel) {
    Mix_VolumeMusic(soundManager[file], volume);
    Mix_PlayChannel(channel, soundManager[file], loops);
}

void sound::playFadeIn(const string& file, const int& loops, const int& volume, const int& channel, const int& ms) {
    Mix_VolumeMusic(soundManager[file], volume);
    Mix_FadeInChannel(channel, soundManager[file], loops, ms);
}
