#include<stdio.h>
int main ()
{
    int n;
    double a,b;
    scanf("%d",&n);
    if(n<=40) a=n*10;
    else a=((n-40)*1.5+40)*10;
    if(a<=300) b=a*0.15;
    else if(a<=450) b=300*0.15+(a-300)*0.2;
    else b=300*0.15+150*0.2+(a-450)*0.25;
    printf("%f %f %f",a,b,a-b);
}

