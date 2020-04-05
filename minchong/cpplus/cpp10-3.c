#include<stdio.h>
int f(int *,int );
int main()
{
    int num[5]={1,3,2,5,4};
    printf("%d\n",f(num,5));
}
int f(int *m,int n)
{
    int l=*m;
    while(n--)
    if(l<*m++)
    l=*(m+1);
    return l;
}
