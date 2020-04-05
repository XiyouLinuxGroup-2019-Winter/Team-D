#include<stdio.h>
int f(double *,int n);
int main()
{
    double h[6]={1.2,2.1,3.3,2.2,6.5,3.4};
    printf("%d\n",f(h,6));
}
int f(double *h,int n)
{
    int i=0,l;
    double k=*h;
    for(l=1;l<n;l++)
    {
        if(k<h[l])
        {
            k=h[l];
            i=l;
        }
    }
    return i;
}
