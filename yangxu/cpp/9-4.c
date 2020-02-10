#include<stdio.h>
double fun(double a,double b)
{
    return 1/((1/a+1/b)/2);
}
int main ()
{
    double a,b;
    scanf("%lf %lf",&a,&b);
    printf("%lf",fun(a,b));
}

