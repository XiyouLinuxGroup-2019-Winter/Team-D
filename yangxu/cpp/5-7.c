#include<stdio.h>
int fun(int n){
    int i,sum=1;
    for(i=0;i<3;i++){
        sum=sum*n;
    }
    return sum;
}
int main ()
{
    int a;
    scanf("%d",&a);
    printf("%d",fun(a));
}

