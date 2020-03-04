#include <stdio.h>

int main()
{
    float height_inch;
    scanf("%f", &height_inch);
    char name[10];
    scanf("%s", name);
    float height_foot = height_inch / 12.0;
    printf("%s, you are %.3f feet tall.\n", name, height_foot);
    return 0;
}

