#include<stdio.h>
int main()
{
    int num[100],i=0,p,k=0,nun[100],l;
    int s=0;
    while(1)
    {
        scanf("%d",&p);
        if(p==0)
        break;
        else
        {
        if(p%2==0)
        {
            num[i]=p;
            i++;
        }
        else
        {
            nun[k]=p;
            k++;
        }
        }
    }
    for(l=0;l<i;l++)
    s+=num[l];
    s=s/i;
    printf("%d  %d  ",i,s);
    s=0;
    for(l=0;l<k;l++)
    s+=nun[l];
    s=s/k;
    printf("%d %d",k,s);
}
