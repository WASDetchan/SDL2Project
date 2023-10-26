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

    void generateMap(SDL_Texture *&texture, int32_t w, int32_t h) const;

private:
    long double _seed;

    static long double generateNext(long double a);
};

TestMapGenerator::TestMapGenerator(Camera* playerCamera) {
    _seed = 0;
}

TestMapGenerator::TestMapGenerator(Camera* playerCamera, long double seed) {
    _seed = seed;
}

void TestMapGenerator::setSeed(long double seed) {
    _seed = seed;
}

void TestMapGenerator::generateMap(SDL_Texture *&texture, int32_t w, int32_t h) const {
    SDL_Surface* map = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    SDL_FillRect(map, nullptr, SDL_MapRGB(map->format, 255, 0, 0));

    int32_t x = 0, y = 0;

    long double a = _seed, xChangeChance = static_cast<long double>(w) / (h + w);

    auto color = SDL_MapRGB(map->format, 0, 255, 0);

    while(x < w || y < h){
        SDL_Rect pixel = SDL_Rect({x, y, 1, 1});
        SDL_FillRect(map, &pixel, color);
        a = generateNext(a);
        if(a <= xChangeChance || y >= h){
            x++;
        }
        if(a > xChangeChance || x >= w){
            y++;
        }
    }
}

long double TestMapGenerator::generateNext(long double a) {
    a *= 14287547854223;
    a /= 778472857548;
    return a - static_cast<int64_t>(a);
}


#endif //CMAKE_INSTALL_CMAKE_TESTMAPGENERATOR_H
