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

int main(int argc, char *argv[]) {
    signal(SIGINT, SIG_IGN);
    int argcount = 0;
    char arglist[100][256];
    char **arg = NULL;
    char *buf = NULL;

    // 将readline配置为在按下Tab键时自动完成路径。
    rl_bind_key('\t', rl_complete);

    while (1) {
        buf = (char *) malloc(sizeof(char) * 256);
        memset(buf, 0, 256);

        print_prompt();

        buf = readline(" ");
        int len = strlen(buf);
        if (!len) {
            continue;
        }
        add_history(buf);
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
    int flag = 0, how = 0, background = 0;
    int status, fd;
    char *arg[argcount + 1], *argnext[argcount + 1];
    char *file;
    pid_t pid;

    for (int i = 0; i < argcount; ++i) {
        arg[i] = (char *) arglist[i];
    }
    arg[argcount] = NULL;

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

    for (int k = 0; arg[k] != NULL; ++k) {
        if (strcmp(arg[k], ">") == 0) {
            flag++;
            how = OUT_REDIRECT;
            if (arg[k+1] == NULL) {
                flag++;
            }
        }
        if (strcmp(arg[k], "<") == 0) {
            flag++;
            how = IN_REDIRECT;
            if (k == 0) {
                flag++;
            }
        }
        if (strcmp(arg[k], "|") == 0) {
            flag++;
            how = HAVE_PIPE;
            if (arg[k+1] == NULL) {
                flag++;
            }
            if (k == 0) {
                flag++;
            }
        }
    }

    if (flag > 1) {
        printf("wrong command\n");
        return;
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
        for (int i = 0; arg[i] != NULL; ++i) {
            if (strcmp(arg[i], "|") == 0) {
                arg[i] = NULL;
                int j;
                for (j = i+1; arg[j] != NULL; ++j) {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];
                break;
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
                if (!find_command(arg[0])) {
                    printf("%s:command not found\n", arg[0]);
                    exit(0);
                }
                fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        case IN_REDIRECT:
            if (pid == 0) {
                if (!(find_command(arg[0]))) {
                    printf("%s:command not found\n", arg[0]);
                    exit(0);
                }
                fd = open(file, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        case HAVE_PIPE:
            if (pid == 0) {
                int pid2;
                int status2;
                int fd2;

                if ((pid2 = fork()) < 0) {
                    printf("");
                }
            }
        default:
            break;
    }

    if (background == 1) {
        return;
    }
    if (waitpid(pid, &status, 0) == -1) {
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