#include <stdio.h>

int main()
{
	int n;
	int k;
	int a[26] = { 0 };
	
	scanf("%d%d", &n, &k);
	
	char ch;
	
	for (int i = 0; i < n; i++) {
		scanf(" %c", &ch);
		a[ch - 'A']++;	
	}
	
	int min = a[0];
	
	for (int i = 0; i < k; i++) {
		if(a[i] < min)
			min = a[i];
	}
	
	printf("%d", min * k);
}