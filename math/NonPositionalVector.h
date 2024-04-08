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
    NonPositionalVector operator*(CompositeFloat scalar) const;
    NonPositionalVector operator*(double scalar) const;
    NonPositionalVector operator*=(CompositeFloat scalar);

    void setXYPosition(CompositeFloat x, CompositeFloat y);
    void setPolarPosition(CompositeFloat angle, CompositeFloat radius);

    [[nodiscard]] CompositeFloat getMagnitude() const;
    [[nodiscard]] CompositeFloat getXProjection() const;
    [[nodiscard]] CompositeFloat getYProjection() const;

    [[nodiscard]] CompositeFloat getAngleToXAxis() const;
private:
    CompositeFloat X, Y, Magnitude, Angle;
};

NonPositionalVector::NonPositionalVector() {
    auto x = CompositeFloat(0.0);
    auto y = CompositeFloat(0.0);

    *this = NonPositionalVector(x, y);
}

NonPositionalVector::NonPositionalVector(double x, double y) {
    *this = NonPositionalVector(CompositeFloat(x), CompositeFloat(y));
}

NonPositionalVector::NonPositionalVector(CompositeFloat x, CompositeFloat y) {
    X = x;
    Y = y;

    auto xd = static_cast<double>(X);
    auto yd = static_cast<double>(Y);
    double l = sqrt(xd * xd + yd * yd);
    Magnitude =  CompositeFloat(l);
    Angle = CompositeFloat(atan2(yd, xd));
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

NonPositionalVector NonPositionalVector::operator*(CompositeFloat scalar) const {
    CompositeFloat X1 = X, X2, Y1 = Y, Y2;
    X2 = scalar * X1;
    Y2 = scalar * Y1;
    return {X2, Y2};
}

NonPositionalVector NonPositionalVector::operator*=(CompositeFloat scalar) {
    *this = *this * scalar;
    return *this;
}

CompositeFloat NonPositionalVector::getMagnitude() const {
    return Magnitude;
}

CompositeFloat NonPositionalVector::getAngleToXAxis() const {
    return Angle;
}

CompositeFloat NonPositionalVector::getXProjection() const {
    return X;
}

CompositeFloat NonPositionalVector::getYProjection() const {
    return Y;
}

NonPositionalVector NonPositionalVector::operator*(double scalar) const {
    return *this * CompositeFloat(scalar);
}

void NonPositionalVector::setXYPosition(CompositeFloat x, CompositeFloat y) {
    X = x;
    Y = y;
}

void NonPositionalVector::setPolarPosition(CompositeFloat angle, CompositeFloat radius) {
    Magnitude = radius;
    Angle = angle;
    X = CompositeFloat(cos(static_cast<double>(angle))) * radius;
    Y = CompositeFloat(sin(static_cast<double>(angle))) * radius;
}


CompositeFloat getAngleBetweenVectors(NonPositionalVector const& v1, NonPositionalVector const& v2){
    CompositeFloat angle1 = v1.getAngleToXAxis();
    CompositeFloat angle2 = v2.getAngleToXAxis();
    CompositeFloat angle = angle1 - angle2;
    if(static_cast<double>(angle) < -M_PI) angle += CompositeFloat(2 * M_PI);
    if(static_cast<double>(angle) > -M_PI) angle -= CompositeFloat(2 * M_PI);
    return angle;
}
#endif //CMAKE_INSTALL_CMAKE_NON_POSITIONAL_VECTOR_H
