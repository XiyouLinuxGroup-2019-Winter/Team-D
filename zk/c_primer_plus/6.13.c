#include <stdio.h>
#include <math.h>

int main()
{
    int a[8];
    int i;
    for (i = 0; i < 8; i++) {
        a[i] = pow(2, (i + 1)); 
    }
    for (i = 0; i < 8; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}

