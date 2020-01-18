/*
	图灵机， state表示正在执行的打印状态， 完成动作后进行状态转换
*/

#include <stdio.h>
#include "ctype.h"
#define WORD 1
#define SPACE 0

int main(int argc, char *argv[]) {
	char ch;
	int state = SPACE;
	
	ch = getchar();
	
	while(ch != EOF)
	{
		switch (state) {
			case SPACE:
					if(isspace(ch))
						{	
							putchar(ch);
							while(isspace(ch = getchar()))
								putchar(ch);
						}
					state = WORD;
					break;
			case WORD:
					if(isalpha(ch))
						{
							putchar(toupper(ch));
							while (isalpha(ch = getchar())) {
								putchar(ch);
							}
						}
					state = SPACE;
					break;
		}		
	}
}