#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define NORMAL        0 // 一般的命令
#define OUT_REDIRECT  1 // 输出重定向
#define IN_REDIRECT   2 // 输入重定向
#define HAVE_PIPE     3 // 命令中有管道

void print_prompt(); // 打印提示符
void explain_input(char *buf, int *argcount, char arglist[][256]);
void do_cmd(int argcount, char arglist[][256]);
int find_command(char *command);
void history();

int main(int argc, char *argv[]) {
    signal(SIGINT, SIG_IGN);
    int argcount = 0;
    char arglist[100][256];
    char **arg = NULL;
    char *buf = NULL;
    rl_bind_key('\t', rl_complete);

    while (1) {
        buf = (char *) malloc(sizeof(char) * 256);
        memset(buf, 0, 256);

        print_prompt();

        buf = readline(" ");
        int len = strlen(buf);
        // 直接回车处理
        if (!len) {
            continue;
        }
        // 空格后直接回车处理
        int cnt = 0;
        for (int i = 0; buf[i] != '\0'; ++i) {
            if (buf[i] == ' ') {
                cnt++;
            }
        }
        if (cnt == len) {
            continue;
        }
        add_history(buf);

//        保存history
//        int fd;
//        if ((fd = open("/tmp/history", O_RDWR | O_CREAT | O_APPEND, 0644) < 0)) {
//            perror("open");
//        }
//        if (write(fd, buf, len) < 0) {
//            perror("write");
//        }
//
//        if (write(fd, "\n", 1) < 0) {
//            perror("write");
//        }
//        close(fd2);

        if (strcmp(buf, "exit") == 0 || strcmp(buf, "logout") == 0) {
            break;
        }
        for (int i = 0; i < 100; ++i) {
            arglist[i][0] = '\0';
        }
        argcount = 0;

        explain_input(buf, &argcount, arglist);
        do_cmd(argcount, arglist);
        if (buf != NULL) {
            free(NULL);
            buf = NULL;
        }
    }
    exit(0);
}

void print_prompt() {
    uid_t uid;
    struct passwd *pw;

    uid = getuid();
    pw = getpwuid(uid);

    char *buf = (char *) malloc(sizeof(char) * PATH_MAX);
    getcwd(buf, PATH_MAX);
    printf("\033[;34m %s\033[0m", pw->pw_name);
    printf("@ubuntu-linux:");
    printf("\033[;36m%s\033[0m $ ", buf);
    free(buf);
}

void explain_input(char *buf, int *argcount, char arglist[100][256]) {
    char *p = buf;
    char *q = buf;
    int number = 0;

    while (1) {
        if (p[0] == '\0') {
            break;
        }
        if (p[0] == ' ') {
            p++;
        } else {
            q = p;
            number = 0;
            while (q[0] != ' ' && q[0] != '\0') {
                number++;
                q++;
            }
            strncpy(arglist[*argcount], p, number);
            arglist[*argcount][number] = '\0';
            *argcount += 1;
            p = q;
        }
    }
}

