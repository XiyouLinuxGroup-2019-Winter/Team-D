#include<stdio.h>
int main()
{
    int i;
    double m[8],n[8];
    for(i=0;i<8;i++)
    scanf("%lf",&m[i]);
    n[0]=m[0];
    for(i=1;i<8;i++)
    n[i]=n[i-1]+m[i];
    for(i=0;i<8;i++)
    printf("%f   ",n[i]);
}
