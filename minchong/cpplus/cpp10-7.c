#include<stdio.h>
void copy2(double *ta2,double *sou,int n)
{
    int i;
    for(i=0;i<n;i++)
    *(ta2+i)=*(sou+i);
}
int main()
{
    double st[4][5]={1,2,3,4,5,6,7,8,9,0,1,1,1,1,1,2,3,4,2,5};
    double sy[4][5];
    int i,l;
    for(i=0;i<4;i++)
    copy2(sy[i],st[i],5);
    for(i=0;i<4;i++)
    for(l=0;l<5;l++)
    printf("%lf   ",sy[i][l]);
}
