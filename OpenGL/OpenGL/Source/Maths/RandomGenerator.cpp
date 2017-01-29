#include "stdafx.h"

#include "Maths/RandomGenerator.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  RandomGenerator::RandomGenerator()
  {
  }

  //------------------------------------------------------------------------------------------------
  RandomGenerator::RandomGenerator(size_t seed)
  {
    srand(seed);
  }

  //------------------------------------------------------------------------------------------------
  float RandomGenerator::generate(float min, float max) const
  {
    float zeroToOne = (float)rand() / RAND_MAX;
    return min + (max - min) * zeroToOne;
  }
}