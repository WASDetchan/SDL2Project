//
// Created by yarik on 06.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_PSEUDONONPOSITIONALVECTOR_H
#define CMAKE_INSTALL_CMAKE_PSEUDONONPOSITIONALVECTOR_H

#include "CompositeFloat.h"

class PseudoNonPositionalVector{
public:
    PseudoNonPositionalVector();
    explicit PseudoNonPositionalVector(CompositeFloat v);
private:
    CompositeFloat V;
};

PseudoNonPositionalVector::PseudoNonPositionalVector() {
    V = CompositeFloat(0.0);
}

PseudoNonPositionalVector::PseudoNonPositionalVector(CompositeFloat v) {
    V = v;
}

#endif //CMAKE_INSTALL_CMAKE_PSEUDONONPOSITIONALVECTOR_H
