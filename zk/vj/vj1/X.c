#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int v[n];
    int i, j;
    int cnt = 0;
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    if (n == 2) {
        printf("0\n");
    }
    else {
        int min = v[0], max = v[n-1];
        for (i = 0; i < n; i++) {
            if (min > v[i]) {
                min = v[i];
            }
            if (max < v[i]) {
                max = v[i];
            }
        }
        for (i = 0; i < n; i++) {
            if (v[i] > min && v[i] < max) {
                cnt++;
            }
        }
        printf("%d\n", cnt); 
    }

    return 0;
}

