#include <stdio.h>

int main()
{
    int n;
    int i, j;
    while (~scanf("%d", &n)) {
        int a[n][n];
        for (i = 0; i < n; i++) {
            a[i][0] = 1;
            a[i][i] = 1;
        }
        for (i = 2; i < n; i++) {
            for (j = 1; j <= i-1; j++) {
                a[i][j] = a[i-1][j-1] + a[i-1][j]; 
            }
        }
        for (i = 0; i < n; i++) {
            printf("%d", a[i][0]);
            for (j = 1; j <= i; j++) {
                printf(" %d", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}

