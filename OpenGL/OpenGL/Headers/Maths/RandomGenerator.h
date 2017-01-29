#pragma once

#include <random>


namespace OpenGL
{

class RandomGenerator
{
  public:
    RandomGenerator();
    RandomGenerator(size_t seed);

    void seed(size_t seed) const { srand(seed); }

    float generate(float min = 0, float max = 1) const;
};

}