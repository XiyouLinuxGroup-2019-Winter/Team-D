#include<stdio.h>
int main ()
{
    double a=100;
    int i;
    for(i=1;;i++){
        a=a+a*0.08-10;
        if(a<=0) break;
    }
    printf("%d\n",i);
}

