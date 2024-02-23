//
// Created by yarik on 15.02.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_CAR1_H
#define CMAKE_INSTALL_CMAKE_CAR1_H

#include "WorldSprite.h"
#include <cmath>

const long double FRICTION_COEFFICIENT = 0.3, BRAKE_COEFFICIENT = 5; // temp⁻¹
const long double MIN_SPEED = 0.001;

class Car1 : public WorldSprite{
public:
    void updatePosition();
    void setAcceleration(long double acceleration);

    void turnRight(bool turn);
    void turnLeft(bool turn);
    void brake(bool brake);

    explicit Car1(Camera *playerCamera);

private:
    void getRotationAngle(long double* angle) final;
    bool _turnRight = false, _turnLeft = false, _brake = false;
    long double _speed, _acceleration, _angle, _radiusOfCurvature;
};

Car1::Car1(Camera *playerCamera) : WorldSprite(playerCamera) {
    _speed = 0;
    _acceleration = 0;
    _angle = 0;
    _turnRight = true;
    _turnLeft = false;
    _brake = false;
    _radiusOfCurvature = 0.3;
}

void Car1::updatePosition() {
    auto deltaTime = (long double)_playerCamera->getFrameTimeDifference() / 1000;
    //long double distance = _speed * deltaTime + _acceleration * deltaTime * deltaTime / 2; // s = vt + (at^2) / 2 in projection on the axis of motion as motion is linear
    long double fc;
    if(_brake) fc = BRAKE_COEFFICIENT;
    else fc = FRICTION_COEFFICIENT;
    long double ex = expl(-fc * deltaTime);
    long double coefficient = 1 / fc / fc;
    long double distance = coefficient *
            ((fc * _acceleration * deltaTime - _acceleration + fc * _speed) -
                    (fc * _speed - _acceleration) * ex);
    long double deltaX, deltaY;

    if(_turnLeft && !_turnRight){
        long double deltaAngle = distance / _radiusOfCurvature / 2,
            displacement = _radiusOfCurvature * sqrtl(2 * (1 - cosl(2 * deltaAngle)));

        if(distance < 0) displacement = -displacement;

        _angle -= deltaAngle;

        deltaX =  displacement * cosl(_angle);
        deltaY =  displacement * sinl(_angle);
    }
    if(_turnRight && !_turnLeft){
        long double deltaAngle = distance / _radiusOfCurvature / 2,
                displacement = _radiusOfCurvature * sqrtl(2 * (1 - cosl(2 * deltaAngle)));

        if(distance < 0) displacement = -displacement;

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
    //_speed += _acceleration * deltaTime; // v = v0 + at in projection on the axis of motion as motion is linear and acceleration is uniform
    _speed = ex * (fc * _speed - _acceleration) / fc + _acceleration / fc;
    if(_acceleration == 0 && abs(_speed) < MIN_SPEED){
        _speed = 0;
    }
    moveWorldPosition(deltaX, deltaY);
}

void Car1::setAcceleration(long double acceleration) {
    _acceleration = acceleration;
}

void Car1::turnRight(bool turn) {
    _turnRight = turn;
}

void Car1::turnLeft(bool turn) {
    _turnLeft = turn;
}

void Car1::brake(bool brake) {
    _brake = brake;
}

void Car1::getRotationAngle(long double *angle) {
    *angle = _angle * 180 / M_PI;
}


#endif //CMAKE_INSTALL_CMAKE_CAR1_H
