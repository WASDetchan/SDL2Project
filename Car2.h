//
// Created by yarik on 10.03.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_CAR2_H
#define CMAKE_INSTALL_CMAKE_CAR2_H
#include "WorldSprite.h"
#include <cmath>

const long double FRICTION_COEFFICIENT = 0.3, BRAKE_COEFFICIENT = 5; // temp⁻¹
const long double MIN_SPEED = 0.001;

class Car2 : public WorldSprite{
public:
    void updatePosition();
    //void setAcceleration(long double acceleration);

    //void turnRight(bool turn);
    //void turnLeft(bool turn);
    //void brake(bool brake);

    explicit Car2(Camera *playerCamera);

private:
    //void getRotationAngle(long double* angle) final;
    bool _turnRight = false, _turnLeft = false, _brake = false;
    long double _speed, _acceleration, _angle, _radiusOfCurvature;
};

void Car2::updatePosition() {

}


Car2::Car2(Camera *playerCamera) : WorldSprite(playerCamera) {
    _speed = 0;
    _acceleration = 0;
    _angle = 0;
    _turnRight = true;
    _turnLeft = false;
    _brake = false;
    _radiusOfCurvature = 0.3;
}

#endif //CMAKE_INSTALL_CMAKE_CAR2_H
