#include<stdio.h>
double fun(double a,double b){
    return (a-b)/a*b;
}
int main ()
{
    double a,b;
    while(scanf("%lf %lf",&a,&b)){
        printf("%lf\n",fun(a,b));
    }
}

