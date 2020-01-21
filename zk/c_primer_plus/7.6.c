#include <stdio.h>

int main()
{
    char ch;
    int flag = 0;
    int cnt = 0;
    while (1) {
        scanf("%c", &ch);
        if (ch == '#') {
            break;
        }
        else {
            if (ch == 'e') {
                flag = 1;
            }
            if (ch != 'e' && ch != 'i') {
                flag = 0;
            }
            if (flag == 1 && ch == 'i') {
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);
    
    return 0;
}

