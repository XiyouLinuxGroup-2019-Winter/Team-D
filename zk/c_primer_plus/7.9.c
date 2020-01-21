#include <stdio.h>

int main()
{
    int num;
    int flag = 0;
    int i, j;
    scanf("%d", &num);
    while (num > 0) {
        for (i = 2; i <= num; i++) {
            flag = 0;
            for (j = 2; j < i; j++) {
                if (i % j == 0) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                printf("%d ", i);
            }
        }
        printf("\n");
        scanf("%d", &num);
    }
    return 0;
}

