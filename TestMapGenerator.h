//
// Created by yarik on 26.10.2023.
//

#ifndef CMAKE_INSTALL_CMAKE_TESTMAPGENERATOR_H
#define CMAKE_INSTALL_CMAKE_TESTMAPGENERATOR_H

#include <SDL.h>
#include "Camera.h"

class TestMapGenerator{
public:
    explicit TestMapGenerator(Camera* playerCamera);

    TestMapGenerator(Camera* playerCamera, long double seed);

    void setSeed(long double seed);

    void generateMap(SDL_Texture *&texture, int32_t w, int32_t h);

    void generateRoad(SDL_Surface *map, int32_t w, int32_t h);

private:
    long double _seed, _last;

    Camera* _playerCamera;

    static long double generateNext(long double a);
};

TestMapGenerator::TestMapGenerator(Camera* playerCamera) {
    _seed = 0;
    _last = 0;
    _playerCamera = playerCamera;
}

TestMapGenerator::TestMapGenerator(Camera* playerCamera, long double seed) {
    _seed = seed;
    _last = seed;
    _playerCamera = playerCamera;
}

void TestMapGenerator::setSeed(long double seed) {
    _seed = seed;
    _last = seed;
}

void TestMapGenerator::generateRoad(SDL_Surface *map, int32_t w, int32_t h) {
    int32_t x = 0, y = 0;

    long double a = _last, xChangeChance = static_cast<long double>(w) / (h + w);

    auto color = SDL_MapRGB(map->format, 0, 255, 0);

    SDL_Rect pixel = SDL_Rect({x, y, 1, 1});
    SDL_FillRect(map, &pixel, color);

    while(x < w - 1 || y < h - 1){
        a = generateNext(a);
        if((a <= xChangeChance || y >= h - 1) && x < w - 1){
            x++;
        }
        if((a > xChangeChance || x >= w - 1) && y < h - 1){
            y++;
        }

        pixel = SDL_Rect({x, y, 1, 1});
        SDL_FillRect(map, &pixel, color);
    }

    _last = a;
}

void TestMapGenerator::generateMap(SDL_Texture *&texture, int32_t w, int32_t h) {
    SDL_Surface* map = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    SDL_FillRect(map, nullptr, SDL_MapRGB(map->format, 255, 0, 0));

    generateRoad(map, w, h);
    generateRoad(map, w, h);
    generateRoad(map, w, h);

    texture = SDL_CreateTextureFromSurface(_playerCamera->getRenderer(), map);
}

long double TestMapGenerator::generateNext(long double a) {
    a *= 14287547854223;
    a /= 778472857548;
    return a - static_cast<int64_t>(a);
}


#endif //CMAKE_INSTALL_CMAKE_TESTMAPGENERATOR_H
