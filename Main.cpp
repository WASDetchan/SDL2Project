#include <SDL.h>
#include <vector>
#include "Init.h"
#include "ACircle2.h"
#include "Camera.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int IMG_FLAGS = IMG_INIT_PNG;
const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC;

const std::vector<const char*> images = {
        "images/ACircle.png",
        "images/ACircle2.png",
        "images/ACircle3.png"
};

long double CAMERA_SPEED = 0.001;

int main(int argc, char *argv[]){
    bool isRunning;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::vector<SDL_Texture*> textures;

    bool initSuccess = init(window, SCREEN_WIDTH, SCREEN_HEIGHT) &&
            initImage(IMG_FLAGS) &&
            initRendered(renderer, window, RENDERER_FLAGS);

    auto* playerCamera = new Camera(renderer);

    ACircle2 circle2(playerCamera);

    circle2.loadTexture(images[2]);

    circle2.setWorldPosition(0.3, 0.3);

    circle2.setWorldSize(0.2, 0.2);

    auto circle3 = ACircle2(playerCamera);

    circle3.loadTexture(images[2]);

    circle3.setWorldPosition(0.5, 0.5);

    circle3.setWorldSize(0.1, 0.1);

    circle3.setRotationCenter(-1, -1);

    if(initSuccess){

        isRunning = true;

        SDL_Event event;

        int64_t cameraMoveMultiplierX = 0, cameraMoveMultiplierY = 0;

        bool wPressed = false, sPressed = false, aPressed = false, dPressed = false;

        while(isRunning){
            cameraMoveMultiplierX = static_cast<int64_t>(dPressed) - static_cast<int64_t>(aPressed);

            cameraMoveMultiplierY = static_cast<int64_t>(sPressed) - static_cast<int64_t>(wPressed);

            long double deltaX = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
                                 CAMERA_SPEED * cameraMoveMultiplierX,
                        deltaY = static_cast<long double>(playerCamera->getFrameTime() - playerCamera->getPreviousFrameTime()) *
                                          CAMERA_SPEED * cameraMoveMultiplierY;

            playerCamera->moveX(deltaX);

            playerCamera->moveY(deltaY);

            playerCamera->updateFrameTime(SDL_GetTicks64());

            circle3.setWorldPosition(0.5, 0.5);

            circle3.setWorldSize(0.1, 0.1);

            circle3.setRotationCenter(-1, -1);

            SDL_RenderClear(renderer);

            circle2.render();

            circle3.render();

            SDL_RenderPresent(renderer);

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
            }
        }
    }

    quit(window, textures, renderer);

    return 0;
}