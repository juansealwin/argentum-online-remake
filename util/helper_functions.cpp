#include "helper_functions.h"
int HelperFunctions::random_int(int a, int b) {
  return rand()%(b-a + 1) + a;
}

double HelperFunctions::distance(double x1, double x2, double y1, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

unsigned int HelperFunctions::difference(int x, int y) {
  return (unsigned int)abs(x - y);
}
