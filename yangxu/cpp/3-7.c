#include<stdio.h>
int main ()
{
    double n,m;
    printf("请您输入身高（/英寸）\n");
    scanf("%lf",&n);
    m=n*2.54;
    printf("%lf\n",m);
}

