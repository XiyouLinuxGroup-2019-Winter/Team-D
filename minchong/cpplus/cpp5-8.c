#include<stdio.h>
int main()
{
    int m,n;
    printf("请输入整数：");
    scanf("%d",&m);
    while(1)
    {
        printf("请输入整数：");
        scanf("%d",&n);
        if(n<=0)
        break;
        printf("%d\n",n%m);
    }
}
