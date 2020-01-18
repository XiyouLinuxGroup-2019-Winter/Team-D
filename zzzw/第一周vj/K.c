#include <stdio.h>

int main(int argc, char *argv[]) {
	int m, k;
	scanf("%d%d", &m, &k);
	char a[k + 1], j = 'a';
	
	for(int i = 0; i < k; i++)
		a[i] = j++;
	
	for(int i = m / k; i > 0; i--)
		for(int j = 0; j < k; j++) printf("%c", a[j]);
	for (int i = 0; i < m - m / k  * k ;i++) {
		printf("%c", a[i]);
	}
}