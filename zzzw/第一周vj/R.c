#include <stdio.h>
#include "ctype.h"
#include "string.h"

int main(int argc, char *argv[]) {
	int n;
	char str[10050];
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int a[26] = { 0 };
		
		scanf("%s", str);
		
		for (int j = 0; j < strlen(str); j++) {
			if(isalpha(str[j]))
				{
					a[tolower(str[j]) - 'a']++;
				}
		}
		printf("a:%d\n", a['a' - 'a']);
		printf("e:%d\n", a['e' - 'a']);
		printf("i:%d\n", a['i' - 'a']);
		printf("o:%d\n", a['o' - 'a']);
		printf("u:%d\n", a['u' - 'a']);
		
		if(i != n - 1)
			printf("\n");
	}	
}