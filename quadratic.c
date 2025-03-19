#include "quadratic.h"
#include <math.h>

double is_zero(double x, double eps) {
  if (x == -0 || fabs(x) < eps)
    return 0;
  return x;
}

int roots(double a, double b, double c, double eps, double epsD, double *x1, double *x2) {

  double D = b * b - 4 * a * c;
  D = is_zero(D, epsD);

  if (D < 0)
    return No_Substantial_Roots;
  else if (fabs(a) < eps)
    return Not_Quadratic_Equation;
  else if (fabs(D) < epsD) {
    *x1 = is_zero(-b / (2 * a), eps);
    return One_Roots;
  } else {
    *x1 = (-b + sqrt(D)) / (2 * a);
    *x2 = c / (*x1 * a);
    if (fabs(*x1 - *x2) < eps)
      return One_Roots;
    return Two_Roots;
  }
}