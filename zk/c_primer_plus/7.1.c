#include <stdio.h>

int main()
{
    char ch;
    int space = 0, newline = 0, other = 0;
    while (1) {
        scanf("%c", &ch);
        if (ch == ' ') {
            space++;
        }
        else if (ch == '\n') {
            newline++;
        }
        else if (ch == '#') {
            break;
        }
        else {
            other++;
        }
    }
    printf("%d %d %d\n", space, newline, other);

    return 0;
}

