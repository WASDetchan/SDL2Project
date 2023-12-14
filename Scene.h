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
private:
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
    for(auto sprite : _sprites){
        sprite->render();
    }
}

#endif //SDL2TEST_SCENE_H
