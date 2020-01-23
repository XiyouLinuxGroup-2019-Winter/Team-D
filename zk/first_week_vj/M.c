#include <stdio.h>

int main()
{
    long long n;
    int cnt = 0;
    scanf("%lld", &n);
    if (n == 0){
        printf("0\n");
    }
    else if ((n+1) % 2 == 1) {
        printf("%lld\n", n+1);
    }
    else {
        printf("%lld\n", (n+1)/2);
    }

    return 0;
}

