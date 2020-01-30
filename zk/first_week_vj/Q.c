#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[100];
    int i;
    while (gets(str)) {
        for (i = 0; i < strlen(str); i++) {
            if (i == 0) {
                str[0] = str[0] - 32;
            }
            if (str[i] == ' ') {
                str[i+1] -= 32;
            }
            printf("%c", str[i]);
        }
        printf("\n");
    }
    return 0;
}

