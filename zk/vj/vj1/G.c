#include <stdio.h>

int main()
{
    int d1, d2, d3;
    scanf("%d %d %d", &d1, &d2, &d3);
    if (d1 + d2 <= d3) {
        printf("%d\n", d1 + d1 + d2 + d2);
    }
    else if (d1 + d3 <= d2){
        printf("%d\n", d1 + d3 + d1 + d3);
    }
    else if (d2 + d3 <= d1){
        printf("%d\n", d2 + d2 + d3 + d3);
    }
    else {
        printf("%d\n", d1 + d2 + d3);
    }
    return 0;
}

