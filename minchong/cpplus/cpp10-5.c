#include<stdio.h>
double f(double *p,int n)
{
    int i;
    double m=p[0],k=p[0];
    for(i=1;i<n;i++)
    {
        if(m<p[i])
        m=p[i];
        if(k>p[i])
        k=p[i];
    }
    return m-k;
}
int main()
{
    double k[5]={1.1,2.2,3.3,4.4,5.5};
    printf("%lf\n",f(k,5));
}
