#include <stdio.h>
#include "string.h"

int main(int argc, char *argv[]) {
	char str1[100];	
	char str2[100];	
	
	scanf("%s", str1);
	
	int j = 0;
	for (int i = strlen(str1) - 1; i >= 0; i--, j++) 
		str2[j] = str1[i];
	
	str2[j] = 0;
	
	int cnt = 0;
	
	for(int i = strlen(str1) - 1; i > 0; i--)	
	{
		if(strcmp(str1, str2) != 0)
			{
				cnt = strlen(str1);
				break;
			}

		str1[i] = '\0';
		
		int j = 0;
		for (int i = strlen(str1) - 1; i >= 0; i--, j++) 
			str2[j] = str1[i];	
		
		str2[j] = 0;
	}
	
	printf("%d", cnt);
}

