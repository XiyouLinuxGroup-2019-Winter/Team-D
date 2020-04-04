#include<stdio.h>
int f(int );
int main()
{
    int m;
    scanf("%d",&m);
    printf("%d\n",f(m));
}
int f(int m)
{
    int s=0;
    for(int k=32;k>0;k--)
    {
        if(m&1==1)
        s++;
        m>>=1;
    }
    return s;
}
