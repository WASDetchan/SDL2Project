//
// Created by yarik on 06.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H
#define CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H

#include "NonPositionalVector.h"

class PositionalVector{
public:
    PositionalVector();
    explicit PositionalVector(NonPositionalVector v);
    PositionalVector(NonPositionalVector r, NonPositionalVector v);

    explicit operator NonPositionalVector() const;
    PositionalVector operator+(NonPositionalVector other) const;

    [[nodiscard]] NonPositionalVector getInitialRadiusVector() const;
    [[nodiscard]] NonPositionalVector getTerminalRadiusVector() const;
    [[nodiscard]] NonPositionalVector getNonPositionalVector() const;

private:
    NonPositionalVector R, V;
};

PositionalVector::PositionalVector() {
    R = NonPositionalVector();
    V = NonPositionalVector();
}

PositionalVector::PositionalVector(NonPositionalVector v) {
    R = NonPositionalVector();
    V = v;
}

PositionalVector::PositionalVector(NonPositionalVector r, NonPositionalVector v) {
    R = r;
    V = v;
}

PositionalVector::operator NonPositionalVector() const {
    return V;
}

NonPositionalVector PositionalVector::getInitialRadiusVector() const{
    return R;
}

NonPositionalVector PositionalVector::getTerminalRadiusVector() const{
    return R + V;
}

NonPositionalVector PositionalVector::getNonPositionalVector() const {
    return static_cast<NonPositionalVector>(*this);
}

PositionalVector PositionalVector::operator+(NonPositionalVector other) const {
    NonPositionalVector v1 = V, v2 = other, v3;
    v3 = v1 + v2;
    return {R, v3};
}




#endif //CMAKE_INSTALL_CMAKE_POSITIONAL_VECTOR_H
