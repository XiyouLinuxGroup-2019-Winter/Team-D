#include "stdio.h"

long long  a[1000][1000];

int main(int argc, char *argv[]) {
	
	int n;
		
	while(scanf("%d", &n) != EOF){
		for(int i = 1; i <= n; i++)
		{
			for(int m = 1; m <= i; m++)
				{
					if(m == i) a[i][m] = 1, printf("%lld\n", a[i][m]);
 					else a[i][m] = a[i - 1][m - 1] + a[i - 1][m],printf("%lld ", a[i][m]);
				}
		}
		printf("\n");
	}

}