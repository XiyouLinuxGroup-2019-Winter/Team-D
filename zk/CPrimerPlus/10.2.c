#include <stdio.h>

void copy_arr(double target1[], double source[], int num) {
    int i;
    for (i = 0; i < num; i++) {
        target1[i] = source[i];
    }
}

void copy_ptr(double *target2, double *source, int n) {
    int i;
    for (i = 0; i < n; i++) {
        *target2++ = *source++;
    }
}

void copy_ptrs(double *target3, double *source, double *p) {
    while (source != p) {
        *target3++ = *source++;
    }
}

int main()
{
    double source[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double target1[5];
    double target2[5];
    double target3[5];
    copy_arr(target1, source, 5);
    copy_ptr(target2, source, 5);
    copy_ptrs(target3, source, source + 5);
    int i;
    for (i = 0; i < 5; i++) {
        printf("%lf\n", target1[i]);
        printf("%lf\n", target2[i]);
        printf("%lf\n", target3[i]);
    }
    return 0;
}

