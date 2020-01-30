#include<stdio.h>
int main ()
{
    int a,b,sum,i;
    while(scanf("%d %d",&a,&b)&&b>a){
        sum=0;
        for(i=a;i<=b;i++){
            sum=sum+i*i;
        }
        printf("%d\n",sum);
    }
}

