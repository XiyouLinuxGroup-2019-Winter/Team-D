#include<stdio.h>
int main()
{
    int n,num[10000],i,j,k,s=0,max=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&j,&k);
        num[i]=k-j;
    }
    for(i=0;i<n;i++)
    {
        s+=num[i];
        if(max<s)
        max=s;
    }
    printf("%d",max);
}
