#ifndef SDL2TEST_ANIMATED_TEXTURE_H
#define SDL2TEST_ANIMATED_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <vector>

class AnimatedTexture {
public:
    //Initializes variables
    explicit AnimatedTexture(SDL_Renderer *renderer);

    //Deallocates memory
    ~AnimatedTexture();

    //Loads image at specified path
    bool loadTexture(const char* file, std::vector<SDL_Texture*> &textures,
                     int columns = 1, int rows = 1, int textureChangeTime = 0);

    //Renders texture at given point
    void render();

    void setSize(double width, double height);

    void setPosition(double xMultiplier, double yMultiplier);

    void setRotationAngle(double angle);

    void setRotationCenter(double xMultiplier, double yMultiplier);

    void setFlip(SDL_RendererFlip flip);

    void setColorMod(unsigned char red, unsigned char green, unsigned char blue);

    void setAlphaMod(unsigned char alpha);

    void setBlendMode(SDL_BlendMode blendMode);



protected:
    //Deallocates texture
    void free();

private:
    SDL_Renderer* _renderer;

    //The actual hardware texture
    SDL_Texture* _texture;

    SDL_Point _center{};

    SDL_BlendMode _blendMode;

    SDL_RendererFlip _flip;

    //Image dimensions
    int _width, _height, _x, _y, _columns, _rows, _textureChangeTime, _red, _green, _blue, _alpha;

    double _angle;

    bool _centerDefined;



    [[nodiscard]] int getFrameNumber() const;

    void getSourceRect(SDL_Rect &sourceRect) const;
    void getDestinationRect(SDL_Rect &destinationRect) const;
};

AnimatedTexture::AnimatedTexture(SDL_Renderer *renderer) {
    _renderer = renderer;

    _texture = nullptr;

    _center = {0, 0};

    _blendMode = SDL_BLENDMODE_BLEND;

    _flip = SDL_FLIP_NONE;

    _width = 0;
    _height = 0;
    _x = 0;
    _y = 0;
    _columns = 0;
    _rows = 0;
    _textureChangeTime = 0;
    _red = 255;
    _green = 255;
    _blue = 255;
    _alpha = 255;

    _angle = 0;

    _centerDefined = false;
}

void AnimatedTexture::free() {
    if(_texture != nullptr){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        _width = 0;
        _height = 0;
    }
}

AnimatedTexture::~AnimatedTexture() {
    free();
}

bool AnimatedTexture::loadTexture(const char *file, std::vector<SDL_Texture*> &textures,
                                  const int columns, const int rows, const int textureChangeTime) {
    _columns = columns;
    _rows = rows;
    _textureChangeTime = textureChangeTime;

    bool loadTextureSuccess = true;

    SDL_Surface* loadedSurface = IMG_Load(file);

    if(loadedSurface == nullptr){
        printf( "Unable to load image %s! SDL Error: %s\n", file, SDL_GetError() );
        loadTextureSuccess = false;
    }

    if(!loadTextureSuccess){
        return loadTextureSuccess;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);

    if(texture == nullptr){
        printf( "Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError() );
    }

    textures.push_back(texture);

    _texture = texture;

    return loadTextureSuccess;
}

void AnimatedTexture::setSize(double widthMultiplier, double heightMultiplier) {
    int windowWidth, windowHeight, minWindowDimension;
    SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);
    minWindowDimension = std::min(windowWidth, windowHeight);

    _width = (int)((double)minWindowDimension*widthMultiplier);
    _height = (int)((double)minWindowDimension*heightMultiplier);
}

void AnimatedTexture::getDestinationRect(SDL_Rect &destinationRect) const {
    destinationRect.x = _x;
    destinationRect.y = _y;
    destinationRect.w = _width;
    destinationRect.h = _height;
}

void AnimatedTexture::render() {
    SDL_SetTextureColorMod(_texture, _red, _green, _blue);
    SDL_SetTextureAlphaMod(_texture, _alpha);
    SDL_SetTextureBlendMode(_texture, _blendMode);

    SDL_Rect sourceRect, destinationRect;
    getSourceRect(sourceRect);
    getDestinationRect(destinationRect);
    //printf("%d, %d, %d \n", _center.x, _center.y, _centerDefined);
    SDL_RenderCopyEx(_renderer, _texture, &sourceRect, &destinationRect, _angle,
                     _centerDefined ? &_center : nullptr, _flip);
}

void AnimatedTexture::getSourceRect(SDL_Rect &sourceRect) const {
    int frameNumber = getFrameNumber();
    int row = frameNumber / _columns;
    int column = frameNumber % _columns;
    int imageWidth, imageHeight;
    SDL_QueryTexture(_texture, nullptr, nullptr, &imageWidth, &imageHeight);
    sourceRect.w = (imageWidth / _columns);
    sourceRect.x = column * sourceRect.w;
    sourceRect.h = (imageHeight / _rows);
    sourceRect.y = row * sourceRect.h;
}

int AnimatedTexture::getFrameNumber() const {
    uint64_t tick = SDL_GetTicks64();
    tick /= _textureChangeTime;
    int framesAmount = _rows * _columns;
    tick %= framesAmount;
    return (int)tick;
}

void AnimatedTexture::setPosition(double xMultiplier, double yMultiplier) {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);

    _x = (int)((double)windowWidth * xMultiplier);
    _y = (int)((double)windowHeight * yMultiplier);
}

void AnimatedTexture::setColorMod(unsigned char red, unsigned char green, unsigned char blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

void AnimatedTexture::setAlphaMod(unsigned char alpha) {
    _alpha = alpha;
}

void AnimatedTexture::setBlendMode(SDL_BlendMode blendMode) {
    _blendMode = blendMode;
}

void AnimatedTexture::setRotationAngle(double angle) {
    _angle = angle;
}

void AnimatedTexture::setRotationCenter(double xMultiplier, double yMultiplier){
    int windowWidth, windowHeight, minWindowDimension;
    SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);
    _center = SDL_Point({(int)((double)windowWidth * xMultiplier), (int)((double)windowHeight * yMultiplier)});
    _centerDefined = true;
}

void AnimatedTexture::setFlip(SDL_RendererFlip flip) {
    _flip = flip;
}

#endif //SDL2TEST_ANIMATED_TEXTURE_H
