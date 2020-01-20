#include <stdio.h>

int main()
{
    float megabyte, megabit, second;
    scanf("%f %f", &megabit, &megabyte);
    second = megabyte * 8 / megabit;
    printf("At %.2f megabits per second, a file of %.2f megabytes\n", megabit, megabyte);
    printf("downloads in %.2f seconds\n", second);

    return 0;
}

