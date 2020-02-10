#include <stdio.h>

int main()
{
    int n;
    int even_num = 0, ave_even = 0, odd_num = 0, ave_odd = 0;
    int even_sum = 0, odd_sum = 0;
    while (1) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        if (n % 2 == 0) {
            even_num++;
            even_sum += n;
        }
        else {
            odd_num++;
            odd_sum += n;
        }
    }
    ave_even = even_sum / even_num;
    ave_odd = odd_sum / odd_num;
    printf("%d %d %d %d\n", even_num, ave_even, odd_num, ave_odd);

    return 0;
}

