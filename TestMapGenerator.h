#ifndef SDL2TEST_TESTMAPGENERATOR_H
#define SDL2TEST_TESTMAPGENERATOR_H

#include <SDL.h>
#include <cmath>
#include "Camera.h"

class TestMapGenerator{
public:
    explicit TestMapGenerator(Camera* playerCamera);

    TestMapGenerator(Camera* playerCamera, long double seed);

    void setSeed(long double seed);

    void generateMap(SDL_Texture *&texture, int32_t w, int32_t h);

    void generateRoad(SDL_Surface *map, int32_t x0, int32_t y0, int32_t x1, int32_t y1);

    void testGenerator();

private:
    long double _seed, _last;

    Camera* _playerCamera;

    static long double generateNext(long double a);

    long double getNext();
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

void TestMapGenerator::generateRoad(SDL_Surface *map, int32_t x0, int32_t y0, int32_t x1, int32_t y1) {

    int32_t deltaX = abs(x1 - x0);
    int32_t deltaY = abs(y1 - y0);

    int32_t steps = deltaX + deltaY;

    int32_t multiplierX = deltaX / (x1 - x0);
    int32_t multiplierY = deltaY / (y1 - y0);

    std::vector < std::pair < long double, int32_t >> route(steps);
    std::fill(route.begin(), route.begin() + deltaX, std::make_pair(0, 1));



    for(int step = 0; step < steps; step++){
        route[step].first = getNext();
    }
    std::stable_sort(route.begin(), route.end());

    int32_t x = x0;
    int32_t y = y0;

    const uint32_t color = SDL_MapRGB(map->format, 0, 255, 0);

    for(std::pair<long double, int32_t> step: route){
        int32_t direction = step.second;

        SDL_Rect pixel = SDL_Rect({x, y, 1, 1});

        if(direction){
            x += multiplierX;
        }
        else{
            y += multiplierY;
        }

        SDL_FillRect(map, &pixel, color);
    }

    SDL_Rect pixel = SDL_Rect({x, y, 1, 1});

    SDL_FillRect(map, &pixel, color);
}

void TestMapGenerator::generateMap(SDL_Texture *&texture, int32_t w, int32_t h) {
    SDL_Surface* map = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    SDL_FillRect(map, nullptr, SDL_MapRGB(map->format, 255, 0, 0));

    auto stops = static_cast<int32_t>(getNext() * 6);

    int32_t x0 = 0;
    int32_t y0 = 0;
    int32_t x1 = 0;
    int32_t y1 = 0;

    for(int stop = 0; stop < stops; stop++){
        x1 = static_cast<int32_t>(getNext() * w);

        y1 = static_cast<int32_t>(getNext() * h);

        if(x0 == x1 || y0 == y1){
            std::cerr << "SAME\n";
            continue;
        }

        generateRoad(map, x0, y0, x1, y1);

        x0 = x1;
        y0 = y1;
    }

    generateRoad(map, x1, y1, w - 1, h - 1);

    texture = SDL_CreateTextureFromSurface(_playerCamera->getRenderer(), map);
}

long double TestMapGenerator::generateNext(long double a) {
    a += 2351;
    a *= 1125899839733759;
    a /= 274876858367;
    auto x = a - static_cast<int64_t>(a);
    std::cerr << x << std::endl;
    return x;
}

void TestMapGenerator::testGenerator() {
    auto a = getNext();
    int m[10] = {};
    const int n = 10000;
    for(int i = 0; i < n; i++){
        m[static_cast<int>(a*10)]++;
        a = getNext();
    }
    for(auto i : m){
        std::cout << static_cast<long double>(i) / n << std::endl;
    }
}

long double TestMapGenerator::getNext() {
    _last = generateNext(_last);
    return _last;
}


#endif //SDL2TEST_TESTMAPGENERATOR_H
