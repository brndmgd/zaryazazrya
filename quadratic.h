#include <math.h>

#define No_Substantial_Roots -1
#define Not_Quadratic_Equation -2
#define One_Roots 1
#define Two_Roots 2

double is_zero(double x, double eps);

int roots(double a, double b, double c, double eps, double epsD, double *x1,
          double *x2);
