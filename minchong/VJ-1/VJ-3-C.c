#include<stdio.h>
int bio[100];
void dfs(char map[9][9],int n,int k,int q);
int ans=0;
int main()
{
    int n,k,p,i;
    char map[9][9];
    while(1)
    {
        scanf("%d%d",&n,&k);
        if(n==-1&&k==-1)
        break;
        for(i=0;i<n;i++)
        scanf("%s",map[i]);
        dfs(map,n,k,0);
        printf("%d\n",ans);
        ans=0;
        for(p=0;p<9;p++)
        for(i=0;i<9;i++)
        map[p][i]='\0';
      for(i=0;i<100;i++)
      bio[i]=0;
    }
}
void dfs(char map[9][9],int n,int k,int q)
{
    int i,l;
    if(k==0)
    {
        ans++;
        return;
    }
    for(q;q<n;q++)
    for(i=0;i<n;i++)
    {
        if(map[q][i]=='.'||bio[i]==1)
        continue;
        bio[i]=1;
        dfs(map,n,k-1,q+1);
        bio[i]=0;
    }
}
