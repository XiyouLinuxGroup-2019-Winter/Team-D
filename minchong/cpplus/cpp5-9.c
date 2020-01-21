#include<stdio.h>
void tem(double);
int main()
{
    double m;
    while((scanf("%lf",&m))==1)
    {
        tem(m);
    }
}
void tem(double m)
{
    float q,w;
    const float a=5.0*9.0,s=273.16;
    q=a*(m-32.0);
    w=m+s;
    printf("%.2f  %.2f\n",q,w);
}
