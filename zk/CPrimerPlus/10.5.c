#include <stdio.h>

int main()
{
    double arr[5] = {1, 2, 3, 4, 5};
    int i, j;
    for (i = 0; i < 5-1; i++) {
        for (j = 0; j < 5-i-1; j++) {
            double t;
            if (arr[j] > arr[j+1]) {
                t = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = t;
            }
        }
    }
    printf("%lf\n", arr[4] - arr[0]);
    return 0;
}

