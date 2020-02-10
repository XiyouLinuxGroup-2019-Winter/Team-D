#include <stdio.h>

void func(int *arr1, int *arr2, int *arr3, int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr3[i] = arr1[i] + arr2[i];
    }
}

int main()
{
    int arr1[4] = {2,4,5,8};
    int arr2[4] = {1,0,4,6};
    int arr3[4];
    func(arr1, arr2, arr3, 4);
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d\n", arr3[i]);
    }    
    return 0;
}

