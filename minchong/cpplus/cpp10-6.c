#include<stdio.h>
void f(double p[],int n)
{
    int i,l=n-1;
    double m;
    for(i=0;i<l/2;i++)
    {
        m=p[i];
        p[i]=p[n-1-i];
        p[n-1-i]=m;
    }
}
int main()
{
    double num[7]={1,2,3,4,5,6,7};
    int i;
    f(num,7);
    for(i=0;i<7;i++)
    printf("%lf  ",num[i]);
}
