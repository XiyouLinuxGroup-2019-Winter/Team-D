#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;
	int cnt = 0;
	
	scanf("%d", &n);
	
	for (int i = 0 ; i < n; i++) {
		int a[3];
		
		scanf("%d%d%d", &a[0], &a[1], &a[2]);
		
		if(a[0] + a[1] + a[2] >= 2) cnt++;
	}
	
	printf("%d", cnt);
}