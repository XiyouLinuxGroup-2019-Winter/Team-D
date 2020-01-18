#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;
	int k;
	
	scanf("%d%d", &n, &k);
	int a[n];
	
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
		
	int i  = 0;
	int cnt = 0;
	
	while(i < n && a[i] <= k)
		i++, cnt++;
	
	while(n - 1 >= i && a[n - 1] <= k)
		n--, cnt++;
	
	printf("%d", cnt);
}