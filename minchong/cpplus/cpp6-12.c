#include<stdio.h>
#include<math.h>
int main()
{
    int m,i;
    float n=0,n1=0;
    scanf("%d",&m);
    for(i=0;i<m;i++)
    {
    n+=1.0/(1.0+i+1);
    if(i%2==0)
    n1+=1.0/(1.0+i+1);
    else
    n1-=1.0/(1.0+i+1);
    }
    printf("%f    %f\n",n,n1);
}
