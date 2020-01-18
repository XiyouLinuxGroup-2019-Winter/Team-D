#include <stdio.h>
#include "ctype.h"
#include "string.h"

int main(int argc, char *argv[]) {
	int n;
	scanf("%d", &n);
	
	char str[1000];
	
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		
		int cnt = 0;
		
		for (int j = 0; j < strlen(str); j++) 
			if(str[j] >= '0' && str[j] <= '9') cnt++;
		
		printf("%d\n", cnt);
	}
}