#include <stdio.h>

int main()
{
    int year = 0;
    int dollar_sum = 100;
    while (dollar_sum > 0) {
        dollar_sum *= 1.08;
        dollar_sum -= 10;
        year++;
    }
    printf("%d\n", year);

    return 0;
}

