#include<stdio.h>
int f(int,int );
int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    printf("%d\n",f(m,n));
}
int f(int m,int n)
{
    m>>=n-1;
    if((m|0)==0)
    return 0;
    return 1;
}
