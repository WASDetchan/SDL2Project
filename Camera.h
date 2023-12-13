//
// Created by yarik on 18.10.2023.
//

#ifndef CMAKE_INSTALL_CMAKE_CAMERA_H
#define CMAKE_INSTALL_CMAKE_CAMERA_H

#include <SDL.h>
#include <algorithm>

class Camera{
public:
    explicit Camera(SDL_Renderer* renderer);

    SDL_Renderer* getRenderer();

    void setX(long double x);

    void setY(long double y);

    void moveX(long double deltaX);

    void moveY(long double deltaY);

    void setZoom(long double zoom);

    void changeZoom(long double deltaZoom);


    [[nodiscard]] long double getCornerX() const;

    [[nodiscard]] long double getCornerY() const;

    [[nodiscard]] long double getCentreX() const;

    [[nodiscard]] long double getCentreY() const;

    [[nodiscard]] long double getZoom() const;

    [[nodiscard]] long double getPixelsPerUnit() const;

    [[nodiscard]] long double getScreenMultiplierX() const;

    [[nodiscard]] long double getScreenMultiplierY() const;

    [[nodiscard]] long double calculateScreenPositionX(long double worldPositionX) const;

    [[nodiscard]] long double calculateScreenPositionY(long double worldPositionY) const;

    [[nodiscard]] uint64_t getFrameTime() const;

    [[nodiscard]] uint64_t getPreviousFrameTime() const;

    void updateFrameTime(uint64_t frameTime);

private:
    long double _x, _y, _zoom, _pixelsPerUnit,  _screenMultiplierX, _screenMultiplierY;

    uint64_t _frameTime, _previousFrameTime;

    SDL_Renderer* _renderer;
};

Camera::Camera(SDL_Renderer* renderer) {
    _renderer = renderer;

    int windowWidth, windowHeight, minWindowDimension;
    SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);
    minWindowDimension = std::min(windowWidth, windowHeight);

    _pixelsPerUnit = minWindowDimension;
    _screenMultiplierX = static_cast<long double>(windowWidth) / minWindowDimension;
    _screenMultiplierY = static_cast<long double>(windowHeight) / minWindowDimension;

    _x = 0;
    _y = 0;
    _zoom = 1;

    _frameTime = 0;
    _previousFrameTime = 0;
}

SDL_Renderer *Camera::getRenderer() {
    return _renderer;
}

void Camera::setX(long double x) {
    _x = x;
}

void Camera::setY(long double y) {
    _y = y;
}

void Camera::setZoom(long double zoom) {
    _zoom = zoom;
}

void Camera::changeZoom(long double deltaZoom) {
    if((deltaZoom > 0 && _zoom < 10) ||
            (deltaZoom < 0 && _zoom > 0.1)){
        _zoom += deltaZoom;
    }
}


long double Camera::getCornerX() const {
    return _x - 0.5 * getScreenMultiplierX() / getZoom();
}

long double Camera::getCornerY() const {
    return _y - 0.5 * getScreenMultiplierY() / getZoom();
}

long double Camera::getCentreX() const {
    return _x;
}

long double Camera::getCentreY() const {
    return _y;
}

void Camera::moveX(long double deltaX) {
    _x += deltaX;
}

void Camera::moveY(long double deltaY) {
    _y += deltaY;
}

long double Camera::getZoom() const {
    return _zoom;
}

long double Camera::getPixelsPerUnit() const {
    return _pixelsPerUnit;
}

long double Camera::getScreenMultiplierX() const {
    return _screenMultiplierX;
}

long double Camera::getScreenMultiplierY() const {
    return _screenMultiplierY;
}

long double Camera::calculateScreenPositionX(long double worldPositionX) const {
    return (worldPositionX - getCentreX())  * getZoom() + 0.5 * getScreenMultiplierX();
}

long double Camera::calculateScreenPositionY(long double worldPositionY) const {
    return (worldPositionY - getCentreY())  * getZoom() + 0.5 * getScreenMultiplierY();
}

uint64_t Camera::getFrameTime() const {
    return _frameTime;
}

uint64_t Camera::getPreviousFrameTime() const {
    return _previousFrameTime;
}

void Camera::updateFrameTime(uint64_t frameTime) {
    _previousFrameTime = _frameTime;
    _frameTime = frameTime;
}


#endif //CMAKE_INSTALL_CMAKE_CAMERA_H
