#include <stdio.h>
#include <string.h>

int main()
{
    char arr[5];
    int i;
    for (i = 0; i < 5; i++) {
        scanf("%c", &arr[i]);
    }
    for (i = 0; i < 5; i++) {
        printf("%c", arr[i]);
    }
    return 0;
}

