#include <stdio.h>

int main()
{
    int upper_limit, lower_limit;
    scanf("%d %d", &upper_limit, &lower_limit);
    int i;
    for (i = lower_limit; i <= upper_limit; i++) {
        printf("%d\t%d\t%d\n", i, i * i, i * i * i);
    }
    
    return 0;
}

