#include "Particle.hpp"

Particle::Particle(int x, int y, SDL_Renderer *renderer) {
    this->renderer = renderer;

    this->_x = x;
    this->_y = y;

    this->_velocityX = Random::Range(MIN_PARTICLE_VELOCITY, MAX_PARTICLE_VELOCITY);
    this->_velocityY = Random::Range(MIN_PARTICLE_VELOCITY, MAX_PARTICLE_VELOCITY);
}

Particle::Particle()
= default;

void Particle::Draw(SDL_Renderer *pSdlRenderer) const {
    SDL_Rect rect;

    rect.w = PARTICLE_SIZE;
    rect.h = PARTICLE_SIZE;
    rect.x = this->_x;
    rect.y = this->_y;

    SDL_SetRenderDrawColor(pSdlRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(pSdlRenderer, &rect);
}

void Particle::Move(double deltaTime) {
    if (this->_x >= WINDOW_WIDTH || this->_x <= 0) {
        this->_velocityX *= -1;
    }

    if (this->_y >= WINDOW_HEIGHT || this->_y <= 0) {
        this->_velocityY *= -1;
    }

    this->_x += this->_velocityX * deltaTime;
    this->_y += this->_velocityY * deltaTime;
}

float Particle::GetX() const {
    return this->_x;
}

float Particle::GetY() const {
    return this->_y;
}
