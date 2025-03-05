#include <math.h>
#include "quadratic.h"

double is_zero(double x, double eps) {
    if (x == -0 || fabs(x) < eps) return 0;
    return x;
}

int roots(double a, double b, double c, double eps, double* x1, double* x2) {
    
    double D = b * b - 4 * a * c;
    D = is_zero(D, 1e-7);

    if (D < 0 || fabs(a) < 1e-7) return 0;
    else if (fabs(D) < 1e-7) {
        *x1 = is_zero(-b/(2*a), eps);
        return 1;
    }
    else {
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = c / ( *x1 * a);
        if(fabs(*x1 - *x2) < eps) return 1;
        return 2;
    }
}