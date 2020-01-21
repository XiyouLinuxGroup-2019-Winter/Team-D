#include<stdio.h>
int main()
{
    float m,n,h;
    while(1)
    {
        printf("请输入身高：");
        scanf("%f",&m);
        if(m<=0)
        break;
        n=m/2.54;
        h=m-(int)n*2.54;
        printf("%f cm = %.0f feet,%.1f inches",m,n,h);
    }
}
