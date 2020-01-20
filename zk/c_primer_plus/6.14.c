#include <stdio.h>

int main()
{
    double a[8], b[8];
    int i, j;
    for (i = 0; i < 8; i++) {
        scanf("%lf", &a[i]);
    }
    for (j = 0; j < 8; j++) {
        if (j == 0) {
            b[j] = a[j];
        }
        else {
            b[j] = b[j - 1] + a[j];
        }
    }
    for (i = 0; i < 8; i++) {
        printf("%lf\t", a[i]);
    }
    printf("\n");
    for (i = 0; i < 8; i++) {
        printf("%lf\t", b[i]);
    }
    return 0;
}

