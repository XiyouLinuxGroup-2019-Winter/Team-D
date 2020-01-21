#include<stdio.h>
int main ()
{
    int a,b;
    scanf("%d",&a);
    while(scanf("%d",&b)&&b>0){
        printf("%d %% %d is %d\n",b,a,b%a);
    }
    printf("Done\n");
}

