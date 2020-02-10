#include<stdio.h>
int fun(int n)
{
    int a=1,b=1,i,sum;
    if(n==1||n==2) return 1;
    else {
        for(i=2;i<n;i++){
            sum=a+b;
            a=b;
            b=sum;
        }
    }
    return sum;
}
int main ()
{
    int n;
    scanf("%d",&n);
    printf("%d",fun(n));
}

