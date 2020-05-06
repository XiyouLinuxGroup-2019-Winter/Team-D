#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    execlp("ls", "ls", "-l", NULL);
    perror("execlp");
    exit(1);
}