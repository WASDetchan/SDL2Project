//
// Created by yarik on 15.02.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_CAR1_H
#define CMAKE_INSTALL_CMAKE_CAR1_H

#include "WorldSprite.h"
#include <cmath>

class Car1 : public WorldSprite{
public:
    void updatePosition();
    void setSpeed(long double speed);
    void setAcceleration(long double acceleration);
    explicit Car1(Camera *playerCamera);

private:
    bool _turnRight = false, _turnLeft = false;
    long double _speed, _acceleration, _angle;
};

Car1::Car1(Camera *playerCamera) : WorldSprite(playerCamera) {
    _speed = 0.5;
    _acceleration = 0;
    _angle = 0;
    _turnRight = false;
    _turnLeft = false;
}

void Car1::updatePosition() {
    auto deltaTime = (long double)_playerCamera->getFrameTimeDifference() / 1000;
    long double distance = _speed * deltaTime + _acceleration * deltaTime * deltaTime / 2,
        deltaX = distance * cosl(_angle),
        deltaY = distance * sinl(_angle);
    _speed += _acceleration * deltaTime;
    moveWorldPosition(deltaX, deltaY);
}

void Car1::setSpeed(long double speed) {
    _speed = speed;
}

void Car1::setAcceleration(long double acceleration) {
    _acceleration = acceleration;
}



#endif //CMAKE_INSTALL_CMAKE_CAR1_H
