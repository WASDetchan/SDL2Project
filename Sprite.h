//
// Created by yarik on 26.08.2023.
//

#ifndef SDL2TEST_SPRITEBASE_H
#define SDL2TEST_SPRITEBASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <iostream>
#include "Camera.h"

class Sprite{
public:
    explicit Sprite(Camera* playerCamera);

    ~Sprite();

    bool loadTexture(const char* file);

    void setTexture(SDL_Texture *texture);

    void render();

protected:
    Camera* _playerCamera;

    SDL_Texture* _texture;

    const char* empty = "images/Empty.png";

    void free();

    virtual void getDestinationRect(SDL_Rect* &destinationRect);

    virtual void getSourceRect(SDL_Rect* &sourceRect);

    virtual void getRotationAngle(long double* angle);

    virtual void getRotationCentre(SDL_Point* &centre);

    virtual void getFlip(SDL_RendererFlip* flip);

    virtual void getColorMod(unsigned char* red, unsigned char* green, unsigned char* blue);

    virtual void getAlphaMod(unsigned char* alpha);

    virtual void getBlendMode(SDL_BlendMode* blendMode);
};

Sprite::Sprite(Camera* playerCamera) {
    _playerCamera = playerCamera;
    _texture = nullptr;
    loadTexture(empty);
}

void Sprite::free() {
    if(_texture != nullptr){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

Sprite::~Sprite(){
    free();
}

bool Sprite::loadTexture(const char *file)  {
    free();

    bool loadTextureSuccess = true;

    SDL_Surface* loadedSurface = IMG_Load(file);

    if(loadedSurface == nullptr){
        printf( "Unable to load image %s! SDL Error: %s\n", file, SDL_GetError() );
        loadTextureSuccess = false;
    }

    if(!loadTextureSuccess){
        return loadTextureSuccess;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_playerCamera->getRenderer(), loadedSurface);

    if(texture == nullptr){
        printf( "Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError() );
        loadTextureSuccess = false;
    }

    if(!loadTextureSuccess){
        return loadTextureSuccess;
    }

    setTexture(texture);

    //delete loadedSurface;

    return loadTextureSuccess;
}

void Sprite::setTexture(SDL_Texture *texture){
    _texture = texture;
}

void Sprite::render() {
    uint8_t red, green, blue, alpha;
    SDL_BlendMode blendMode;

    getColorMod(&red, &green, &blue);
    getAlphaMod(&alpha);
    getBlendMode(&blendMode);

    SDL_SetTextureColorMod(_texture, red, green, blue);
    SDL_SetTextureAlphaMod(_texture, alpha);
    SDL_SetTextureBlendMode(_texture, blendMode);

    SDL_Rect *sourceRect, *destinationRect;
    SDL_Point *centre;
    long double angle;
    SDL_RendererFlip flip;

    getSourceRect(sourceRect);
    getDestinationRect(destinationRect);
    getRotationCentre(centre);
    getRotationAngle(&angle);
    getFlip(&flip);
    SDL_RenderCopyEx(_playerCamera->getRenderer(), _texture, sourceRect, destinationRect,
                     static_cast<double>(angle), centre, flip);
    delete sourceRect;
    delete destinationRect;
}

void Sprite::getDestinationRect(SDL_Rect *&destinationRect) {
    destinationRect = nullptr;
}


void Sprite::getSourceRect(SDL_Rect *&sourceRect) {
    sourceRect = nullptr;
}

void Sprite::getRotationAngle(long double *angle) {
    *angle = 0;
}

void Sprite::getRotationCentre(SDL_Point *&centre) {
    centre = nullptr;
}

void Sprite::getFlip(SDL_RendererFlip *flip) {
    *flip = SDL_FLIP_NONE;
}

void Sprite::getColorMod(unsigned char *red, unsigned char *green, unsigned char *blue) {
    *red = 255;
    *green = 255;
    *blue = 255;
}

void Sprite::getAlphaMod(unsigned char *alpha) {
    *alpha = 255;
}

void Sprite::getBlendMode(SDL_BlendMode *blendMode) {
    *blendMode = SDL_BLENDMODE_BLEND;
}


#endif //SDL2TEST_SPRITEBASE_H