#include<stdio.h>
int main ()
{
    int n,a=0,b=0,sum=0,sum1=0;
    while(scanf("%d",&n)&&n!=0){
        if(n%2==0){
            a++;
            sum=sum+n;
        }else{
            b++;
            sum1=sum+n;
        }
    }
    printf("%d %f %d %f",a,sum*1.0/a,b,sum1*1.0/b);
}

