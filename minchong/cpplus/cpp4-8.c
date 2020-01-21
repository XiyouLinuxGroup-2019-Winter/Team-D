#include<stdio.h>
int main()
{
    float m,n,h,s;
    printf("请输入行驶里程和消耗汽油：");
    scanf("%f %f",&m,&n);
    h=m/n;
    printf("%.1f",h);
    m=m*1.609;
    n=n*3.785;
    s=n/(m*100);
    printf("     %f",s);
}
