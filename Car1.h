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
    void setRadiusOfCurvature(long double radiusOfCurvature);

    void turnRight(bool turn);
    void turnLeft(bool turn);

    explicit Car1(Camera *playerCamera);

private:
    void getRotationAngle(long double* angle) final;
    bool _turnRight = false, _turnLeft = false;
    long double _speed, _acceleration, _angle, _radiusOfCurvature;
};

Car1::Car1(Camera *playerCamera) : WorldSprite(playerCamera) {
    _speed = 0;
    _acceleration = 0;
    _angle = 0;
    _turnRight = true;
    _turnLeft = false;
    _radiusOfCurvature = 0.5;
}

void Car1::updatePosition() {
    auto deltaTime = (long double)_playerCamera->getFrameTimeDifference() / 1000;
    long double distance = _speed * deltaTime + _acceleration * deltaTime * deltaTime / 2; // s = vt + (at^2) / 2 in projection on the axis of motion as motion is linear
    long double deltaX, deltaY;

    if(_turnLeft && !_turnRight){
        long double deltaAngle = distance / _radiusOfCurvature / 2,
            displacement = _radiusOfCurvature * sqrtl(2 * (1 - cosl(2 * deltaAngle)));

        std::cerr << _angle << std::endl;

        deltaX =  displacement * cosl(_angle);
        deltaY =  displacement * sinl(_angle);
    }
    if(_turnRight && !_turnLeft){
        long double deltaAngle = distance / _radiusOfCurvature / 2,
                displacement = _radiusOfCurvature * sqrtl(2 * (1 - cosl(2 * deltaAngle)));

        _angle += deltaAngle;

        deltaX =  displacement * cosl(_angle);
        deltaY =  displacement * sinl(_angle);
    }
    if(_turnLeft && _turnRight || (!_turnLeft && !_turnRight)){
        deltaX = distance * cosl(_angle); // Δx = s * cos(α)
        deltaY = distance * sinl(_angle); // Δy = s * sin(α)
    }
    while(_angle > 2 * M_PI) _angle -= 2 * M_PI;
    while(_angle < 0) _angle += 2 * M_PI;
    _speed += _acceleration * deltaTime; // v = v0 + at in projection on the axis of motion as motion is linear and acceleration is uniform
    moveWorldPosition(deltaX, deltaY);
}

void Car1::setSpeed(long double speed) {
    _speed = speed;
}

void Car1::setAcceleration(long double acceleration) {
    _acceleration = acceleration;
}

void Car1::setRadiusOfCurvature(long double radiusOfCurvature) {
    _radiusOfCurvature = radiusOfCurvature;
}

void Car1::turnRight(bool turn) {
    _turnRight = turn;
}

void Car1::turnLeft(bool turn) {
    _turnLeft = turn;
}

void Car1::getRotationAngle(long double *angle) {
    *angle = _angle * 180 / M_PI;
}


#endif //CMAKE_INSTALL_CMAKE_CAR1_H
