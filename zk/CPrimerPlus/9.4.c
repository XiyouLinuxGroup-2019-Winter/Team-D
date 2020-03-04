#include <stdio.h>

double ave(double x, double y);

int main()
{
    double x = 3, y = 5;
    printf("%lf\n", ave(x, y));
    return 0;
}

double ave(double x, double y) {
    double a, b, c;
    a = 1 / x;
    b = 1 / y;
    double ave = (a + b) / 2;
    c = 1 / ave;
    return c;
}
