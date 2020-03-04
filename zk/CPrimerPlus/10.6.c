#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

int main()
{
    double arr[N] = {1,2,3,4,5};
    int i;
    for (i = 0; i < N/2; i++) {
        int t = arr[i];
        arr[i] = arr[4-i];
        arr[4-i] = t;
    } 
    for (i = 0; i < N; i++) {
        printf("%lf\n", arr[i]);
    }
    return 0;
}

