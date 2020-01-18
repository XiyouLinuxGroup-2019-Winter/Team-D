#include <stdio.h>

int main(int argc, char *argv[]) {
	int a[26] = { 0 };
	char ch;
	
	for (int i = 0; i < 2; i ++) {	
		while((ch = getchar(
		)) != '\n')
			a[ch - 'A']++;
	}
	
	while ((ch = getchar()) != '\n') {
		a[ch - 'A']--;
	}
	
	int f = 0;
	
	for (int i = 0; i < 26; i++) {
		if(a[i] != 0)	
			{
				f = 1;
				break;
			}
	}
	
	if(f == 1) printf("NO");
	else printf("YES");
}