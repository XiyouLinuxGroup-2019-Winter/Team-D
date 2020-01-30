#include<stdio.h>
#include<string.h>
int main()
{
    int i,num[10000],h,n,k,m=0;
    char str[10000];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
    scanf("%s",str);
    h=strlen(str);
    for(k=0;k<h;k++)
    if(str[k]>='0'&&str[k]<='9')
    m++;
    num[i]=m;
    m=0;
}
    for(i=0;i<n;i++)
    printf("%d\n",num[i]);
}
