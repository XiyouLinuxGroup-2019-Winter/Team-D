#include<stdio.h>
int main()
{
    int m,num[100000],i,k=0,d1,d2,d3;
    scanf("%d",&m);
    for(i=0;i<m;i++)
    {
        scanf("%d %d %d",&d1,&d2,&d3);
        if((d1+d2+d3)>1)
        k++;
    }
    printf("%d",k);
}
