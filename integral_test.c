#include "integral.h"
#include <assert.h>
#include <stdio.h>

void integral_test_cosx() {
  double a = 0, b = 1;
  double res = integral(a, b, cosx);
  assert(fabs(res - 0.84147) < 0.00001);
}

void integral_test_xsquared() {
  double a = 0, b = 1;
  double res = integral(a, b, xsquared);
  assert(fabs(res - 0.33333) < 0.00001);
}

void integral_test_expx() {
  double a = 0, b = 1;
  double res = integral(a, b, expx);
  assert(fabs(res - 1.71828) < 0.00001);
}

void integral_test_lgx() {
  double a = 0, b = 1;
  double res = integral(a, b, lgx);
  assert(fabs(res - 0.49715) < 0.00001);
}

int main() {
  integral_test_cosx();
  integral_test_xsquared();
  integral_test_expx();
  integral_test_lgx();
  return 0;
}