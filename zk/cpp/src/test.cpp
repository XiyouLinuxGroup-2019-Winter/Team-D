#include <iostream>

int main()
{
    int no = 4;
    if (no == 1) {
        printf("no is 1");
    }
    else if (no == 2) {
        printf("no is 2");
    }
    else if (no == 3) {
        printf("no is 3");
    }
    else if (no == 4) {
        printf("no is 4");
    }
    return 0;
}

/*对应汇编
mov     dword ptr[no], 4
cmp     dword ptr[no], 1
jne     main + 44h()*/
