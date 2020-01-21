#include<stdio.h>
void three(float);
int main()
{
    float m;
    scanf("%f",&m);
    three(m);
}
void three(float m)
{
    printf("%f",m*m*m);
}
