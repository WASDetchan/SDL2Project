//
// Created by yarik on 06.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_NON_POSITIONAL_VECTOR_H
#define CMAKE_INSTALL_CMAKE_NON_POSITIONAL_VECTOR_H

#include "CompositeFloat.h"
#include "PseudoNonPositionalVector.h"

class NonPositionalVector{
public:
    NonPositionalVector();
    NonPositionalVector(double x, double y);
    NonPositionalVector(CompositeFloat x, CompositeFloat y);

    NonPositionalVector operator+(NonPositionalVector other) const;
    NonPositionalVector operator+=(NonPositionalVector other);

    PseudoNonPositionalVector operator*(NonPositionalVector other) const;

    CompositeFloat getMagnitude() const;

    double getAngleToXAxis() const;
private:
    CompositeFloat X, Y;
};

NonPositionalVector::NonPositionalVector() {
    X = CompositeFloat(0.0);
    Y = CompositeFloat(0.0);
}

NonPositionalVector::NonPositionalVector(double x, double y) {
    X = CompositeFloat(x);
    Y = CompositeFloat(y);
}

NonPositionalVector::NonPositionalVector(CompositeFloat x, CompositeFloat y) {
    X = x;
    Y = y;
}

NonPositionalVector NonPositionalVector::operator+(NonPositionalVector other) const {
    CompositeFloat x1 = X, x2 = other.X, x3;
    CompositeFloat y1 = Y, y2 = other.Y, y3;
    x3 = x1 + x2;
    y3 = y1 + y2;
    return {x3, y3};
}

NonPositionalVector NonPositionalVector::operator+=(NonPositionalVector other) {
    *this = *this + other;
    return *this;
}

PseudoNonPositionalVector NonPositionalVector::operator*(NonPositionalVector other) const {
    auto v = CompositeFloat(0);
    v += (X * other.Y) - (Y * other.X);
    return PseudoNonPositionalVector(v);
}

CompositeFloat NonPositionalVector::getMagnitude() const {
    auto x = static_cast<double>(X);
    auto y = static_cast<double>(Y);
    double l = sqrt(x * x + y * y);
    return CompositeFloat(l);
}

double NonPositionalVector::getAngleToXAxis() const {
    auto x = static_cast<double>(X);
    auto y = static_cast<double>(Y);
    double angle = atan2(y, x);
    return angle;
}

double getAngleBetweenVectors(NonPositionalVector const& v1, NonPositionalVector const& v2){
    double angle1 = v1.getAngleToXAxis();
    double angle2 = v2.getAngleToXAxis();
    double angle = angle1 - angle2;
    if(angle < -M_PI) angle += 2 * M_PI;
    if(angle > -M_PI) angle -= 2 * M_PI;
    return angle;
}
#endif //CMAKE_INSTALL_CMAKE_NON_POSITIONAL_VECTOR_H
