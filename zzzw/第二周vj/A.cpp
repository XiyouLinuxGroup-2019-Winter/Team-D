#include <cstdio>
using namespace std;

int main(int argc, char *argv[]) {
	int n ;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int c[100050];
		int v[100050];
		int dp[100050] = { 0  };
		int n1;
		int s;
		scanf("%d%d", &n1, &s);
		
		for (int i = 0; i < n1 ; i++) {
			scanf("%d", &v[i]);
		}
		for (int i = 0; i < n1 ; i++) {
			scanf("%d", &c[i]);
		}
		
		for(int i = 0; i < n1; i++)
		{
			for (int t = s ; t >= c[i] ; t--) {
				if(dp[t] < dp[t - c[i]] + v[i])
				dp[t] = dp[t - c[i]] + v[i];
			}
		}
		
		printf("%d\n", dp[s]);
	}		
}