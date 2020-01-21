#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    int geton, getoff;
    int sum = 0;
    int max;
    for (i = 0; i < n; i++) {
        scanf("%d %d", &getoff, &geton);
        sum = sum + geton - getoff;
        if (i == 0) {
            max = sum; 
        }
        if (max < sum) {
            max = sum;
        }
    }
    printf("%d\n", max);
    
    return 0;
}

