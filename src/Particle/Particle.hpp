#pragma once

#include <SDL.h>
#include <iostream>

#include "../Random/Random.hpp"
#include "../app.config.hpp"

class Particle {
private:
    SDL_Renderer *renderer = nullptr;
    float _x{};
    float _y{};
    float _velocityX{};
    float _velocityY{};

public:
    Particle(int x, int y, SDL_Renderer *renderer);

    Particle();

    void Draw(SDL_Renderer *pSdlRenderer) const;

    void Move(double deltaTime);

    float GetX() const;

    float GetY() const;
};