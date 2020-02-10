#include <stdio.h>

int fun(int n) {
    int i;
    int sum = 0;
    for (i = 1; i <= n-1; i++) {
        sum += i;
    }
    return sum;
}
int main()
{
    int N;
    int time;
    int a, b;
    while (~scanf("%d", &N)) {
            a = N / 2;
            b = N - a;
            printf("%d\n", fun(a) + fun(b));
    }

    return 0;
}

