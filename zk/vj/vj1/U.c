#include <stdio.h>
#include <string.h>

int main()
{
    char s[500001];
    scanf("%s", s);
    int i, j, k, m, n;
    int cnt = 0;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '[') {
            cnt++;
            break;
        }
    }
    for (j = i+1; j < strlen(s); j++) {
        if (s[j] == ':') {
            cnt++;
            break;
        }
    }
    for (k = strlen(s)-1; k > j; k-- ) {
        if (s[k] == ']') {
            cnt++;
            break;
        }
    }
    for (m = k-1; m > j; m--) {
        if (s[m] == ':') {
            cnt++;
            break;
        }
    }
    if (cnt < 4) {
        printf("-1\n");
    }
    else {
        for (n = j; n < m; n++) {
            if (s[n] == '|') {
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}

