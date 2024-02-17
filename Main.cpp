#include <SDL.h>
#include <vector>
#include <cmath>
#include "Init.h"
#include "ACircle2.h"
#include "Camera.h"
#include "TestMapGenerator.h"
#include "Scene.h"
#include "Car1.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int IMG_FLAGS = IMG_INIT_PNG;
const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED /* | SDL_RENDERER_PRESENTVSYNC*/;

const std::vector<const char*> images = {
        "images/ACircle.png",
        "images/ACircle2.png",
        "images/ACircle3.png",
        "images/car1.png"
};

const long double CAMERA_SPEED = 0.001, SEED = 0.54455712795763551975, WHEEL_SENSITIVITY = 0.1;

WorldSprite gen1(Camera* playerCamera){
    auto seed = SEED;

    seed *= 53498874654978542231684477.0L;
    seed /= 54978542231684316847.0L;

    seed -= static_cast<uint64_t>(seed);

    TestMapGenerator generator = TestMapGenerator(playerCamera, seed);

    SDL_Texture* mapTexture;

    generator.generateMap(mapTexture, 100, 100);

    WorldSprite map = WorldSprite(playerCamera);

    map.setTexture(mapTexture);

    map.setWorldPosition(0.5, 0.8);

    map.setWorldSize(0.5, 0.5);

    return map;
}

void gen2(WorldSprite* &map, Camera* playerCamera){
    auto seed = SEED;

    seed *= 14287547854223;
    seed /= 778472857548;

    seed -= static_cast<uint64_t>(seed);

    TestMapGenerator generator = TestMapGenerator(playerCamera, seed);

    SDL_Texture* mapTexture;

    generator.generateMap(mapTexture, 100, 100);

    map = new WorldSprite(playerCamera);

    map->setTexture(mapTexture);

    map->setWorldPosition(1.0000000000, 0.80000000);

    map->setWorldSize(0.500000000000, 0.500000000);
}

void moveCamera(Camera* playerCamera, bool wPressed, bool sPressed, bool aPressed, bool dPressed){
    int64_t cameraMoveMultiplierX = 0, cameraMoveMultiplierY = 0;

    long double deltaX = 0, deltaY = 0;

    cameraMoveMultiplierX = static_cast<int64_t>(dPressed) - static_cast<int64_t>(aPressed);

    cameraMoveMultiplierY = static_cast<int64_t>(sPressed) - static_cast<int64_t>(wPressed);

    deltaX = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
             CAMERA_SPEED * cameraMoveMultiplierX / playerCamera->getZoom();
    deltaY = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
             CAMERA_SPEED * cameraMoveMultiplierY / playerCamera->getZoom();

    playerCamera->moveX(deltaX);

    playerCamera->moveY(deltaY);

    playerCamera->updateFrameTime(SDL_GetTicks64());
}

void eventCheck(Camera* playerCamera, bool &isRunning, bool &wPressed, bool &sPressed, bool &aPressed, bool &dPressed){
    static SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) {
            isRunning = false;
        }
        if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_w:
                    wPressed = true;
                    break;
                case SDLK_s:
                    sPressed = true;
                    break;
                case SDLK_a:
                    aPressed = true;
                    break;
                case SDLK_d:
                    dPressed = true;
                    break;
            }
        }
        if(event.type == SDL_KEYUP){
            switch (event.key.keysym.sym){
                case SDLK_w:
                    wPressed = false;
                    break;
                case SDLK_s:
                    sPressed = false;
                    break;
                case SDLK_a:
                    aPressed = false;
                    break;
                case SDLK_d:
                    dPressed = false;
                    break;
            }
        }
        if(event.type == SDL_MOUSEWHEEL){
            int32_t y = event.wheel.y;
            playerCamera->changeZoom(y * WHEEL_SENSITIVITY);
        }
    }
}

void accelerateCar(Car1 &car, bool aPressed, bool dPressed) {
    if(aPressed) car.setAcceleration(-0.5);
    if(dPressed) car.setAcceleration(0.5);
    if(aPressed && dPressed) car.setAcceleration(0);
    if(!aPressed && !dPressed) car.setAcceleration(0);
}

int main(int argc, char *argv[]){
    bool isRunning;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d12");

    std::vector<SDL_Texture*> textures;

    bool initSuccess = init(window, SCREEN_WIDTH, SCREEN_HEIGHT) &&
            initImage(IMG_FLAGS) &&
            initRendered(renderer, window, RENDERER_FLAGS);


    if(initSuccess){
        auto* playerCamera = new Camera(renderer, SDL_GetTicks64());

        Scene mainScene = Scene(playerCamera);

        ACircle2 circle2(playerCamera);

        mainScene.addSprite(&circle2);

        circle2.loadTexture(images[2]);

        circle2.setWorldPosition(0.3, 0.3);

        circle2.setWorldSize(0.2, 0.2);

        auto circle3 = ACircle2(playerCamera);

        mainScene.addSprite(&circle3);

        circle3.loadTexture(images[2]);

        circle3.setWorldPosition(0.5, 0.5);


        circle3.setWorldSize(0.1, 0.1);

        WorldSprite map1 = gen1(playerCamera);

        WorldSprite* map2;

        mainScene.addSprite(&map1);

        gen2(map2, playerCamera);

        mainScene.addSprite(map2);


        Car1 car(playerCamera);

        car.loadTexture(images[3]);
        car.setWorldSize(0.4, 0.1);


        mainScene.addSprite(&car);
        mainScene.followSprite(&car);

        isRunning = true;

        bool wPressed = false, sPressed = false, aPressed = false, dPressed = false;

        while(isRunning) {
            moveCamera(playerCamera, wPressed, sPressed, aPressed, dPressed);

            accelerateCar(car, aPressed, dPressed);

            SDL_RenderClear(renderer);

            car.updatePosition();

            long double X, Y;

            car.getWorldPosition(&X, &Y);

            mainScene.renderAll();

            SDL_RenderPresent(renderer);

            eventCheck(playerCamera, isRunning, wPressed, sPressed, aPressed, dPressed);
        }
    }

    quit(window, textures, renderer);

    return 0;
}