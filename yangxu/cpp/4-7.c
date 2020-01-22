#include<stdio.h>
#include<float.h>
int main ()
{
    double a=1.0/3.0;
    float b=1.0/3.0;
    int n=FLT_DIG,m=DBL_DIG;
    printf("%.6lf %.6f\n",a,b);
    printf("%.12lf %.12f\n",a,b);
    printf("%.16lf %.16f\n",a,b);
    printf("%d %d",n,m);
}

