#include "integral.h"

double integral(double a, double b, int step, double (*f)(double)) {
  double square = 0;
  if (step <= 0) {
    return -1;
  }

  double n = (b - a) / step;

  for (int i = 0; i < step; i++) {
    square += 0.5 * n * (f(a + n * i) + f(a + n * (i + 1)));
  }

  return square;
}
