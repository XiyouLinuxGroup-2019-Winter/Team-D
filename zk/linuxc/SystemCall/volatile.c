#include <stdio.h>

void do_sig(int n) {
    n = 0;
}

volatile int n = 5;

int main() {

    while (n) {
        printf("Hello");
    }
    return 0;
}