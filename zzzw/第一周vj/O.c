#include <stdio.h>
#include "string.h"

int main(int argc, char *argv[]) {
	char str[10050];
	
	scanf("%s", str);
	
	while(strcmp(str, "0") != 0)
	{

		while(strlen(str) != 1)
			{
				int sum = 0;
				
				for(int i = 0; i < strlen(str); i++)			
					sum += str[i] - '0';
				
				sprintf(str, "%d", sum);
			}
		printf("%s\n", str);
		scanf("%s", str);
	}
}