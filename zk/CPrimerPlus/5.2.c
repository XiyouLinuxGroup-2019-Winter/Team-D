#include <stdio.h>

int main()
{
    int num;
    scanf("%d", &num);
    int i;
    printf("%d", num);
    for (i = 1; i <= 10; i++) {
        printf(" %d", num + i);
    }
    return 0;
}

