#include<stdio.h>
#include<algorithm>
int jud(int n,int c,long int num[],long int w);
int main()
{
    int n,c;
    long int num[1000000];
    long int i,q,w,mod,ctr;
    scanf("%d%d",&n,&c);
    for(i=0;i<n;i++)
    scanf("%ld",&num[i]);
    std::sort(num,num+n);
    long int max=num[n-1],min=num[0];
    while(max-min>1)
    {
        w=(max+min)/2;
        ctr=jud(n,c,num,w);
        if(ctr)
        min=w;
        else
        max=w;
    }
    printf("%ld\n",min);
}
int jud(int n,int c,long int num[],long int w)
{
   long  int i,q,p=0;
    q=1;
    for(i=1;i<n;i++)
    {
        if(num[i]-num[p]>=w)
        {
        q++;
        p=i;
        }
        if(q>=c)
        return 1;
    }
    return 0;
    
}

