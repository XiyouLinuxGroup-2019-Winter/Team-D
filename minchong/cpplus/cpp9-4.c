#include<stdio.h>
double h(double x,double y)
{
    return 1/((1/x+1/y)/2);
}
int main()
{
    double x,y;
    scanf("%lf %lf",&x,&y);
    printf("%lf\n",h(x,y));
}
