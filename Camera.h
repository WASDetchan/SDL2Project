#ifndef SDL2TEST_CAMERA_H
#define SDL2TEST_CAMERA_H

#include <SDL.h>
#include <algorithm>
#include <vector>
#include <cmath>

class Camera{
public:
    [[maybe_unused]] explicit Camera(SDL_Renderer* renderer);

    [[maybe_unused]] explicit Camera(SDL_Renderer* renderer, uint64_t frameTime);

    [[maybe_unused]] SDL_Renderer* getRenderer();

    [[maybe_unused]] void setX(long double x);

    [[maybe_unused]] void setY(long double y);

    [[maybe_unused]] void setPosition(long double x, long double y);

    [[maybe_unused]] void moveX(long double deltaX);

    [[maybe_unused]] void moveY(long double deltaY);

    [[maybe_unused]] void setZoom(long double zoom);

    [[maybe_unused]] void changeZoom(long double deltaZoom);

    [[maybe_unused]] void setZoomStep(long double zoomStep);


    [[nodiscard]] long double getCornerX() const;

    [[nodiscard]] long double getCornerY() const;

    [[nodiscard]] long double getCentreX() const;

    [[nodiscard]] long double getCentreY() const;

    void getCentrePosition(long double &x, long double &y) const;

    [[nodiscard]] long double getZoom() const;

    [[nodiscard]] long double getPixelsPerUnit() const;

    [[nodiscard]] long double getScreenMultiplierX() const;

    [[nodiscard]] long double getScreenMultiplierY() const;

    [[nodiscard]] long double calculateScreenPositionX(long double worldPositionX) const;

    [[nodiscard]] long double calculateScreenPositionY(long double worldPositionY) const;

    [[nodiscard]] uint64_t getFrameTime() const;

    [[nodiscard]] uint64_t getPreviousFrameTime() const;

    [[nodiscard]] uint64_t getFrameTimeDifference() const;

    void updateFrameTime(uint64_t frameTime);

private:
    long double _x, _y, _zoom, _zoomStep{}, _zoomSteps{}, _pixelsPerUnit,  _screenMultiplierX, _screenMultiplierY;

    uint64_t _frameTime, _previousFrameTime;

    SDL_Renderer* _renderer;
};

[[maybe_unused]] Camera::Camera(SDL_Renderer* renderer) {
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
    _zoomSteps = 0;
    _zoomStep = 1.1;

    _frameTime = 0;
    _previousFrameTime = 0;
}


Camera::Camera(SDL_Renderer *renderer, uint64_t frameTime) {
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
    _zoomSteps = 0;
    _zoomStep = 1.1;

    _frameTime = frameTime;
    _previousFrameTime = frameTime;
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

void Camera::setPosition(long double x, long double y) {
    _x = x;
    _y = y;
}


void Camera::setZoom(long double zoom) {
    _zoomSteps = zoom;
    _zoom = powl(_zoomStep, _zoomSteps);
}

void Camera::changeZoom(long double deltaZoom) {
    _zoomSteps += deltaZoom;
    setZoom(_zoomSteps);
}

void Camera::setZoomStep(long double zoomStep) {
    _zoomStep = zoomStep;
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

void Camera::getCentrePosition(long double &x, long double &y) const {
    x = _x;
    y = _y;
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

uint64_t Camera::getFrameTimeDifference() const {
    return _frameTime - _previousFrameTime;
}

void Camera::updateFrameTime(uint64_t frameTime) {
    _previousFrameTime = _frameTime;
    _frameTime = frameTime;
}


#endif //SDL2TEST_CAMERA_H
