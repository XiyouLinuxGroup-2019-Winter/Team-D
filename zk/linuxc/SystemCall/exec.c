#include <stdio.h>
#include <unistd.h>

int main() {
    char *argvv[] = {"ls", "-l", NULL};
    printf("hello\n");
    execl("/bin/ls", "ls", "-l", NULL);
//    execlp("ls", "ls", "-l", NULL);
//    execv("/bin/ls", argvv);
//    execvp("ls", argvv);

    printf("world\n");
    return 0;
}