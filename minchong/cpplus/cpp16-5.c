#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void f(int *p,int n,int m)
{
    int num[n],l=0;
    srand(time(NULL));
    int i;
    for(i=0;i<m;i++)
    {
        l=0;
        int h=rand()%n;
        for(int k=0;k<=i;k++)
        if(num[k]==h)
        {
            i--;
            l=1;
            break;
        }
        if(l==1)
        continue;
        num[i]=h;
    }
    for(i=0;i<m;i++)
    printf("%d  ",p[num[i]]);
}
int main()
{
    int p[10]={1,2,3,4,5,6,7,8,9,0};
    f(p,10,4);
}
