#include<stdio.h>
int main ()
{
    int a=0,b=0,c=0,m;
    double sum,d,e,sum1;
    char n;
    while(scanf("%c",&n)){
        if(n=='a'){
            scanf("%d",&m);
            a=a+m;
        }else if(n=='b'){
            scanf("%d",&m);
            b=b+m;
        }else if(n=='c'){
            scanf("%d",&m);
            c=c+m;
        }else if(n=='q') break;
    }
    sum=a*2.05+b*1.15+c*1.09;
    if(sum<=100){
        d=0;
        sum1=sum;
    }
    else{
        d=0.95;
        sum1=sum*0.95;
    }
    if((a+b+c)<=5) e=6.5;
    else if((a+b+c)<=20) e=14;
    else e=14+(a+b+c-20)*0.5;
    printf("%.2f %.2f %.2f %d %.2f %.2f %.2f %.2f\n",2.05,1.15,1.09,a+b+c,sum,sum1+e,d,e);
}

