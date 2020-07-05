#include "helper_functions.h"
int HelperFunctions::random_int(int a, int b) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(a, b);
  return distribution(generator);
}