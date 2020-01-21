#include<stdio.h>
int main()
{
    int m,n,i;
    scanf("%d %d",&m,&n);
    for(i=m;i<=n;i++)
    printf("%4d %4d %4d\n",i,i*i,i*i*i);
}
