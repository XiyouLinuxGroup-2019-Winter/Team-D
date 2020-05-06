#include <stdio.h>
#include <dirent.h>

int main() {
    printf("%d\n", PATH_MAX); // 4096
    printf("%d\n", NAME_MAX); // 255
    return 0;
}