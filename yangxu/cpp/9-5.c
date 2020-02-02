#include<stdio.h>
void fun(double *a,double *b)
{
    if(*a>*b){
        *b=*a;
    }else *a=*b;
}
int main ()
{
    double a,b;
    scanf("%lf %lf",&a,&b);
    fun(&a,&b);
    printf("%lf %lf",a,b);
}

