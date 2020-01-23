#include <stdio.h>
#include <string.h>

int main()
{
    char n[100000] = {0};
    scanf("%s", n);
    int cnt = 0;
    int i, j;
    int sum = 0;
    int sum1[10000];
    while (n[0] != '0') {
        cnt = strlen(n);
        sum = 0;
        for (i = 0; i < cnt; i++) {
            sum += n[i] - '0';
        }
        while (sum >= 10) {
            j = 0;
            while (sum != 0) {
                sum1[j++] = sum % 10;
                sum /= 10;
            }
            for (i = 0; i < j; i++) {
                sum += sum1[i];
            }
        }
        printf("%d\n", sum);
        scanf("%s", n);
    }
    return 0;
}

