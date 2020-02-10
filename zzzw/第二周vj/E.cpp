#include <iostream>
#include <cstdio>
#include "algorithm"
using namespace std;

int dp[100050], v[100050], num[100050], vnew[100050], wnew[100050];
int W, n;
int cnt = 0;

int main(int argc, char *argv[]) {
	
	while (1) {
		scanf("%d%d", &n, &W);
		
		if(n == 0 && W == 0) break;
		
		for(int i = 1; i <= n; i++)	scanf("%d", &v[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
		
		for (int i = 1 ; i <= n ; i++) {
			for (int j = 1; j <= num[i]; j <<= 1) {
				num[i] -= j;
				vnew[++cnt] = j * v[i];
				wnew[cnt] = j * v[i];
			}
			if(num[i])	vnew[++cnt] = num[i] * v[i], wnew[cnt] = num[i] * v[i];	
		}
		
		for (int i = 1; i <= cnt; i++){
			for (int j = W; j >= wnew[i]; j--){
				dp[j] = max(dp[j], dp[j - wnew[i]] + vnew[i]);
			}
		}
		
		int ans = 0;
		for (int i = 1 ; i <= W ; i++) {
			if(dp[i] == i) ans++;
		}
		
		printf("%d\n", ans);
		cnt  = 0;
		memset(dp, 0, sizeof(dp));
	}
}