#pragma once
#include<cmath>

bool checkCollision(Spaceship& s, Asteroid& a) {
    float sX = s.getX(), sY = s.getY(), aX = a.getX(), aY = a.getY();
    float sW = s.getWidth(), aW = a.getSize();

    float distance = sqrt((sX - aX) * (sX - aX) + (sY - aY) * (sY - aY));

    return distance < (sW / 2) + aW * 10;
}
