#include<stdio.h>
int main()
{
    float q,w;
    printf("请输入下载速度与文件大小：");
    scanf("%f %f",&q,&w);
    printf("At %.2f megabits per second, a file of %.2f megabytes downloads in %.2f seconds",q,w,w/q);
}
