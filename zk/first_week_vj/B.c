#include <stdio.h>

int main()
{
    int N, M;
    scanf("%d", &N);
    int num, sum = 0;
    int i, j;
    for (i = 0; i < N; i++) {
        scanf("%d", &M);
        sum = 0;
        for (j = 0; j < M; j++) {
            scanf("%d", &num);
            sum += num;
        }
        printf("%d\n", sum);
    }
    return 0;
}

