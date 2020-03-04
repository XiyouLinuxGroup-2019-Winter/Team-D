#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    int i, j, k;
    int sum = 0;
    char str[10000] = {0};
    for (i = 0; i < n; i++) {
        scanf("%s", str);
        j = strlen(str);
        sum = 0;
        for (k = 0; k < j; k++) {
            if (str[k] >= '0' && str[k] <= '9') {
                sum++;
            }
        }
        printf("%d\n", sum);
    }

    return 0;
}

