#include <stdio.h>

int main()
{
    double arr[5] = {1, 2, 3, 4, 5};
    int i;
    double max = arr[0];
    int idx;
    for (i = 1; i < 5; i++) {
        if (max < arr[i]) {
            max = arr[i];
            idx = i;
        }
    }
    printf("%d\n", idx);
    return 0;
}

