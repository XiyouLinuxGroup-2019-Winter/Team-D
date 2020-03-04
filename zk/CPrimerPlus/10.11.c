#include <stdio.h>

void func1(int (*p)[5], int x) {
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < 5; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
 
}

void func2(int (*p)[5], int x) {
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < 5; j++) {
            p[i][j] *= 2;
        }
    }
}

int main()
{
    int arr[3][5] = {
        {1,2,3,4,5},
        {11,22,33,44,55},
        {111,222,333,444,555}
    };
    func1(arr, 3);
    func2(arr, 3);
    func1(arr, 3);
    return 0;
}

