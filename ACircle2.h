#ifndef SDL2TEST_ACIRCLE2_H
#define SDL2TEST_ACIRCLE2_H

#include "WorldSprite.h"

const double COLOR_CHANE_SPEED = 0.1;
const double TEXTURE_CHANGE_SPEED = 0.01;

class ACircle2 : public WorldSprite{
public:
    explicit ACircle2(Camera *playerCamera);
private:

    SDL_Point *_centre;

    [[nodiscard]] static int getFrameNumber() ;

    void getColorMod(unsigned char *red, unsigned char *green, unsigned char *blue) override;

    void getSourceRect(SDL_Rect *&sourceRect) override;

    void getRotationAngle(long double *angle) override;
};

void ACircle2::getColorMod(unsigned char *red, unsigned char *green, unsigned char *blue) {
    auto tick = SDL_GetTicks64();
    tick = (unsigned long long)(COLOR_CHANE_SPEED * (double)tick);
    tick %= 768;
    if(tick < 256){
        *red = tick;
        *green = 255 - tick;
        *blue = 0;
    } else if(tick < 512){
        tick -= 256;
        *red = 255 - tick;
        *green = 0;
        *blue = tick;
    } else{
        tick -= 512;
        *red = 0;
        *green = tick;
        *blue = 255 - tick;
    }
}

int ACircle2::getFrameNumber() {
    uint64_t tick = SDL_GetTicks64();
    tick = static_cast<uint64_t>(static_cast<double>(tick)  * TEXTURE_CHANGE_SPEED);
    int framesAmount = 1 * 4;
    tick %= framesAmount;
    return (int)tick;
}

void ACircle2::getSourceRect(SDL_Rect *&sourceRect) {
    int frameNumber = getFrameNumber();
    int row = frameNumber / 4;
    int column = frameNumber % 4;
    int imageWidth, imageHeight;
    SDL_QueryTexture(_texture, nullptr, nullptr, &imageWidth, &imageHeight);
    sourceRect = new SDL_Rect({column * (imageWidth / 4), row * (imageHeight / 1), (imageWidth / 4), (imageHeight / 1)});
}

ACircle2::ACircle2(Camera *playerCamera) : WorldSprite(playerCamera) {
    _centre = nullptr;
}

void ACircle2::getRotationAngle(long double *angle) {
    auto tick = static_cast<long double>(SDL_GetTicks64() % 3000);
    *angle = tick / 3000 * 360;
}

#endif //SDL2TEST_ACIRCLE2_H
