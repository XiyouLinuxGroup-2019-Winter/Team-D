#include<stdio.h>
int main ()
{
    int a,b,c,n;
    scanf("%d %d %d",&a,&b,&c);
    if(a>(b+c)) n=b+c;
    else n=a;
    if(c>(a+b)) n=n+a+b;
    else n=n+c;
    if(b>(a+c)) n=n+a+c;
    else n=n+b;
    printf("%d",n);
}

