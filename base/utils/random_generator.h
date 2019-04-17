#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__

#include <random>

class RandomGenerator {
 public:
  RandomGenerator();
  ~RandomGenerator();

  /*
  * Generate random number include (min ... max - 1) value
  */
  int Get(int min, int max);
 private:
  std::random_device rand;
};

#endif // __RANDOM_GENERATOR_H__