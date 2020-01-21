#include<stdio.h>
int main ()
{
    double a;
    while(scanf("%lf",&a)&&a>0){
        int b=a/2.54/12;
        printf("%lf cm = %d feet, %lf inches\n",a,b,a/2.54-b*12);
    }
    printf("bye\n");
}

