#include<stdio.h>
int main ()
{
    double a;
    char n[82];
    printf("请您输入身高（英寸）\n");
    scanf("%lf",&a);
    printf("请您输入姓名\n");
    scanf("%s",n);
    printf("%s, you are %lf feet tall",n,a);
}

