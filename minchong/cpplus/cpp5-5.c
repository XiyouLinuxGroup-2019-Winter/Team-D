#include<stdio.h>
int main()
{
    int m,i,s;
    scanf("%d",&m);
    for(i=0,s=0;i<=m;i++)
    s+=i;
    printf("sum = %d\n",s);
}
