#include <stdio.h>

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    char password[101] = {0};
    char i;
    int j = 0;
    int cnt = 0;
    while (cnt != n) {
        for (i = 'a'; i <= 'z'; i++) {
            password[j++] = i;
            if (i == 'a' + k-1) {
                i = 'a' - 1;
            }
            cnt++;
            if (cnt == n) {
                break;
            }
        }
    }
    printf("%s\n", password);
    
    return 0;
}

