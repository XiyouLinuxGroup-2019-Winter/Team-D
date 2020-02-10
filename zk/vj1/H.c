#include <stdio.h>

int main()
{
    int n, i;
    int leader, children, girl;
    int cnt = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &leader, &children, &girl);
        if ((leader && children) || (leader && girl )|| (children && girl)) {
            cnt++;
        }  
    }
    printf("%d\n", cnt);
    return 0;
}

