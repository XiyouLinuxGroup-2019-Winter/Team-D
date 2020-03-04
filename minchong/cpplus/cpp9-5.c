#include<stdio.h>
double larger_of(double x,double y)
{
    return x>y?x:y;
}
int main()
{
    double x,y;
    scanf("%lf %lf",&x,&y);
    printf("%lf\n",larger_of(x,y));
}
