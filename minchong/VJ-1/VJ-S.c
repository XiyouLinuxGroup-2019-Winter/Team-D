#include<stdio.h>
int main()
{
    int m,n,i,k,num[100000],h;
    scanf("%d",&m);
    for(i=0;i<m;i++)
    scanf("%d",&num[i]);
    for(i=0;i<m;i++)
    for(k=i+1;k<m;k++)
    if(num[i]>num[k])
    {
        n=num[i];
        num[i]=num[k];
        num[k]=n;
    }
    n=m%2;
    h=m/2;
    if(n==0)
    printf("%d",num[h-1]);
    else
    printf("%d",num[h]);
}
