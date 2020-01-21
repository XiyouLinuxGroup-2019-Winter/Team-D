#include<stdio.h>
#define si 60
int main()
{
    int h,m,s;
    while(1)
    {
        scanf("%d",&m);
        if(m<=0)
        break;
        h=m/60;
        m=m%60;
        printf("%dhour%dmin\n",h,m);
    }
}
