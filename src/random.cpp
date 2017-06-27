#include "random.h"
#include <random>

int Random::generate(int lower, int upper) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(lower, upper);
  return dist(gen);
}
