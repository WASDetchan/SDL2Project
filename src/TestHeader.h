//
// Created by yarik on 27.08.2023.
//

#ifndef SDL2TEST_TESTHEADER_H
#define SDL2TEST_TESTHEADER_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

class TestClass{
public:
    TestClass();

    void setRect(SDL_Rect* rect);

    void setWH(int w, int h);

    void printRect();

private:
    SDL_Rect* _rect;
};

TestClass::TestClass() {
    _rect = nullptr;
}

void TestClass::setRect(SDL_Rect *rect) {
    _rect = rect;
}

void TestClass::setWH(int w, int h) {
    _rect->h = h;
    _rect->w = w;
}

void TestClass::printRect() {
    if(_rect == nullptr){
        printf("nullptr\n");
    }
    else{
        printf("%d, %d\n", _rect->w, _rect->h);
    }
}

#endif //SDL2TEST_TESTHEADER_H
