#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <random>
#include <chrono>
namespace HelperFunctions {
  //devuelve un entero random entre a y b
  //PRE: b debe ser mayor que a
  int random_int(int a, int b);
  double distance(double x1, double x2, double y1, double y2);
  unsigned int difference(int x, int y);
}
#endif  // HELPER_FUNCTIONS_H
