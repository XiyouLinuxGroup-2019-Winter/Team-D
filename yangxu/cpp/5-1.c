#include<stdio.h>
int main ()
{
    const int a=60;
    int b;
    while(scanf("%d",&b)&&b>0){
        printf("%d %d\n",b/a,b%a);
    }
}

