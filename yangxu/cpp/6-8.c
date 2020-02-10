#include<stdio.h>
int main ()
{
    double n,m,a;
    while(scanf("%lf %lf",&n,&m)){
        a=(n-m)/n*m;
        printf("%lf\n",a);
    }
}

