//
// Created by yarik on 08.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_VECTORSPRITE_H
#define CMAKE_INSTALL_CMAKE_VECTORSPRITE_H

#include "WorldSprite.h"
#include "math/PositionalVector.h"
#include <string>


class VectorSprite : public WorldSprite{
public:
    explicit VectorSprite(Camera *playerCamera);
    VectorSprite(Camera *playerCamera, PositionalVector v);

    void setVector(PositionalVector v);

    void updatePosition();
private:
    void getRotationAngle(long double* angle) final;

    std::string file = "images/VectorArrow.png";

    PositionalVector vector;
    void getColorMod(unsigned char *red, unsigned char *green, unsigned char *blue) final;
};

VectorSprite::VectorSprite(Camera *playerCamera) : WorldSprite(playerCamera) { //TODO ne robit hz pachimu
    *this = VectorSprite(playerCamera, PositionalVector());
}

VectorSprite::VectorSprite(Camera *playerCamera, PositionalVector v) : WorldSprite(playerCamera) {
    vector = v;
    name = "Vector Sprite";
    loadTexture(file.c_str());
}

void VectorSprite::setVector(PositionalVector v) {
    vector = v;
}

void VectorSprite::updatePosition() {
    NonPositionalVector R, V, C;
    R = vector.getInitialRadiusVector();
    V = vector.getNonPositionalVector() * 0.5;

    C = R + V;
    CompositeFloat X = C.getXProjection();
    CompositeFloat Y = C.getYProjection();

    auto width = V.getMagnitude() * CompositeFloat(2.0);

    setWorldPosition(static_cast<double>(X), static_cast<double>(Y));
    setWorldSize(static_cast<double>(width), static_cast<double>(0.03));
}

void VectorSprite::getColorMod(unsigned char *red, unsigned char *green, unsigned char *blue) {
    *red = 0;
    *green = 0;
    *blue = 255;
}

void VectorSprite::getRotationAngle(long double *angle) {
    auto V = vector.getNonPositionalVector();
    *angle = static_cast<double>(V.getAngleToXAxis()) * 180.0 / M_PI;
}

#endif //CMAKE_INSTALL_CMAKE_VECTORSPRITE_H
