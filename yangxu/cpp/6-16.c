#include<stdio.h>
int main ()
{
    int i,j;
    double a,b;
    for(i=1;;i++){
        a=b=100;
        a=a+10*i;
        for(j=1;j<=i;j++){
            b=b+b*0.05;
        }
        if(b>a) break;
    }
    printf("%d %lf %lf",i,a,b);
}

