#ifndef SDL2TEST_TEST_MAP_GENERATOR_H
#define SDL2TEST_TEST_MAP_GENERATOR_H

#include <SDL.h>
#include <cmath>
#include "Camera.h"

const long long INITIAL_SPIN = 10000, PAINT_RAD = 3;

class TestMapGenerator{
public:
    [[maybe_unused]] explicit TestMapGenerator(Camera* playerCamera);

    TestMapGenerator(Camera* playerCamera, long double seed);

    [[maybe_unused]] void setSeed(long double seed);

    void generateMap(SDL_Texture *&texture, int32_t w, int32_t h);

    void generateRoad(std::vector<std::vector<int>> &m, int32_t w, int32_t h);

    void generateSegment(std::vector<std::vector<int>> &m, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t w, int32_t h);

    [[maybe_unused]] void testGenerator();

private:
    [[maybe_unused]] long double _seed, _last;

    Camera* _playerCamera;

    static long double generateNext(long double a);

    long double getNext();

    void spin(long long n);
};

[[maybe_unused]] TestMapGenerator::TestMapGenerator(Camera* playerCamera) {
    _seed = 0;
    _last = 0;
    _playerCamera = playerCamera;
}

TestMapGenerator::TestMapGenerator(Camera* playerCamera, long double seed) {
    _seed = seed;
    _last = seed;
    _playerCamera = playerCamera;
    spin(INITIAL_SPIN);
}

[[maybe_unused]] void TestMapGenerator::setSeed(long double seed) {
    _seed = seed;
    _last = seed;
    spin(INITIAL_SPIN);
}

void TestMapGenerator::generateSegment(std::vector<std::vector<int>> &m, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t w, int32_t h) {

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



    for(std::pair<long double, int32_t> step: route){
        int32_t direction = step.second;

        m[x][y] = 1;

        if(direction){
            x += multiplierX;
        }
        else{
            y += multiplierY;
        }
        for(int i = x - PAINT_RAD; i <= x + PAINT_RAD; i++){
            for(int j = y - PAINT_RAD; j <= y + PAINT_RAD; j++){
                if(i >= 0 && i < w && j >= 0 && j < h && m[i][j] != 1 && m[i][j] != 2){
                    m[i][j] = 3;
                }
            }
        }
    }

    m[x][y] = 1;

    for(int i = x - PAINT_RAD; i <= x + PAINT_RAD; i++){
        for(int j = y - PAINT_RAD; j <= y + PAINT_RAD; j++){
            if(i >= 0 && i < w && j >= 0 && j < h && m[i][j] != 1){
                m[i][j] = 2;
            }
        }
    }
}

void TestMapGenerator::generateMap(SDL_Texture *&texture, int32_t w, int32_t h) {

    std::vector<std::vector<int>> m(w);
    for(auto &i : m) i.resize(h);


    auto roads = 1 + getNext() * 4.0;
    for(auto i = 0; i < roads; i++){
        generateRoad(m, w, h);
    }

    SDL_Surface* map = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(map, nullptr, SDL_MapRGB(map->format, 255, 0, 0));
    const uint32_t color = SDL_MapRGB(map->format, 0, 255, 0);
    const uint32_t color2 = SDL_MapRGB(map->format, 0, 255, 255);
    const uint32_t color3 = SDL_MapRGB(map->format, 255, 255, 0);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int col = m[x][y];
            SDL_Rect pixel = SDL_Rect({x, y, 1, 1});
            if(col == 1){
                SDL_FillRect(map, &pixel, color);
            }
            if(col == 2){
                SDL_FillRect(map, &pixel, color2);
            }
            if(col == 3){
                SDL_FillRect(map, &pixel, color3);
            }
        }
    }

    texture = SDL_CreateTextureFromSurface(_playerCamera->getRenderer(), map);
}

long double TestMapGenerator::generateNext(long double a) {
    a += 2351;
    a *= 1125899839733759;
    a /= 274876858367;
    auto x = a - static_cast<int64_t>(a);
    return x;
}

[[maybe_unused]] void TestMapGenerator::testGenerator() {
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

void TestMapGenerator::spin(long long int n) {
    for(long long i = 0; i < n; i++){
        getNext();
    }
}

void TestMapGenerator::generateRoad(std::vector<std::vector<int>> &m, int32_t w, int32_t h) {
    auto stops =  0 + static_cast<int32_t>(getNext() * 3.0);

    int32_t x0 = 0;
    int32_t y0 = 0;
    int32_t x1 = 0;
    int32_t y1 = 0;

    for(int stop = 0; stop < stops; stop++){
        do{
            x1 = static_cast<int32_t>(getNext() * w);

            y1 = static_cast<int32_t>(getNext() * h);

        }
        while(m[x1][y1] != 0);

        if(x0 == x1 || y0 == y1){
            continue;
        }

        generateSegment(m, x0, y0, x1, y1, w, h);

        x0 = x1;
        y0 = y1;
    }
    if(x1 != w - 1 && y1 != h - 1) generateSegment(m, x1, y1, w - 1, h - 1, w, h);

}


#endif //SDL2TEST_TEST_MAP_GENERATOR_H
