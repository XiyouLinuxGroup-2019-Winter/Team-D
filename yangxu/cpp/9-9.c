#include<stdio.h>
double fun(int a,int b)
{
    int i,sum=1;
    if(a==0) return 0;
    if(b==0){
        return 1;
    }else if(b>0){
        if(b!=1){
            return fun(a,--b)*a;
        }else return a;
    }else if(b<0){
        if(b!=0){
            return fun(a,++b)*(1.0/a);
        }else return 1/a;
    }
}
int main ()
{
    int a,b;
    scanf("%d %d",&a,&b);
    if(b==0) printf("幂数为0无定义\n");
    printf("%lf",fun(a,b));
}

