#include <stdio.h>

int main()
{
    char ch;
    int cnt = 0;
    while (1) {
        scanf("%c", &ch);
        if (ch == '#') {
            break;
        }
        else {
            if (ch == '.') {
                ch = '!';
                cnt++;
            }
            else if (ch == '!') {
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);

    return 0;
}

