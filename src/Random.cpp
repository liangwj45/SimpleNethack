#include "../include/Random.hpp"

std::default_random_engine e(time(0));

int rand(const int s, const int t) {
  std::uniform_int_distribution<int> r(s, t);
  return r(e);
}