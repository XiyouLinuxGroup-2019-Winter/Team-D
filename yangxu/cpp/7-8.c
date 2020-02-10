#include<stdio.h>
int main ()
{
    int a,n;;
    double b,sum,m;
    scanf("%d",&n);
    while(1)
    {
        printf("*******************************************************************\n\nEnter the number corresponding to the desired pay rate or action\n\n1. $8.75/hr                                           2. $9.33/hr\n\n3. $10.00/hr                                          4. $11.20/hr\n\n5. quit\n\n*******************************************************************\n");
        scanf("%d",&a);
        switch(a){
            case 1:
                b=8.75;
                break;
            case 2:
                b=9.33;
                break;
            case 3:
                b=10;
                break;
            case 4:
                b=11.2;
                break;
            case 5:
                b=1;
                break;
            default:
                printf("请输入正确数字\n");
        }
        if(b==1) break;
        else {
                if(n<=40) sum=n*b;
                else sum=((n-40)*1.5+40)*b;
                if(sum<=300) m=sum*0.15;
                else if(sum<=450) m=300*0.15+(sum-300)*0.2;
                else m=300*0.15+150*0.2+(sum-450)*0.25;
                printf("%f %f %f\n",sum,m,sum-m);
        }
    }
}

