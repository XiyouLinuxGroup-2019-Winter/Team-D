#include<stdio.h>
void fun(double *a,double *b,double *c)
{
    double y;
    if(*b<*a){
        y=*b;
        *b=*a;
        *a=y;
    }
    if(*b>*c){
        y=*b;
        *b=*c;
        *c=y;
    }
    if(*b<*a){
        y=*b;
        *b=*a;
        *a=y;
    }
}
int main ()
{
    double a,b,c;
    scanf("%lf %lf %lf",&a,&b,&c);
    fun(&a,&b,&c);
    printf("%lf %lf %lf",a,b,c);
}

