#define SDL_MAIN_HANDLED

#include "app.config.hpp"

#include <SDL_main.h>

#include <iostream>
#include <cmath>
#include <ctime>

#include "Particle/Particle.hpp"

void InitializeParticles(Particle *dots, SDL_Renderer *renderer) {
    for (int i = 0; i < PARTICLES_COUNT; i++) {
        dots[i] = Particle(
                (int) std::floor((float) rand() / RAND_MAX * WINDOW_WIDTH),
                (int) std::floor((float) rand() / RAND_MAX * WINDOW_HEIGHT),
                renderer
        );
    }
}

int GetDisplayRefreshRate() {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);

    return mode.refresh_rate;
}

int main(int argc, char **argv) {
    SDL_SetMainReady();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    int refreshRate = {0};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
    } else {
        srand((unsigned) time(nullptr));

        refreshRate = GetDisplayRefreshRate();

        window = SDL_CreateWindow(
                "Particles Animation",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        renderer =
                SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    Particle particles[PARTICLES_COUNT];
    InitializeParticles(particles, renderer);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    bool quit = false;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    while (!quit) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double) ((NOW - LAST) * 1000 / (double) SDL_GetPerformanceFrequency());

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;
        }

        for (auto &particle: particles) {
            particle.Draw(renderer);
            particle.Move(deltaTime);
        }

        for (const auto & particle : particles) {
            for (const auto & j : particles) {
                const float distance = std::sqrt(std::pow(j.GetX() - particle.GetX(), 2) +
                                                 std::pow(j.GetY() - particle.GetY(), 2));

                if (distance <= MAX_DRAWING_DISTANCE) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawLine(renderer, particle.GetX(), particle.GetY(), j.GetX(),
                                       j.GetY());
                }
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / refreshRate);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}