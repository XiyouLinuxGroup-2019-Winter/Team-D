#include <stdio.h>

int main()
{
    int upper_limit, lower_limit;
    scanf("%d %d", &lower_limit, &upper_limit);
    while  (upper_limit > lower_limit) {
        int i;
        int sum = 0;
        for (i = lower_limit; i <= upper_limit; i++) {
            sum += i * i;
        }
        printf("%d\n", sum);
        scanf("%d %d", &lower_limit, &upper_limit);
    }

    return 0;
}

