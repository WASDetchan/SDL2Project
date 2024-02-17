#ifndef SDL2TEST_SCENE_H
#define SDL2TEST_SCENE_H

#include "Camera.h"
#include "Sprite.h"

class Scene{
public:
    explicit Scene(Camera *camera);

    void setCamera(Camera* camera);

    void addSprite(Sprite* sprite);

    void renderAll();

    void followSprite(WorldSprite *followedSprite);

    void unfollow();
private:
    WorldSprite *_followedSprite = nullptr;

    bool _following = false;

    Camera* _camera;

    std::vector<Sprite*> _sprites;
};

Scene::Scene(Camera *camera) {
    _camera = camera;
}

void Scene::setCamera(Camera *camera) {
    _camera = camera;
}

void Scene::addSprite(Sprite *sprite) {
    _sprites.push_back(sprite);
}

void Scene::renderAll() {
    if(_following){
        long double followedX, followedY;
        _followedSprite->getWorldPosition(&followedX, &followedY);
        _camera->setPosition(followedX, followedY);
    }
    for(auto sprite : _sprites){
        sprite->render();
    }
}

void Scene::followSprite(WorldSprite *followedSprite) {
    _followedSprite = followedSprite;
    _following = true;
}

void Scene::unfollow() {
    _followedSprite = nullptr;
    _following = false;
}

#endif //SDL2TEST_SCENE_H
