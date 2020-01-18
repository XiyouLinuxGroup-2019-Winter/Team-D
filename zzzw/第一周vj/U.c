#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char str[500050];
	
	scanf("%s", str);
	
	int i = 0;
	int end = strlen(str) - 1;
	
	while(i < strlen(str) && str[i] != '[')
		i++;
	
	if(i == strlen(str))
		printf("-1");
	else {
		while(end > i && str[end] != ']')
			end--;
		
		if(end == i)
			printf("-1");
		else {
			int fnt = i;
			int tail = end;
			
			while(fnt < end && str[fnt] != ':')
				fnt++;
			if(fnt == end)
				printf("-1");
			else {
				while(tail > fnt && str[tail] != ':')
					tail--;
				if(tail == fnt)
					printf("-1");
				else {
					int cnt = 0;
					
					for (int j = fnt; j < tail; j++) {
						if(str[j] == '|')
							cnt++;
					}
					
					printf("%d", cnt + 4);
				}
			}	
			
		}
	}
}