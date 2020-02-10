#include <stdio.h>

int main()
{
    char n;
    scanf("%c", &n);
    int i, j, k;
    char s = 'A';
    char s1;
    for (i = 0; i <= n - 'A'; i++) {
        char x = 'A';
        for (j = n - 'A' - i; j > 0; j--) {
            printf(" ");
        }
        for (k = 0; k < i; k++) {
            printf("%c", x++);
        }
        printf("%c", s++);
        s1 = s - 2;
        for (k = 0; k < i; k++) {
            printf("%c", s1--);
        }
        printf("\n");
    }
    return 0;
}

