#include<stdio.h>
int main ()
{
    int i,a;
    a=5;
    for(i=1;;i++){
        a=(a-i)*2;
        if(a>150) break;
        printf("%d\n",a);
    }
}

