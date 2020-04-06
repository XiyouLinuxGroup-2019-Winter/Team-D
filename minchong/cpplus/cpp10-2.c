#include<stdio.h>
void copy1(double [],double [],int);
void copy2(double *,double *,int);
void copy3(double *,double *,double *);
int main()
{
    int i;
    double sou[5]={1.1,2.2,3.3,4.4,5.5},ta1[5],ta2[5],ta3[5];
    copy1(ta1,sou,5);
    copy2(ta2,sou,5);
    copy3(ta3,sou,sou+5);
    for(i=0;i<5;i++)
    printf("%lf  %lf  %lf  %lf\n",sou[i],ta1[i],ta2[i],ta3[i]);
}
void copy1(double ta1[],double sou[],int n)
{
    int i;
    for(i=0;i<n;i++)
    ta1[i]=sou[i];
}
void copy2(double *ta2,double *sou,int n)
{
    int i;
    for(i=0;i<n;i++)
    *(ta2+i)=*(sou+i);
}
void copy3(double *ta3,double *sou,double *l)
{
    for(sou;sou<l;sou++,ta3++)
    *ta3=*sou;
}
