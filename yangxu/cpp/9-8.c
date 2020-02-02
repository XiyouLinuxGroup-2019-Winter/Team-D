#include<stdio.h>
double fun(int a,int b)
{
    int i,sum=1;
    if(a==0) return 0;
    if(b==0){
        printf("幂数为0无定义\n");
        return 1;
    }else if(b>0){
        for(i=0;i<b;i++){
            sum=sum*a;
        }
        return sum;
    }else if(b<0){
        for(i=0;i<-b;i++){
            sum=sum*a;
        }
        return 1.0/sum;
    }
}
int main ()
{;
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%lf",fun(a,b));
}

