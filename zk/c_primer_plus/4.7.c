#include <stdio.h>
#include <float.h>
int main()
{
    printf("%d\n", FLT_DIG);
    printf("%d\n", DBL_DIG);
    double num = 1.0 / 3.0;
    float num1 = 1.0 / 3.0;
    printf("%.6f %.6lf\n", num1, num);
    printf("%.12f %.12lf\n", num1, num);
    printf("%.16f %.20lf\n", num1, num);

    return 0;
}

