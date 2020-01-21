#include<stdio.h>
int main()
{
    float  m,n,q,w,e;
    while((scanf("%f%f",&m,&n))==2)
    {
        q=m-n;
        w=m*n;
        e=q/w;
        printf("%f\n",e);
    }
}
