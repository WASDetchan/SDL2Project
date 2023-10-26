//
// Created by yarik on 18.10.2023.
//

#ifndef CMAKE_INSTALL_CMAKE_WORLDSPRITE_H
#define CMAKE_INSTALL_CMAKE_WORLDSPRITE_H

#include "Sprite.h"

class WorldSprite : public Sprite{
public:
    explicit WorldSprite(Camera *playerCamera);

    void setWorldPosition(long double x, long double y);

    void setWorldSize(long double w, long double h);
protected:
    long double _worldX, _worldY, _worldWidth, _worldHeight;

    void getDestinationRect(SDL_Rect *&destinationRect) final;

    virtual void getWorldPosition(long double *x, long double *y) const;

    virtual void getWorldSize(long double *w, long double *h) const;
};

void WorldSprite::setWorldPosition(long double x, long double y) {
    _worldX = x;
    _worldY = y;
}

void WorldSprite::setWorldSize(long double w, long double h) {
    _worldWidth = w;
    _worldHeight = h;
}

void WorldSprite::getDestinationRect(SDL_Rect *&destinationRect) {
    long double screenX = _worldX - _playerCamera->getX(),
    screenY = _worldY - _playerCamera->getY(),
    screenWidth = _worldWidth,
    screenHeight = _worldHeight,
    screenMultiplier = _playerCamera->getScreenMultiplier();


    destinationRect = new SDL_Rect({static_cast<int>(screenX * screenMultiplier),
                                   static_cast<int>(screenY * screenMultiplier),
                                   static_cast<int>(screenWidth * screenMultiplier),
                                   static_cast<int>(screenHeight * screenMultiplier)});
}

void WorldSprite::getWorldPosition(long double *x, long double *y) const {
    *x = _worldX;
    *y = _worldY;
}

void WorldSprite::getWorldSize(long double *w, long double *h) const {
    *w = _worldWidth;
    *h = _worldHeight;
}

WorldSprite::WorldSprite(Camera *playerCamera) : Sprite(playerCamera) {
    _worldX = 0;
    _worldY = 0;
    _worldWidth = 0;
    _worldHeight = 0;
}


#endif //CMAKE_INSTALL_CMAKE_WORLDSPRITE_H
