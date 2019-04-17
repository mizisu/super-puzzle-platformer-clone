#include "base/utils/random_generator.h"
#include <random>

RandomGenerator::RandomGenerator() {}

RandomGenerator::~RandomGenerator() {}

int RandomGenerator::Get(int min, int max) {
  std::uniform_int_distribution<int> range(min, max - 1);
  return range(rand);
}