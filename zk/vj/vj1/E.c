#include <stdio.h>

int main()
{
    int N, M;
    scanf("%d", &N);
    int i, j;
    int num, sum = 0;
    for (i = 0; i < N; i++) {
        sum = 0;
        scanf("%d", &M);
        for (j = 0; j < M; j++) {
            scanf("%d", &num);
            sum += num;
        }
        printf("%d\n", sum);
        printf("\n");
        printf("\n");
    }

    return 0;
}

