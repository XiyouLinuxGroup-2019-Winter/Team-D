#include<stdio.h>
double fun(double n){
    const double a=5.0/9.0;
    return a*(n-32);
}
double fun1(double n){
    const double a=273.16;
    return fun(n)+a;
}
int main ()
{
    double a;
    scanf("%lf",&a);
    printf("华氏度：%lf 摄氏度：%lf 开氏度：%lf\n",a,fun(a),fun1(a));
}

