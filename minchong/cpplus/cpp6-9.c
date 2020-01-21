#include<stdio.h>
void sum(float,float);
int main()
{
    float m,n;
    while(scanf("%f %f",&m,&n)==2)
    {
        sum(m,n);
    }
}
void sum(float m,float n)
{
    printf("%f\n",(m-n)/(m*n));
}
