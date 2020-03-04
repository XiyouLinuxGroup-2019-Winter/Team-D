#include<stdio.h>
void h(double *p1,double *p2,double *p3)
{
    double m,n,k;
    m=*p1>*p2?*p1:*p2;
    m=m>*p3?m:*p3;
    n=*p1<*p2?*p1:*p2;
    n=n<*p3?n:*p3;
    if(*p1!=m&&*p1!=n)
    k=*p1;
    else if(*p2!=m&&*p2!=n)
    k=*p2;
    else
    k=*p3;
    *p1=m;
    *p2=k;
    *p3=n;
}
int main()
{
    double a,s,d;
    scanf("%lf,%lf,%lf",&a,&s,&d);
    h(&a,&s,&d);
    printf("%lf,%lf,%lf",a,s,d);
}
