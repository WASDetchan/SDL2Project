//
// Created by yarik on 10.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_SOMETHING_H
#define CMAKE_INSTALL_CMAKE_SOMETHING_H

#include <SDL2/SDL.h>

const long double CAMERA_SPEED = 0.001, SEED = 0.586456314595763551975, WHEEL_SENSITIVITY = 1;
long mouseX, mouseY;


void gen2(WorldSprite* &map, Camera* playerCamera){
    static auto seed = SEED;
    seed *= 14287547854223;
    seed /= 778472857548;
    seed -= static_cast<uint64_t>(seed);

    TestMapGenerator generator = TestMapGenerator(playerCamera, seed);
    SDL_Texture* mapTexture;
    generator.generateMap(mapTexture, 1000, 1000);
    map = new WorldSprite(playerCamera);
    map->setTexture(mapTexture);
    map->setWorldPosition(1.0000000000, 0.80000000);
    map->setWorldSize(25.00000000000, 25.00000000);
}

[[maybe_unused]] void moveCamera(Camera* playerCamera, bool wPressed, bool sPressed, bool aPressed, bool dPressed){
    int64_t cameraMoveMultiplierX, cameraMoveMultiplierY;
    long double deltaX, deltaY;

    cameraMoveMultiplierX = static_cast<int64_t>(dPressed) - static_cast<int64_t>(aPressed);
    cameraMoveMultiplierY = static_cast<int64_t>(sPressed) - static_cast<int64_t>(wPressed);
    deltaX = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
             CAMERA_SPEED * cameraMoveMultiplierX / playerCamera->getZoom();
    deltaY = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
             CAMERA_SPEED * cameraMoveMultiplierY / playerCamera->getZoom();

    playerCamera->moveX(deltaX);
    playerCamera->moveY(deltaY);
}

void eventCheck(Camera* playerCamera, bool &isRunning, bool &wPressed, bool &sPressed, bool &aPressed, bool &dPressed, bool &spacePressed, bool &nPressed){
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
                case SDLK_SPACE:
                    spacePressed = true;
                    break;
                case SDLK_n:
                    nPressed = true;
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
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
                case SDLK_SPACE:
                    spacePressed = false;
                    break;
            }
        }
        if(event.type == SDL_MOUSEMOTION){
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
        if(event.type == SDL_MOUSEWHEEL){
            int32_t y = event.wheel.y;
            playerCamera->changeZoom(y * WHEEL_SENSITIVITY);
        }
    }
}

void accelerateCar(Car1 *car, bool wPressed, bool sPressed, bool aPressed, bool dPressed, bool spacePressed) {
    if(sPressed) car->setAcceleration(-1);
    if(wPressed) car->setAcceleration(1);
    if(sPressed && wPressed) car->setAcceleration(0);
    if(!sPressed && !wPressed) car->setAcceleration(0);

    car->turnLeft(false);
    car->turnRight(false);

    if(aPressed) car->turnLeft(true);
    if(dPressed) car->turnRight(true);

    car->brake(spacePressed);
}
#endif //CMAKE_INSTALL_CMAKE_SOMETHING_H
