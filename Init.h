#ifndef SDL2TEST_INIT_H
#define SDL2TEST_INIT_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <vector>
#include "Init.h"

bool init (SDL_Window* &window, const int width, const int height){
    bool initSuccess = true;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        initSuccess = false;
    }

    window = SDL_CreateWindow( "SDL Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_FOCUS);

    if(window == nullptr){
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        initSuccess = false;
    }

    return initSuccess;
}

bool initImage(const int flags){
    bool initImageSuccess = true;
    if(!(IMG_Init(flags) & flags))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        initImageSuccess = false;
    }
    return initImageSuccess;
}

bool initRendered(SDL_Renderer* &renderer, SDL_Window* window, int flags){
    bool initRendererSuccess = true;

    renderer = SDL_CreateRenderer(window, -1, flags);

    if(renderer == nullptr){
        initRendererSuccess = false;
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) < 0){
        initRendererSuccess = false;
        printf("Render draw color could not be set! SDL Error: %s\n", SDL_GetError());
    }

    return initRendererSuccess;
}

void quit(SDL_Window* &window, std::vector<SDL_Texture*> &textures, SDL_Renderer* &renderer){
    for(SDL_Texture* &texture : textures){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool loadTexture(const char *file, std::vector<SDL_Texture*> &textures, SDL_Renderer* renderer){
    bool loadTextureSuccess = true;

    SDL_Surface* loadedSurface = IMG_Load(file);

    if(loadedSurface == nullptr){
        printf( "Unable to load image %s! SDL Error: %s\n", file, SDL_GetError() );
        loadTextureSuccess = false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if(texture == nullptr){
        printf( "Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError() );
    }

    textures.push_back(texture);

    return loadTextureSuccess;
}

bool loadTextures(const std::vector<const char*> &files, std::vector<SDL_Texture*> &textures, SDL_Renderer* renderer){
    bool loadTexturesSuccess = true;
    for(const char *file : files) {
        loadTexturesSuccess = loadTexturesSuccess && loadTexture(file, textures, renderer);
    }
    return loadTexturesSuccess;
}

#endif //SDL2TEST_INIT_H
