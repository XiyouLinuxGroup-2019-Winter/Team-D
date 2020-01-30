#include <stdio.h>

double min(double x, double y);
int main()
{
    double x = 1, y = 2;
    double a = min(x, y);
    printf("%lf\n", a);
    return 0;
}
double min(double x, double y) {
    return x < y ? x : y;
}


