#include <stdio.h>
#include <string.h>

int main()
{
    char str[50];
    scanf("%s", str);
    int cnt = strlen(str);
    int i, j, k;
    int flag = 0;
    int flag1 = 0;
    for (i = 0; i < cnt; i++) {
        for (j = i+1; j < cnt; j++) {
            if (str[i] != str[j]) {
                flag1 = 1;
            }
        }
    }
    if (flag1 == 0) {
        printf("0\n");
        return 0;
    }
    if (cnt % 2 == 1) {
        for (i = 0, j = cnt-1; i < cnt/2; i++,j--) {
            if (str[i] != str[j]) {
                flag = 1;
            }   
        } 
        if (flag == 0) {
            printf("%d\n", cnt-1);
        }
        else {
            printf("%d\n", cnt);
        }
    }
    else {
        for (i = 0, j = cnt-1; i < cnt/2; i++,j--) {
            if (str[i] != str[j]) {
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("%d\n", cnt-1);
        }
        else {
            printf("%d\n", cnt);
        }
    }
    return 0;
}

