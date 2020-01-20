#include <stdio.h>

int main()
{
    int start_friend = 5;
    int week = 1;
    while (start_friend <= 150) {
        start_friend -= week;
        start_friend *= 2;
        week++;
        printf("%d\n", start_friend);
    }
    
    return 0;
}

