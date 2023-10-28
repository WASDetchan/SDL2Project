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


    [[nodiscard]] long double getX() const;

    [[nodiscard]] long double getY() const;

    [[nodiscard]] long double getZoom() const;

    [[nodiscard]] long double getScreenMultiplier() const;

    [[nodiscard]] uint64_t getFrameTime() const;

    [[nodiscard]] uint64_t getPreviousFrameTime() const;

    void updateFrameTime(uint64_t frameTime);

private:
    long double _x, _y, _zoom, _screenMultiplier;

    uint64_t _frameTime, _previousFrameTime;

    SDL_Renderer* _renderer;
};

Camera::Camera(SDL_Renderer* renderer) {
    _renderer = renderer;

    int windowWidth, windowHeight, minWindowDimension;
    SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);
    minWindowDimension = std::min(windowWidth, windowHeight);

    _screenMultiplier = minWindowDimension;

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
        std::cerr << _zoom << std::endl;
    }
}


long double Camera::getX() const {
    return _x;
}

long double Camera::getY() const {
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

long double Camera::getScreenMultiplier() const {
    return _screenMultiplier;
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
