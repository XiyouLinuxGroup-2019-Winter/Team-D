#include <math.h>
#include <stdio.h>
 
using namespace std;
int min(int x, int y) {
    return x > y ? y : x;
} 
 
const int MAXN = 1e4 + 10;
const int INF = 1e9;
 
int dp[MAXN];
int p[MAXN];
int w[MAXN];
 
int main()
{
    int t;
    int e, f;
    int n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &e, &f);
        for (int i = 1;i <= f - e;i++)
            dp[i] = INF;
        dp[0] = 0;
        scanf("%d", &n);
        for (int i = 1;i <= n;i++)
            scanf("%d%d", &p[i], &w[i]);
        for (int i = 1;i <= n;i++)
        {
            for (int j = w[i];j <= f - e;j++)
                dp[j] = min(dp[j], dp[j - w[i]] + p[i]);
        }
        if (dp[f - e] == INF)
            printf("This is impossible.\n");
        else
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[f - e]);
    }
 
 
    return 0;
}
