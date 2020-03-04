#include<stdio.h>
int min(int n,int m)
{
    int a,k;
    k=m*n;
    if(n<m)
    {
        a=n;
        n=m;
        m=a;
    }
    while(n%m)
    {
        a=n%m;
        n=m;
        m=a;
    }
    return k/m;
}
int main()
{
    int n,m,z,k;
    scanf("%d %d %d",&n,&m,&z);
    k=min(n,m);
    printf("%d\n",z/k);
}
