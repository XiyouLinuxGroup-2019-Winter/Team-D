#include <stdio.h>

int main()
{
    int total_day, week, day;
    scanf("%d", &total_day);
    week = total_day / 7;
    day = total_day % 7;
    printf("%d %d", week, day);
    return 0;
}

