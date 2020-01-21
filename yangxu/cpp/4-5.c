#include<stdio.h>
int main ()
{
    double m,n,a;
    printf("请您输入下载速度和文件大小\n");
    scanf("%lf %lf",&m,&n);
    a=n*8/m;
    printf("At %.2lf megabits per second, a file of %.2lf megabtyes downloads in %.2lf seconds.",m,n,a);
}

