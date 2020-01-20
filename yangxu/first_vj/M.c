#include<stdio.h>
int main ()
{
    unsigned long long n,i;
    scanf("%lld",&n);
    if(n==0) i=0;
    else if(n==1) i=1;
    else if((n+1)%2==0) i=(n+1)/2;
    else i=n+1;
    printf("%lld",i);
}

