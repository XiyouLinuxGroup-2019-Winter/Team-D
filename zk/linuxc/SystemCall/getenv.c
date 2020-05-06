#include <stdio.h>
#include <stdlib.h>

int main() {
//    char *home_path = getenv("HOME");
//    printf("%s\n", home_path);
    printf("PATH=%s\n", getenv("PATH"));
    setenv("PATH", "hello", 1);
    printf("PATH=%s\n", getenv("PATH"));
    return 0;
}