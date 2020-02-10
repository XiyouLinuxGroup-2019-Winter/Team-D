#include <stdio.h>

void copy_ptr(double *arr, double *dest, int x) {
    int i;
    for (i = 0; i < x; i++) {
        dest[i] = *(arr+i); 
    }
}

int main()
{
    double arr[7] = {1,2,3,4,5,6,7};
    double dest[3];

    copy_ptr(arr+2, dest, 3);
    int i;
    for (i = 0; i < 3; i++) {
        printf("%lf\n", dest[i]);
    }
    return 0;
}

