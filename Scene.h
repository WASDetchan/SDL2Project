#ifndef SDL2TEST_SCENE_H
#define SDL2TEST_SCENE_H

#include "Camera.h"
#include "Sprite.h"

const long double CAMERA_SMOOTH_FOLLOW_COEFFICIENT = 0.01;

typedef enum {
    NONE,
    INSTANT,
    SMOOTH
} FollowMode;

class Scene{
public:
    explicit Scene(Camera *camera);

    void setCamera(Camera* camera);

    void addSprite(Sprite* sprite);

    void renderAll();

    void followSprite(WorldSprite *followedSprite, FollowMode mode = INSTANT);

    void unfollow();
private:
    void instantFollowPositionUpdate();

    void smoothFollowPositionUpdate();

    WorldSprite *_followedSprite = nullptr;

    bool _following = false;

    Camera* _camera;

    FollowMode _followMode;

    std::vector<Sprite*> _sprites;
};

Scene::Scene(Camera *camera) {
    _camera = camera;
    _followMode = NONE;
}

void Scene::setCamera(Camera *camera) {
    _camera = camera;
}

void Scene::addSprite(Sprite *sprite) {
    _sprites.push_back(sprite);
}



void Scene::renderAll() {
    switch(_followMode){
        case NONE:
            break;
        case INSTANT:
            instantFollowPositionUpdate();
            break;
        case SMOOTH:
            smoothFollowPositionUpdate();
            break;
    }
    for(auto sprite : _sprites){
        sprite->render();
    }
}

void Scene::followSprite(WorldSprite *followedSprite, FollowMode mode) {
    _followedSprite = followedSprite;
    _following = true;
    _followMode = mode;
}

void Scene::unfollow() {
    _followedSprite = nullptr;
    _following = false;
}

void Scene::instantFollowPositionUpdate() {
    long double followedX, followedY;
    _followedSprite->getWorldPosition(&followedX, &followedY);
    _camera->setPosition(followedX, followedY);
}

void Scene::smoothFollowPositionUpdate() {
    long double followedX, followedY;
    _followedSprite->getWorldPosition(&followedX, &followedY);
    long double x, y;
    _camera->getCentrePosition(x, y);
    long double xDifference = followedX - x,
        yDifference = followedY - y,
        xSpeed = xDifference * CAMERA_SMOOTH_FOLLOW_COEFFICIENT,
        ySpeed = yDifference * CAMERA_SMOOTH_FOLLOW_COEFFICIENT;
    auto deltaTime = _camera->getFrameTimeDifference();
    long double deltaX = xSpeed * deltaTime,
        deltaY = ySpeed * deltaTime;
    x += deltaX;
    y += deltaY;
    if(abs(deltaX) > abs(xDifference)){
        x = followedX;
    }
    if(abs(deltaY) > abs(yDifference)){
        y = followedY;
    }
    _camera->setPosition(x, y);
}

#endif //SDL2TEST_SCENE_H
