#include <stdio.h>

int main()
{
    int height;
    scanf("%d", &height);
    double centimeter_height = 2.54 * height;
    printf("%lf\n", centimeter_height);
    return 0;
}

