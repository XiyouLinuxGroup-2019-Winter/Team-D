#include<stdio.h>
#include<stdlib.h>
int ks(int num[],int key,int ctr,int n)
{
    int i,q=1,w,e,j,h,m;
    int mod[101];
    mod[0]=0;
    for(i=1;i<=n;i++)
        if(num[i]!=-1)
        {
            mod[q]=num[i];
            if(mod[q]==ctr)
            e=q;
            q++;
        }
    for(m=q;m<101;m++)
    mod[m]=0;
    q--;
    w=key%q;
    if(e==q)
    {
        printf("%d ",mod[w]);
        num[mod[w]]=-1;
        h=mod[w]+1;
        if(w=q)
        h=mod[1];
        return h;
    }
    for(i=1;i<=w;i++)
    {
        e++;
        if(e==q&&i!=w)
        e=0;
    }
    printf("%d ",mod[e]);
    num[mod[e]]=-1;
    h=mod[e]+1;
    if(e=q)
    h=mod[1];
    return h;
}
int main()
{
    int n,k,num[101],ai[101],i,q,j,ctr;
    scanf("%d %d",&n,&k);
    for(i=0;i<k;i++)
    scanf("%d",&ai[i]);
    for(i=1;i<=n;i++)
    num[i]=i;
    num[0]=-1;
    for(i=n+1;i<101;i++)
    num[i]=-1;
    ctr=1;
    for(i=0;i<k;i++)
    {
    j=ai[i];
    ctr=ks(num,j,ctr,n);
    }
}
