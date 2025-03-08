#pragma once
#include<SDL_mixer.h>
#include<map>
#include<string>

using namespace std;

class sound {
private:
    map<string, Mix_Chunk*> soundManager;
public:
    void loadSound(const string& filePath);
    void loadAllSound();
    ~sound();
    void play(const string& file, const int& loops, const int& volume, const int& channel);
    void playFadeIn(const string& file, const int& loop, const int& volume, const int& channel, const int& ms);
};
