#include <stdio.h>

void print(char ch, int i, int j);

int main()
{
    char ch = 'a';
    int i = 3, j = 5;
    print(ch, i, j);
    return 0;
}

void print(char ch, int i, int j) {
    int k = j;
    int m = i;
    for (j = 0; j < k; j++) {
        for (i = 0; i < m; i++) {
            printf("%c", ch);
        }
        printf("\n");
    }
}
