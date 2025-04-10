#include "quadratic.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void square_test_1() {
  double x1, x2;
  double a = 1, b = 0, c = -1, eps = 1e-15, epsQ = 1e-15;
  int res = roots(a, b, c, eps, &x1, &x2);

  assert(res == 2 && fabs(x1 - 1) < epsQ && fabs(x2 + 1) < epsQ);
}

void square_test_2() {
  double x1, x2;
  double a = 1, b = 0, c = 0, eps = 1e-15, epsQ = 1e-15;
  int res = roots(a, b, c, eps, &x1, &x2);

  assert(res == 1 && fabs(x1) < epsQ);
}

void square_test_3() {
  double x1, x2;
  double a = 1, b = 0, c = 1, eps = 1e-15, epsQ = 1e-15;
  int res = roots(a, b, c, eps, &x1, &x2);

  assert(res == -1);
}

void square_test_4() {
  double x1, x2;
  double a = 1, b = 0, c = -1e-7, eps = 1e-7, epsQ = 1e-4;
  int res = roots(a, b, c, eps, &x1, &x2);
  printf("x1=%f, x2=%f\n", x1, x2);
  assert(res == 2 && fabs(x1 - 3e-4) < epsQ && fabs(x2 + 3e-4) < epsQ);
}

void square_test_5() {
  double x1, x2;
  double a = 1, b = -1e+10, c = -1, eps = 1e-11, epsQ = 1e-11;
  int res = roots(a, b, c, eps, &x1, &x2);

  assert(res == 2 && fabs(x1 - 1e+10) < epsQ && (x2 + 1e-10) < epsQ);
}

void square_test_6() {
  double x1, x2;
  double a = 1, b = 0, c = -1e-8, eps = 1e-7, epsQ = 1e-7;
  int res = roots(a, b, c, eps, &x1, &x2);

  assert(res == 1 && fabs(x1) < epsQ);
}

int main() {

  square_test_1();
  square_test_2();
  square_test_3();
  square_test_4();
  square_test_5();
  square_test_6();
  printf("square success\n");

  return 0;
}
