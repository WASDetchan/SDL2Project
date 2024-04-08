//
// Created by yarik on 06.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_PSEUDO_NON_POSITIONAL_VECTOR_H
#define CMAKE_INSTALL_CMAKE_PSEUDO_NON_POSITIONAL_VECTOR_H

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

#endif //CMAKE_INSTALL_CMAKE_PSEUDO_NON_POSITIONAL_VECTOR_H