void do_cmd(int argcount, char arglist[100][256]) {
    int flag = 0, how = NORMAL, background = 0;
    int status, fd;
    char *arg[argcount+1], *argnext[argcount+1], *argnext2[argcount+1];
    char *file;
    pid_t pid;

    // 取出命令
    for (int i = 0; i < argcount; ++i) {
        arg[i] = (char *) arglist[i];
    }
    arg[argcount] = NULL;

    // 判断是否后台运行 &
    for (int j = 0; j < argcount; ++j) {
        if (strncmp(arg[j], "&", 1) == 0) {
            if (j == argcount - 1) {
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            } else {
                printf("wrong command\n");
                return;
            }
        }
    }

    // 内置命令 cd
    if (strncmp(arg[0], "cd", 2) == 0) {
        if (arg[1] == NULL || strcmp(arg[1], "~") == 0) {
            char *home_path = getenv("HOME");
            if ((chdir(home_path) < 0)) {
                perror("chdir");
            }
            return;
        } else if (arg[1][0] == '~') {
            char *home_path = getenv("HOME");
            char *path = (char *) malloc(sizeof(char) * PATH_MAX);
            strcpy(path, home_path);
            strcat(path, arg[1] + 1);
            if ((chdir(path) < 0)) {
                perror("chdir");
            }
            return;
        } else {
            if ((chdir(arg[1]) < 0)) {
                perror("chdir");
            }
            return;
        }
    }

    // 判断 < > |
    for (int k = 0; arg[k] != NULL; ++k) {
        if (strcmp(arg[k], ">") == 0) {
            how = OUT_REDIRECT;
            if (arg[k+1] == NULL) {
                printf("wrong command\n");
                return;
            }
        }
        if (strcmp(arg[k], "<") == 0) {
            how = IN_REDIRECT;
            if (k == 0) {
                printf("wrong command\n");
                return;
            }
        }
        if (strcmp(arg[k], "|") == 0) {
            flag++;
            how = HAVE_PIPE;
            if (arg[k+1] == NULL) {
                printf("wrong command\n");
                return;
            }
            if (k == 0) {
                printf("wrong command\n");
                return;
            }
        }
    }

    if (how == OUT_REDIRECT) {
        for (int i = 0; arg[i] != NULL; ++i) {
            if (strcmp(arg[i], ">") == 0) {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if (how == IN_REDIRECT) {
        for (int i = 0; arg[i] != NULL; ++i) {
            if (strcmp(arg[i], "<") == 0) {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if (how == HAVE_PIPE) {
        int cnt = 0;
        // 把管道后面的部分存入argnext，管道后面那部分是一个可执行的shell命令
        for (int i = 0; arg[i] != NULL; ++i) {
            if (strcmp(arg[i], "|") == 0) {
                arg[i] = NULL;
                int j;
                cnt++;
                for (j = i+1; arg[j] != NULL && strcmp(arg[j], "|") != 0; ++j) {
                    if (flag == 1) {
                        argnext[j-i-1] = arg[j];
                        argnext[j-i] = NULL;
                    } else if (flag == 2) {
                        if (cnt == 2) {
                            argnext2[j-i-1] = arg[j];
                            argnext2[j-i] = NULL;
                        } else {
                            argnext[j-i-1] = arg[j];
                            argnext[j-i] = NULL;
                        }
                    }
                }
//                argnext[j-i-1] = arg[j];
                if (flag == 1) {
                    break;
                }
            }
        }
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        return;
    }
    switch(how) {
        case NORMAL:
            if (pid == 0) {
                if (!strcmp(arg[0], "history")) {
                    history();
                    exit(0);
                }
                if (!(find_command(arg[0]))) {
                    printf("%s:command not found\n", arg[0]);
                    exit(0);
                }
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        case OUT_REDIRECT:
            if (pid == 0) {
                if (!strcmp(arg[0], "history")) {
                    history();
                    exit(0);
                }
                if (!find_command(arg[0])) {
                    printf("%s:command not found\n", arg[0]);
                    return;
                }
                fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        case IN_REDIRECT:
            if (pid == 0) {
                if (!strcmp(arg[0], "history")) {
                    history();
                    exit(0);
                }
                if (!(find_command(arg[0]))) {
                    printf("%s:command not found\n", arg[0]);
                    return;
                }
                fd = open(file, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        case HAVE_PIPE:
            if (pid == 0) {
                int pid2, pid3;
                int fd2[2], fd3[2];

                // fd[0] 读端
                // fd[1] 写端
                if (pipe(fd2) < 0) {
                    perror("pipe");
                    return;
                }

                // 多重管道处理
                if ((pid2 = fork()) < 0) {
                    perror("fork");
                    return;
                }

                if (pid2 > 0) {
                    close(fd2[0]);
                    dup2(fd2[1], STDOUT_FILENO);
                    if (!(find_command(arg[0]))) {
                        printf("%s:command not found\n", arg[0]);
                        return;
                    }
                    execvp(arg[0], arg);
                } else if (pid2 == 0) {
                    if (flag > 1) {
                        if (pipe(fd3) < 0) {
                            perror("pipe");
                            return;
                        }
                        if ((pid3 = fork()) < 0) {
                            perror("fork");
                            return;
                        }
                        if (pid3 > 0) {
                            close(fd2[1]);
                            close(fd3[0]);
                            dup2(fd2[0], STDIN_FILENO);
                            dup2(fd3[1], STDOUT_FILENO);
                            if (!(find_command(argnext[0]))) {
                                printf("%s:command not found\n", argnext[0]);
                                return;
                            }
                            execvp(argnext[0], argnext);
                        } else if (pid3 == 0) {
                            close(fd2[1]);
                            close(fd2[0]);
                            close(fd3[1]);
                            dup2(fd3[0], STDIN_FILENO);
                            if (!(find_command(argnext2[0]))) {
                                printf("%s:command not found\n", argnext2[0]);
                                return;
                            }
                            execvp(argnext2[0], argnext2);
                        }
                    } else {
                        close(fd2[1]);
                        dup2(fd2[0], STDIN_FILENO);
                        if (!(find_command(argnext[0]))) {
                            printf("%s:command not found\n", argnext[0]);
                            return;
                        }
                        execvp(argnext[0], argnext);
                    }
                }
            }
            break;
    }

    // 若命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if (background == 1) {
        return;
    }
    if (waitpid(-1, &status, 0) == -1) {
        printf("wait for child process errno\n");
    }
}

int find_command(char *command) {
    DIR *dp;
    struct dirent *dirp;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};

    if (strncmp(command, "./", 2) == 0) {
        command += 2;
    }

    int i = 0;
    while (path[i] != NULL) {
        if ((dp = opendir(path[i])) == NULL) {
            perror("opendir");
        }
        while ((dirp = readdir(dp)) != NULL) {
            if (strcmp(dirp->d_name, command) == 0) {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}

void history() {
    int fd = 0;
    char *buf = (char *)malloc(sizeof(char) * 1000);

    fd = open("/tmp/history", O_RDWR);
    if (fd < 0) {
        perror("open");
        return;
    }
    read(fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, strlen(buf));
    free(buf);
}