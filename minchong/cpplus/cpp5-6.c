#include<stdio.h>
int main()
{
    int m,i,s;
    scanf("%d",&m);
    for(i=1,s=0;i<=m;i++)
    s+=i*i;
    printf("%d",s);
}
