#include<stdio.h>
int main ()
{
    int a;
    while(scanf("%d",&a)&&a>0){
        printf("%d days are %d weeks, %d days.\n",a,a/7,a%7);
    }
}

