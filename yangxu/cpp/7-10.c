#include<stdio.h>
int main ()
{
    int a,sum;
    double m;
    while(1){
        printf("1. 单身         2.户主\n\n3.已婚,共有       4.已婚，离异\n\n5.quit\n\n");
        scanf("%d",&a);
        if(a==5) break;
        scanf("%d",&sum);
        if(a==1){
            if(sum<=17850) m=sum*0.15;
            else m=17850*0.15+(sum-17850)*0.28;
        }else if(a==2){
            if(sum<=23900) m=sum*0.15;
            else m=23900*0.15+(sum-23900)*0.28;
        }else if(a==3){
            if(sum<=29750) m=sum*0.15;
            else m=29750*0.15+(sum-29750)*0.28;
        }else if(a==4){
            if(sum<=14875) m=sum*0.15;
            else m=14875*0.15+(sum-14875)*0.28;
        }
        printf("%lf\n",m);
    }
}

