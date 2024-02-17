#ifndef SDL2TEST_WORLDSPRITE_H
#define SDL2TEST_WORLDSPRITE_H

#include "Sprite.h"

class WorldSprite : public Sprite{
public:
    explicit WorldSprite(Camera *playerCamera);

    void setWorldPosition(long double x, long double y);

    void moveWorldPosition(long double x, long double y);

    void setWorldSize(long double w, long double h);

    void setWorldRotationCentre(long double x, long double y);

    virtual void getWorldPosition(long double *x, long double *y) const;

    bool rotate; // temporary !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
protected:
    long double _worldX, _worldY, _worldRotationCentreX, _worldRotationCentreY, _worldWidth, _worldHeight;

    void getDestinationRect(SDL_Rect *&destinationRect) final;

    void getRotationCentre(SDL_Point *&center) final;

    virtual void getWorldSize(long double *w, long double *h) const;

    virtual void getWorldRotationCentre(long double *x, long double *y) const;
};

WorldSprite::WorldSprite(Camera *playerCamera) : Sprite(playerCamera) {
    _worldX = 0;
    _worldY = 0;
    _worldRotationCentreX = 0;
    _worldRotationCentreY = 0;
    _worldWidth = 0;
    _worldHeight = 0;
    rotate = false;
}

void WorldSprite::setWorldPosition(long double x, long double y) {
    _worldX = x;
    _worldY = y;
}

void WorldSprite::moveWorldPosition(long double x, long double y) {
    _worldX += x;
    _worldY += y;
}

void WorldSprite::setWorldSize(long double w, long double h) {
    _worldWidth = w;
    _worldHeight = h;
}

void WorldSprite::setWorldRotationCentre(long double x, long double y) {
    _worldRotationCentreX = x;
    _worldRotationCentreY = y;
}

void WorldSprite::getDestinationRect(SDL_Rect *&destinationRect) {
    long double worldX, worldY, worldWidth, worldHeight;

    getWorldPosition(&worldX, &worldY);
    getWorldSize(&worldWidth, &worldHeight);

    long double pixelsPerUnit = _playerCamera->getPixelsPerUnit(),
    screenX = _playerCamera->calculateScreenPositionX(worldX),
    screenY = _playerCamera->calculateScreenPositionY(worldY),
    screenWidth = worldWidth * _playerCamera->getZoom(),
    screenHeight = worldHeight * _playerCamera->getZoom();



    destinationRect = new SDL_Rect({static_cast<int>(screenX * pixelsPerUnit),
                                   static_cast<int>(screenY * pixelsPerUnit),
                                   static_cast<int>(ceill(screenWidth * pixelsPerUnit)),
                                   static_cast<int>(ceill(screenHeight * pixelsPerUnit))});
}

void WorldSprite::getRotationCentre(SDL_Point *&center) {
    if(!rotate){
        center = nullptr;
        return;
    }

    long double worldRotationCentreX, worldRotationCentreY;

    getWorldRotationCentre(&worldRotationCentreX, &worldRotationCentreY);

    long double pixelsPerUnit = _playerCamera->getPixelsPerUnit(),
            screenX = _playerCamera->calculateScreenPositionX(worldRotationCentreX),
            screenY = _playerCamera->calculateScreenPositionY(worldRotationCentreY);

    std::cerr << screenX * pixelsPerUnit << std::endl;

    center = new SDL_Point({static_cast<int>(screenX * pixelsPerUnit),
                           static_cast<int>(screenY * pixelsPerUnit)});
}

void WorldSprite::getWorldPosition(long double *x, long double *y) const {
    *x = _worldX;
    *y = _worldY;
}

void WorldSprite::getWorldSize(long double *w, long double *h) const {
    *w = _worldWidth;
    *h = _worldHeight;
}

void WorldSprite::getWorldRotationCentre(long double *x, long double *y) const {
    *x = _worldRotationCentreX;
    *y = _worldRotationCentreY;
}


#endif //SDL2TEST_WORLDSPRITE_H
