#include"explosion.h"
#include"constant.h"

explosion::explosion(float _x, float _y, int _size)
    :x(_x), y(_y), size(_size), currentFrame(0), totalFrames(6), frameDuration(EXPLOSION_FRAME_DURATION), timer(0.0f), alive(1) {};

void explosion::update() {
    timer += 0.016f;
    if(timer >= frameDuration) {
        timer -= frameDuration;
        currentFrame++;
    }
    if(currentFrame > totalFrames) alive = 0;
}
