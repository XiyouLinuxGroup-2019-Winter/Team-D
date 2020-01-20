#include <stdio.h>

int main()
{
    int first_num, second_num;
    scanf("%d %d", &first_num, &second_num);
    while (second_num > 0) {
        printf("%d\n", second_num % first_num);
        scanf("%d", &second_num);
    }

    return 0;
}

