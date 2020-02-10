#include<stdio.h>
#include<math.h>
int main ()
{
    int n,i;
    double sum,sum1;
    while(scanf("%d",&n)&&n>0){
        sum=sum1=0;
        for(i=1;i<=n;i++){
            sum=sum+1.0/i;
            sum1=sum1+1.0/i*(pow(-1,i+1));
        }
        printf("%lf %lf\n",sum,sum1);
    }
}

