#ifndef SDL2TEST_PARTICLES_H
#define SDL2TEST_PARTICLES_H

#include <SDL.h>
#include "AnimatedTexture.h"

//(SDL_Texture* texture, int xPosition, int yPosition,
//double xSpeed, double ySpeed,
//double xAcceleration, double yAcceleration,
//double rotationAngle, double rotationSpeed,
//unsigned char alpha,double fadeOutSpeed);

class Particle:AnimatedTexture{
public:
    explicit Particle(SDL_Renderer *renderer);

    ~Particle();


};

Particle::Particle(SDL_Renderer *renderer) : AnimatedTexture(renderer) {

}

Particle::~Particle() {
    free();
}

#endif //SDL2TEST_PARTICLES_H
