#include "integral.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#define EXP 2.7182818284590452354
#define M_PI 3.14159265358979323846

double cosx(double x) { return cos(x); }

double xsquared(double x) { return x * x; }

double expx(double x) { return pow(EXP, x); }

double lgx(double x) { return log10(M_PI); }

void integral_test_cosx() {
  double a = 0, b = 1;
  int step = 10000;
  double res = integral(a, b, step, cosx);
  assert(fabs(res - 0.84147) < 0.00001);
}

void integral_test_xsquared() {
  double a = 0, b = 1;
  int step = 10000;
  double res = integral(a, b, step, xsquared);
  assert(fabs(res - 0.33333) < 0.00001);
}

void integral_test_expx() {
  double a = 0, b = 1;
  int step = 10000;
  double res = integral(a, b, step, expx);
  assert(fabs(res - 1.71828) < 0.00001);
}

void integral_test_lgx() {
  double a = 0, b = 1;
  int step = 10000;
  double res = integral(a, b, step, lgx);
  assert(fabs(res - 0.49715) < 0.00001);
}

int main() {
  integral_test_cosx();
  integral_test_xsquared();
  integral_test_expx();
  integral_test_lgx();
  return 0;
}
