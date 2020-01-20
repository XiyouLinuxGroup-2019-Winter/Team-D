#include <stdio.h>
#define X 60
int main()
{
    int time;
    scanf("%d", &time);
    while (time > 0) {
        int hour = time / X, minute = time % X;
        printf("%d %d\n", hour, minute);
        scanf("%d", &time);
    }
    return 0;
}

