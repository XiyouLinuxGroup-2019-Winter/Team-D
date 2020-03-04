#include<stdio.h>
double min(double x,double y)
{
    return x<y?x:y;
}
int main()
{
    double x,y;
    scanf("%lf %lf",&x,&y);
    printf("%lf\n",min(x,y));
}
