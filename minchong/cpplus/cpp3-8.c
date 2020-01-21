#include"stdio.h"
int main()
{
    int m;
    float q,w,e,r;
    printf("请输入杯数：");
    scanf("%d",&m);
    q=m*0.5;
    w=m*8;
    e=w*2;
    r=e*3;
    printf("%.2f品脱%.2f盎司%.2f汤勺%.2f茶勺\n",q,w,e,r);
}
