#include "quadratic.h"
#include <math.h>

int roots(double a, double b, double c, double eps, double *x1, double *x2) {

  double D = b * b - 4 * a * c;

  if (D < -eps)
    return No_Real_Roots;
  else if (fabs(a) < eps)
    return Not_Quadratic_Equation;
  else if (fabs(D) < eps) {
    *x1 = -b / (2 * a);
    return One_Roots;
  } else {
    *x1 = (-b + sqrt(D)) / (2 * a);
    *x2 = c / (*x1 * a);
    return Two_Roots;
  }
}
