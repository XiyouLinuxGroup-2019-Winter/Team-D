#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;
	
	scanf("%d", &n);
		
	int max = 0;
	int now = 0;
	
	for (int i = 0; i < n; i++) {
		int minus;
		int add;
		
		scanf("%d%d", &minus, &add);
		
		now = now - minus + add;
		
		if(now > max) max = now;
	}	
	
	printf("%d", max);

}