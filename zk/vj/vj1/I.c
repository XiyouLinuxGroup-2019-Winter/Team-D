#include <stdio.h>

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    int i;
    int cnt = 0;
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++) {
        if (a[i] <= k) {
            cnt++;
        }
        else {
            break;
        }
    }
    if (cnt != n) {
        for (i = n-1; i >= 0; i--) {
            if (a[i] <= k) {
                cnt++;
            }
            else {
                break;
            }
        }
    }
    printf("%d\n", cnt);

    return 0;
}

