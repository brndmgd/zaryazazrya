#include "integral.h"
#define EXP 2.7182818284590452354
#define M_PI 3.14159265358979323846

double cosx(double x) { return cos(x); }

double xsquared(double x) { return x * x; }

double expx(double x) { return pow(EXP, x); }

double lgx(double x) { return log10(M_PI); }

double integral(double a, double b, double (*f)(double)) {
  double square = 0;
  double n = (b - a) / 10000;

  for (int i = 0; i < 10000; i++) {
    square += 0.5 * n * (f(a + n * i) + f(a + n * (i + 1)));
  }

  return square;
}
