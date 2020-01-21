#include <stdio.h>

int main()
{
    int cnt = 0;
    char ch;
    while (1) {
        scanf("%c", &ch);
        if (ch == '#') {
            break;
        }
        printf("%c %d ", ch, ch);
        cnt++; 
        if (cnt % 8 == 0) {
            printf("\n");
        }
    }

    return 0;
}

