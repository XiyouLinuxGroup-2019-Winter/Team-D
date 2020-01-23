#include<stdio.h>
int main()
{
    int d1,d2,d3,i[4],min,h;
    scanf("%d %d %d",&d1,&d2,&d3);
    i[0]=2*(d1+d2);
    i[1]=d1+d2+d3;
    i[2]=2*(d1+d3);
    i[3]=2*(d2+d3);
    min=i[0];
    for(h=1;h<4;h++)
    if(min>i[h])
    min=i[h];
    printf("%d",min);
}
