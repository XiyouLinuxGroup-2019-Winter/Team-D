#include <stdio.h>

void larger_of(double *x, double *y);

int main()
{
    double a, b;
    double *x = &a, *y = &b;
    *x = 1, *y = 2; 
    larger_of(x, y);
    return 0;
}

void larger_of(double *x, double *y) {
    double max = *x;
    if (max < *y) {
        max = *y;
    }
    *x = max;
    *y = max;
    printf("%lf %lf\n", *x, *y);
}
