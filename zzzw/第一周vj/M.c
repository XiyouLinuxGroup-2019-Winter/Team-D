#include <stdio.h>

int main(int argc, char *argv[]) {
	unsigned long long n;
	scanf("%lld", &n);
	
	if(n == 0) printf("0\n");
	else if((n + 1) % 2 == 0)
		printf("%lld\n", (n + 1) / 2);
	else printf("%lld\n", n + 1);
}