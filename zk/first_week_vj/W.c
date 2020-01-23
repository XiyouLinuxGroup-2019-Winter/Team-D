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
    int people = 0;
    int flag = 0;
    int max;
    int k = 1;
    for (j = 0; j < n; j++) {
        int cnt = 0;

        if (flag == 0) {
            max = a[][j];
        }
        else {
            j = 0;
            for ( ; k < n; k++) {
                max = a[k][j];
                break;
            }
        }
        for (i = 0; i < n; i++) {
            if (max > a[i][j]) {
                cnt++;
            } 
        }
        if (cnt == n-1) {
            people++;
            flag = 1;
        }
        else {
            flag = 0;
        }
    }

    printf("%d\n", people);

    return 0;
}

