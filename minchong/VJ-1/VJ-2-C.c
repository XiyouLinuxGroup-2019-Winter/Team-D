#include<stdio.h>
#define INF 999999
int main()
{
    int T,e,f,n,num1[1000],num2[1000],i,q,m,h,w,k;
    scanf("%d",&T);
    for(q=0;q<T;q++)
    {
        int dp[100001];
        scanf("%d %d",&e,&f);
        h=f-e;
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        scanf("%d %d",&num1[i],&num2[i]);
        for(k=0;k<=h;k++)
        dp[k]=INF;
        dp[0]=0;
        for(i=1;i<=n;i++)
        for(m=num2[i];m<=h;m++)
        {
            if(m<num2[i])
            dp[m]=dp[m-1];
            else
            dp[m]=(dp[m]>(dp[m-num2[i]]+num1[i])?(dp[m-num2[i]]+num1[i]):dp[m]);
        }
        if(dp[h]>=INF)
        printf("This is impossible.\n");
        else
        printf("The minimum amount of money in the piggy-bank is %d.\n",dp[h]);
    }
}
