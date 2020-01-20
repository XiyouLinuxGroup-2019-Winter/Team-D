#include <stdio.h>
#define NUM 8

int main()
{
    char a[NUM];
    int i;
    for (i = 0; i < NUM; i++) {
        scanf("%c", &a[i]);
    }
    for (i = NUM - 1; i >= 0; i--) {
        printf("%c", a[i]);
    }

    return 0;
}

