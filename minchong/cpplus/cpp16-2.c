#include<stdio.h>
#define TDE(x,y)  (1/(((1/(x))+(1/(y)))/2))
int main()
{
    float a,b;
    scanf("%f %f",&a,&b);
    printf("%.2f\n",TDE(a,b));
}
