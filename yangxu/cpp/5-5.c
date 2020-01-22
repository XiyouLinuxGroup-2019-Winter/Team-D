#include<stdio.h>
int main ()
{
    int a;
    scanf("%d",&a);
    int i,sum=0;
    for(i=1;i<=a;i++){
        sum=sum+i;
    }
    printf("%d",sum);
}

