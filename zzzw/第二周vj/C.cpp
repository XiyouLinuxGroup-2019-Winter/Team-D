#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	int n;
	scanf("%d", &n);
	
	for (int i = 0 ; i < n; i++) {
		int a, b;
		int n1;
		int dp[10050];
		int v[10050];
		int w[10050];
		
		memset(dp, 0x3f, sizeof(dp));
		dp[0] = 0;
		
		scanf("%d%d", &a, &b);
		int tle = b - a;
		scanf("%d", &n1);
		
		for (int i = 1; i <= n1; i++) {
			scanf("%d%d", &v[i], &w[i]);
		}
		
		for (int i = 1; i <= n1; i++) {
			for (int j = w[i]; j <= tle; j++) {
				if(dp[j] > dp[j - w[i]] + v[i])
					dp[j] = dp[j - w[i]] + v[i]; 
			}
		}
		if(dp[tle] != 0x3f3f3f3f)	printf("The minimum amount of money in the piggy-bank is %d.\n", dp[tle]);
		else printf("This is impossible.\n");
	}

}