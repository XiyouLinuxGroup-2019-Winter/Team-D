#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    int m;
    scanf("%d %d", &n, &m);
    getchar();
    char a[n][m];
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%c", &a[i][j]);
        }
        getchar();
    }
    int max;
    int cnt = 0;
    for (j = 0; j < m; j++) {
        max = 0;
        for (i = 0; i < n; i++) {
            if (max < a[i][j]) {
                max = a[i][j];
            } 
        }
        for (i = 0; i < n; i++) {
            if (a[i][j] == max) {
                cnt++;
            }
        }
    }

    printf("%d\n", cnt);

    return 0;
}

