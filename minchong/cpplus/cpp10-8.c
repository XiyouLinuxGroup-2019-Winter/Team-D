#include<stdio.h>
void copy2(double *ta2,double *sou,int n)
{
    int i;
    for(i=0;i<n;i++)
    *(ta2+i)=*(sou+i);
}
int main()
{
    double k[7]={1,2,3,4,5,6,7},l[3];
    copy2(l,&k[3],3);
    int i;
    for(i=0;i<3;i++)
    printf("%lf  ",l[i]);
}
