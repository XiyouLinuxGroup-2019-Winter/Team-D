#include<stdio.h>
unsigned int f(unsigned int,unsigned int);
int main()
{
    unsigned int m,n;
    scanf("%du %du",&m,&n);
    printf("%du\n",f(m,n));
}
unsigned int f(unsigned int m,unsigned int n)
{
    int i,h=m>>(32-n);
    m<<=n;
    return m+h;
}
