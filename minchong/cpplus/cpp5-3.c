#include<stdio.h>
int main()
{
    int m,n,h;
    while(1)
    {
    printf("请输入天数：");
    scanf("%d",&m);
    if(m<=0)
    break;
    n=m/7;
    h=m%7;
    printf("%d days are %d weeks,%d days.",m,n,h);
    }
}
