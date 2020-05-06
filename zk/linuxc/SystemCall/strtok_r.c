#include <stdio.h>
#include <string.h>

int main() {
    // 字符串切割函数strtok_r
    char buf[] = "hello world what test";
    char *save = buf, *p;

    while ((p = strtok_r(save, " ", &save)) != NULL) {
        printf("%s\n", p);
    }
    return 0;
}