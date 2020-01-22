#include<stdio.h>
int main ()
{
    const double n=3.785/1.609;
    double a,b;
    printf("请您输入里程和汽油消耗量\n");
    scanf("%lf %lf",&a,&b);
    printf("%lf\n",a/b);
    printf("%lf\n",a*n/b);
}

