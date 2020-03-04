#include <stdio.h>

int main(int argc, char *argv[]) {
	
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		double dp[10050] = { 0 };
		double t[10050];
		int v[10050];
		
		int n1;
		double tle;
		scanf("%lf%d", &tle, &n1);
		int max = 0;
		double tmax = 0;
	
		for (int i = 1; i <= n1; i++) {
			double b;
			scanf("%d%lf", &v[i], &b);
			t[i] = 1 - b;
			max += v[i];
		}
		
		dp[0] = 1;

		for (int i = 1; i <= n1 ; i++) {
			for (int j = max ; j >= v[i]; j--) {
				if(dp[j] < dp[j - v[i]] * t[i])
					dp[j] = dp[j - v[i]] * t[i]; 
			}
		}	
		for (int i = max; i >= 0; i--) {
			if(dp[i] >= 1 - tle)
				{
					printf("%d\n", i);
					break;
				}
		}

	}
}