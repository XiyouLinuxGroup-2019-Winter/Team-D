#include<stdio.h>
int main()
{
    int m,n,q,w,e,num1[1111],num2[1111],i;
    scanf("%d",&m);
    for(q=0;q<m;q++)
    {
        int dp[1111][1111]={{0}};
        scanf("%d %d",&n,&w);
        for(i=1;i<=n;i++)
        scanf("%d",&num1[i]);
        for(i=1;i<=n;i++)
        scanf("%d",&num2[i]);
        for(i=1;i<=n;i++)
        for(e=0;e<=w;e++)
        {
            if(e<num2[i])
            dp[i][e]=dp[i-1][e];
            else
            dp[i][e]=(dp[i-1][e]>(dp[i-1][e-num2[i]]+num1[i])?dp[i-1][e]:dp[i-1][e-num2[i]]+num1[i]);
        }
        printf("%d\n",dp[n][w]);
    }
    return 0;
}
