#include <stdio.h>

void fun(double *a, double *b, double *c);

int main()
{
    double a, b = 4, c = 1;
    scanf("%lf %lf %lf", &a, &b, &c);
    fun(&a, &b, &c);
    printf("%lf %lf %lf\n", a, b ,c);
    return 0;
}

void fun(double *a, double *b, double *c) {
    double max = *a;
    double min = *a;
    if (max < *b) {
        max = *b;
    }
    if (max < *c) {
        max = *c;
    }
    if (min > *b) {
        min = *b;
    }
    if (min > *c) {
        min = *c;
    }
    double half = *a;
    if (half < max && half > min) {
        half = *a;
    }
    else {
        half = *b;
        if (half < max && half > min) {
            half = *b;    
        }
        else {
            half = *c;
        }
    }
    *a = min;
    *b = half;
    *c = max;
}
