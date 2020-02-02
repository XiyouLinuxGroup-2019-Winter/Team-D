#include<stdio.h>
double min(double a,double b)
{
    if(a<b) return a;
    else return b;
}
int main ()
{
    double a,b;
    scanf("%lf %lf",&a,&b);
    printf("%f\n",min(a,b));
}

