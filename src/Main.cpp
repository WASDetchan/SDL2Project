#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <exception>
#include <vector>
#include "engine/Scene.h"
#include "engine/Init.h"
#include "ACircle2.h"
#include "TestMapGenerator.h"
#include "Car1.h"
#include "engine/VectorSprite.h"
#include <iostream>
#include "something.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int IMG_FLAGS = IMG_INIT_PNG;
const int RENDERER_FLAGS = 0 | SDL_RENDERER_ACCELERATED/*  | SDL_RENDERER_PRESENTVSYNC*/;

const std::vector<const char*> images = {
        "images/ACircle.png",
        "images/ACircle2.png",
        "images/ACircle3.png",
        "images/car11.png"
};


int main(int argc, char *argv[]){
    bool isRunning;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

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
        circle2.setWorldPosition(0, 0);
        circle2.setWorldSize(0.2, 0.2);


        auto circle3 = ACircle2(playerCamera);
        mainScene.addSprite(&circle3);
        circle3.loadTexture(images[2]);
        circle3.setWorldPosition(0, 0.5);
        circle3.setWorldSize(0.1, 0.1);

        WorldSprite* map2;
        gen2(map2, playerCamera);
        mainScene.addSprite(map2);
        map2->name = "Map";


        Car1 car(playerCamera);
        car.loadTexture(images[3]);
        car.setWorldSize(0.4, 0.2);
        auto cart = &car;
        mainScene.addSprite(cart);
        mainScene.followSprite(&car, SMOOTH);

        NonPositionalVector R = NonPositionalVector(CompositeFloat(0.2), CompositeFloat(0.2)), V = NonPositionalVector();
        long double angle;

        circle3.getRotationAngle(&angle);
        auto angleCF = CompositeFloat(static_cast<double>(angle));
        V.setPolarPosition(angleCF, CompositeFloat(0.3));
        PositionalVector PV(R, V);
        auto* VS = new VectorSprite(playerCamera, PositionalVector());
        VS->setVector(PV);
        VS->name = "VS";
        mainScene.addSprite(VS);

        V.setPolarPosition(CompositeFloat(0.0), CompositeFloat(0.3));
        auto PV1 = PositionalVector(NonPositionalVector(), R);
        auto* VS1 = new VectorSprite(playerCamera, PV1);
        VS1->updatePosition();
        mainScene.addSprite(VS1);
        VS1->name = "VS1";

        auto PV3 = PositionalVector(NonPositionalVector(), R + V);
        auto* VS3 = new VectorSprite(playerCamera, PV3);
        VS3->updatePosition();
        mainScene.addSprite(VS3);
        VS3->name = "VS3";

        isRunning = true;
        bool wPressed = false, sPressed = false, aPressed = false, dPressed = false, spacePressed = false, nPressed = false;


        while(isRunning) {
            playerCamera->updateFrameTime(SDL_GetTicks64());

            accelerateCar(&car, wPressed, sPressed, aPressed, dPressed, spacePressed);

            SDL_RenderClear(renderer);

            car.updatePosition();

            long double X, Y;

            if(nPressed){
                nPressed = false;
                mainScene.removeSprite(map2);
                delete map2;
                gen2(map2, playerCamera);
                //mainScene.addSprite(map2);

                mainScene.removeSprite(cart);
                mainScene.addSprite(cart);
            }

            auto worldMouseX = (double)playerCamera->calculateWorldPositionX(mouseX / playerCamera->getPixelsPerUnit());
            auto worldMouseY = (double)playerCamera->calculateWorldPositionY(mouseY / playerCamera->getPixelsPerUnit());

            R.setXYPosition(CompositeFloat(worldMouseX), CompositeFloat(worldMouseY));

            circle3.getRotationAngle(&angle);
            angleCF = CompositeFloat(M_PI * static_cast<double>(angle) / 180.0);
            V.setPolarPosition(angleCF, CompositeFloat(0.3));
            PV = PositionalVector(R, V);
            VS->setVector(PV);
            VS->updatePosition();

            PV1 = PositionalVector(NonPositionalVector(CompositeFloat(0.0), CompositeFloat(0.0)), R);
            VS1->setVector(PV1);
            VS1->updatePosition();

            auto PNPV = R * V;

            PV3 = PositionalVector(NonPositionalVector(CompositeFloat(0.0), PNPV.getMagnitude()));
            VS3->setVector(PV3);
            VS3->updatePosition();

            car.getWorldPosition(&X, &Y);

            mainScene.renderAll();

            SDL_RenderPresent(renderer);

            eventCheck(playerCamera, isRunning, wPressed, sPressed, aPressed, dPressed, spacePressed, nPressed);
        }
    }

    quit(window, textures, renderer);

    return 0;
}