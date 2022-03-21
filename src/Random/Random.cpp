#include "Random.hpp"

float Random::Range(float min, float max) {
    return (float) rand() / (float) RAND_MAX * (max - min) + min;
}

float Random::RandomDirection() {
    const float randomNum = Random::Range(-1, 1);

    if (randomNum > 0) return 1;
    if (randomNum < 0) return -1;

    return 0;
}