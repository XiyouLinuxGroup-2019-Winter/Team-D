#include<stdio.h>
#include<tgmath.h>
int main()
{
    int m,n=0,num[8];
    for(m=1;m<=8;m++)
    num[m-1]=pow(2,m);
    do
    {
        printf("%d  ",num[n]);
        n++;
    }
    while(n<8);
}
