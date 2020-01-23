#include<stdio.h>
int main()
{
    int n,k,m=0,num[1000000],i,h;
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
    scanf("%d",&num[i]);
    for(i=0;num[i]<=k&&i<n;i++)
    m++;
    for(h=n-1;num[h]<=k&&h>i;h--)
    m++;
    printf("%d",m);
}
