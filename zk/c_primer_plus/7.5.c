#include <stdio.h>

int main()
{
    char ch;
    int cnt = 0;
    int flag = 0;
    while (1) {
        scanf("%c", &ch);
        switch(ch) {
        case '.' :cnt++;break;
        case '!' :cnt++;break;
        case '#' :flag = 1;break;  
        }
        if (flag == 1) {
            break;
        }
    }
    printf("%d\n", cnt);

    return 0;
}

