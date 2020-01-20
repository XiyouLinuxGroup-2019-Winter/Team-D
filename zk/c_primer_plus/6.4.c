#include <stdio.h>

int main()
{
    int i, j = 0,k;
    for (i = 0; i < 6; i++) {
        for (k = 0; k <= i; j++, k++) {
            printf("%c", 'A' + j);
        }
        printf("\n");
    }

    return 0;
}

