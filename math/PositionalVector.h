//
// Created by yarik on 06.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H
#define CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H

#include "NonPositionalVector.h"

class PositionalVector{
public:
    PositionalVector();
    PositionalVector(NonPositionalVector r, NonPositionalVector v);

    explicit operator NonPositionalVector() const;
    PositionalVector operator+(NonPositionalVector other) const;

    NonPositionalVector getInitialRadiusVector();
    NonPositionalVector getTerminalRadiusVector();
private:
    NonPositionalVector R, V;
};

PositionalVector::PositionalVector() {
    R = NonPositionalVector();
    V = NonPositionalVector();
}

PositionalVector::PositionalVector(NonPositionalVector r, NonPositionalVector v) {
    R = r;
    V = v;
}

PositionalVector::operator NonPositionalVector() const {
    return V;
}

NonPositionalVector PositionalVector::getInitialRadiusVector() {
    return R;
}

NonPositionalVector PositionalVector::getTerminalRadiusVector() {
    return R + V;
}

PositionalVector PositionalVector::operator+(NonPositionalVector other) const {
    NonPositionalVector v1 = V, v2 = other, v3;
    v3 = v1 + v2;
    return {R, v3};
}

#endif //CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H
