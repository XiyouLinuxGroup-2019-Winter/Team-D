#include<stdio.h>
int main()
{
    int num[8],q;
    for(q=0;q<8;q++)
    scanf("%d",&num[q]);
    for(q=7;q>=0;q--)
    printf("%d  ",num[q]);
}
