#include <stdio.h>

int main()
{
    int N;
    int num, sum = 0;
    int i;
    while (~scanf("%d", &N)) {
        sum = 0;
        for (i = 0; i < N; i++) {
            scanf("%d", &num);
            sum += num;
        }
        printf("%d\n", sum);
    }
    return 0;
}

