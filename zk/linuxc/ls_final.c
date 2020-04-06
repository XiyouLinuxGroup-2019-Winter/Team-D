#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <pwd.h>
#include <linux/limits.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <signal.h>

#define PARAM_NONE 0
#define PARAM_a 1
#define PARAM_l 2
#define PARAM_i 4 // i列出inode号码
#define PARAM_t 8 // t以时间排序而不是用文件名
#define PARAM_r 16 // r将排序结果反向输出
#define PARAM_R 32
#define NORMAL 0
#define GREEN  1
#define BLUE   2

#define MAXROWLEN 80

int g_leavelen = MAXROWLEN;
int g_maxlen;

void display_dir(int flag_param, char *path);

void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d", line);
    perror(err_string);
    if (errno != 13) {
        exit(0);
    } else {
        printf("无权限\n");
    }
}

// 打印颜色
void printfColor(char *name, int color) {
    if (color == GREEN) {
        printf("\033[;32m %-s\033[0m" "",name);
    } else if (color == BLUE) {
        printf("\033[;36m %-s\033[0m" "",name);
    } else if (color == NORMAL) {
        printf(" %-s",name);
    }
}

/**
 * -l实现
 * @param sb 文件信息结构体
 * @param name 文件名
 * @param color 颜色
 */
void display_attribute(struct stat sb, char *name, int color) {
    char time_buf[32];
    struct passwd *psd;
    struct group *grp;

    if (S_ISLNK(sb.st_mode)) {
        printf("l");
    } else if (S_ISREG(sb.st_mode)) {
        printf("-");
    } else if (S_ISDIR(sb.st_mode)) {
        printf("d");
    } else if (S_ISCHR(sb.st_mode)) {
        printf("c");
    } else if (S_ISBLK(sb.st_mode)) {
        printf("b");
    } else if (S_ISFIFO(sb.st_mode)) {
        printf("f");
    } else if (S_ISSOCK(sb.st_mode)) {
        printf("s");
    }

    if (sb.st_mode & S_IRUSR) {
        printf("r");
    } else {
        printf("-");
    }
    if (sb.st_mode & S_IWUSR) {
        printf("w");
    } else {
        printf("-");
    }
    if (sb.st_mode & S_IXUSR) {
        printf("x");
    } else {
        printf("-");
    }
    if (sb.st_mode & S_IRGRP) {
        printf("r");
    } else {
        printf("-");
    }
    if (sb.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (sb.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (sb.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if (sb.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (sb.st_mode & S_IXOTH){
        printf("x");
    }
    else
        printf("-");

    printf("\t");

    psd = getpwuid(sb.st_uid);
    grp = getgrgid(sb.st_gid);

    printf("%4ld ",sb.st_nlink);
    printf("%-8s  ",psd->pw_name);
    printf("%-8s", grp->gr_name);

    printf("%6ld", sb.st_size);
    strcpy(time_buf,ctime(&sb.st_mtime)); // 把时间转换成普通表示格式

    time_buf[strlen(time_buf)-1] = '\0'; // 去掉换行符
    printf("  %s", time_buf);

    printfColor(name, color);
    printf("\n");
}

/**
 * 没有-l时的输出
 * @param name 名字
 * @param color 颜色
 */
void display_single(char *name, int color) {
    int i;
    int len;

    if (g_leavelen < g_maxlen) {
        printf("\n");
        g_leavelen = MAXROWLEN;
    }
    len = strlen(name);
    len = g_maxlen - len;
    printfColor(name,color);
    for(i = 0;i < len;i++) {
        printf(" ");
    }
    printf(" ");
    g_leavelen -= (g_maxlen + 2);
}

/**
 * -i 打印inode号码
 * @param name 文件名
 * @param color 颜色
 */
void display_inode(char *name, int color) {
    int i;
    int len;
    struct stat sb;
    if(g_leavelen < g_maxlen) {
        printf("\n");
        g_leavelen = MAXROWLEN;
    }
    if(lstat(name,&sb) == -1) {
        my_err("lstat",__LINE__);
    }
    printf("%ld ",sb.st_ino);
    len = strlen(name);
    len  = g_maxlen - len;
    printfColor(name,color);
    for(i = 0;i < len;i++) {
        printf(" ");
    }
    printf(" ");
    g_leavelen -= (g_maxlen + 2 + 8);
}

/**
 * 打印文件函数
 * @param flag 权限
 * @param pathname 包含了文件名的路径名
 */
void display(int flag, char *pathname) {
    int i;
    int j;
    struct stat sb;
    char name[PATH_MAX + 1];
    int color = 0;

    //获取文件名称  /home/zk/a.c
    for (i = 0, j = 0; i < (int)strlen(pathname); i++) {
        if (pathname[i] == '/') {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';
    // name = "'a''.''c''\0''m''e'"

    //获取文件信息
    lstat(pathname,&sb);

    //判断颜色
    if (S_ISDIR(sb.st_mode)) {
        color = BLUE;
    } else if ((sb.st_mode & S_IXUSR) && color != BLUE) {
        color = GREEN;  // 是可执行文件
    } else {
        color = NORMAL;
    }

    // 去掉tRr权限, 放到别处处理
    if (flag & PARAM_t) { // t 按时间排序打印文件名
        flag -= PARAM_t;
    }
    if (flag & PARAM_R) {  // R 递归目录打印文件名
        flag -= PARAM_R;
    }
    if (flag & PARAM_r) { // r 反向排序打印文件名
        flag -= PARAM_r;
    }

    // name = "'a''.''c''\0''m''e'"
    switch (flag) {
        case PARAM_NONE:        //没有参数ls 0
            if(name[0] != '.') { // 忽略掉. 和..目录
                display_single(name,color);
            }
            break;
        case PARAM_l:           //-l 2
            if(name[0] != '.') { // 忽略掉. 和..目录
                display_attribute(sb,name,color);
            }
            break;
        case PARAM_a:           //-a 1
            display_single(name,color); // 不忽略掉. 和..目录
            break;
        case PARAM_i:           //-i 4
            if(name[0] != '.') {
                display_inode(name,color);
            }
            break;
            // 支持ali三种参数的任意组合-al -ai -li -ail
        case PARAM_a + PARAM_l:     //-la
            display_attribute(sb,name,color); // 不忽略掉. 和..目录
            break;
        case PARAM_a + PARAM_i: //-ia
            display_inode(name,color);
            break;
        case PARAM_l + PARAM_i: //-il
            if(name[0] != '.') {
                printf(" %ld",sb.st_ino);
                display_dir(flag,name);
            }
            break;
        case PARAM_a + PARAM_l + PARAM_i:   //-ial
            printf("%ld ",sb.st_ino);
            display_dir(flag,name);
            break;
        default:
            break;
    }
}

/**
 * 显示目录中的文件
 * @param flag_param 权限
 * @param path 路径
 */
void display_dir(int flag_param, char *path) {
    // path = "/home/zk/"
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    struct stat sb;
    char **filename;
    filename = (char **)malloc(sizeof(char *) * 20000);
    int t;
    for (t = 0; t < 20000; ++t) {
        filename[t] = (char *)malloc(sizeof(char *) * 20000);
    }
    long *filetime;
    filetime = (long *)malloc(sizeof(long) * 20000);
    char temp[PATH_MAX];
    long timeTemp;

    dir = opendir(path);
    if(dir == NULL){
        my_err("opendir",__LINE__);
    }
    /*获取目录下文件的个数，以及最大长度*/
    while((ptr = readdir(dir))!= NULL){
        if(g_maxlen < (int)strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }

    closedir(dir);

    if(count > 20000) {
        my_err("too many files under this directory",__LINE__);
    }

    int i;
    int j;
    int len = strlen(path);

    dir = opendir(path);

    /*获取目录下文件名和时间参数*/
    for(i = 0;i < count;i++) {
        ptr = readdir(dir);
        if(ptr == NULL) {
            my_err("readdir",__LINE__);
        }

        // filename[i] = "/home/zk/"
        strncpy(filename[i],path,len);
        filename[i][len] = 0;

        // filename[i] = "/home/zk/a.c"
        strcat(filename[i], ptr->d_name);
        filename[i][len + strlen(ptr->d_name)] = 0;
        lstat(filename[i], &sb);
        filetime[i] = sb.st_mtime;
    }

    closedir(dir);

    //排序
    if(flag_param & PARAM_t){ // 含-t按时间排序, 时间大的放前面
        for(i = 0;i < count - 1;i++) {
            for(j = 0;j < count - 1 -i;j++) {
                if(filetime[j] < filetime[j+1]) {
                    timeTemp = filetime[j]; // 交换时间
                    filetime[j] = filetime[j+1];
                    filetime[j+1] = timeTemp;
                    strcpy(temp,filename[j]); // 交换文件名
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }
        }
    } else {                                    //按文件名排序
        for(i = 0;i < count - 1;i++) {
            for(j = 0;j < count - 1 -i;j++) {
                if(strcmp(filename[j],filename[j+1]) > 0) {
                    strcpy(temp,filename[j]);
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }
        }
    }

    if(flag_param & PARAM_R) {   // -R               //如果含r倒序输出
        if(flag_param & PARAM_r) {  // -r   包含-Rr
            for(i = count - 1;i >= 0;i--) {
                // printColor("%s", filename);
                display(flag_param,filename[i]);
            }
            for(i = count - 1;i >= 0;i--) {
                if((stat(filename[i],&sb)) == -1) {
                    my_err("stat",__LINE__);
                }
                //判断文件是否是目录
                if(S_ISDIR(sb.st_mode)) {
                    // filename[i] = "/home/zk"
                    len = strlen(filename[i]);
                    //.和..不能递归, 忽略
                    // filename[i] = "/home/zk/."
                    // filename[i] = "/home/zk/.."
                    if((filename[i][len-1] == '.' && filename[i][len-2] == '/') ||
                       (filename[i][len-1] == '.' && filename[i][len-2] == '.' && filename[i][len-3] == '/')) {
                        continue;
                    }
                    printf("\n\n%s:",filename[i]);

                    // filename[i] = "/home/zk/"
                    strcat(filename[i],"/"); //一定要加上
                    display_dir(flag_param,filename[i]); // 递归
                } else {
                    // 不是目录filename[i] = "/home/zk/a.c"
                    // printColor("%s", filename);
                    display(flag_param,filename[i]);
                }
            }
        } else {    // -R
            for(i = 0;i < count;i++) {
                // filename[i] = "/home/zk/a.c"
                stat(filename[i],&sb);
                //判断文件是否是目录
                if(S_ISDIR(sb.st_mode)) {
                    len = strlen(filename[i]);
                    //.和..不能递归, 忽略
                    // filename[i] = "/home/zk/."
                    // filename[i] = "/home/zk/.."
                    if((filename[i][len-1] == '.' && filename[i][len-2] == '/') ||
                       (filename[i][len-1] == '.' && filename[i][len-2] == '.' && filename[i][len-3] == '/')) {
                        continue;
                    }
                    printf("\n\n%s:\n",filename[i]);

                    strcat(filename[i],"/"); // 注意
                    display_dir(flag_param,filename[i]); // 递归
                } else {
                    display(flag_param,filename[i]); // 打印
                }
            }
        }
    }else { // 没有-R
        if(flag_param & PARAM_r) {   // -r

            for(i = count - 1;i >= 0;i--) {
                display(flag_param,filename[i]); // 逆序打印
            }
        } else {    // 无, 没有-Rr
            for(i = 0;i < count;i++) {
                display(flag_param,filename[i]);
            }
        }
    }

    // 没有-l打印空行(格式)
    if((flag_param & PARAM_l) == 0) {
        printf("\n");
    }

// 释放内存
    for(i = 0;i < 20000;i++) {
        free(filename[i]);
    }
    free(filename);
    free(filetime);
}

int main(int argc, char *argv[]) {
    int i = 0, j = 0 , k = 0;
    int num = 0;
    char path[PATH_MAX+1];
    char param[32];
    int  flag_param = PARAM_NONE;
    struct stat  buf;
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, NULL);

    //解析其参数，以-为标志
    // ./my_ls -Rl /home/zk
    // 有参数num = 1 没有参数num = 0
    for(i = 1; i < argc;i++) {
        if(argv[i][0] == '-') {
            for(k = 1;k < (int)strlen(argv[i]);k++,j++) {
                param[j] = argv[i][k];
            }
            num++;
        }
    }
// j =2 k = 3
    for(i = 0;i < j;i++) {
        if(param[i] == 'a'){
            flag_param |= PARAM_a;
            continue;
        }
        else if(param[i] == 'l'){
            flag_param |= PARAM_l;
            continue;
        }
        else if(param[i] == 'i'){
            flag_param |= PARAM_i;
            continue;
        }
        else if(param[i] == 'r'){
            flag_param |= PARAM_r;
            continue;
        }
        else if(param[i] == 't'){
            flag_param |= PARAM_t;
            continue;
        }else if(param[i] == 'R'){
            flag_param |= PARAM_R;
            continue;
        }
        else{
            printf("my_ls: no avail option -%c\n", param[i]);
            exit(1);
        }
    }
    param[j] = 0;
    //默认为当前路径
    // ls num = 0 argc = 1
    // ls -Rl num = 1 argc = 2
    if((num+1) == argc) {
        strcpy(path,"./");
        path[2] =  0;
        display_dir(flag_param,path);
        return 0;
    }

    i = 1;
    do{
        if(argv[i][0] == '-') {
            i++;
            continue;
        } else {
            //得到具体路径
            strcpy(path, argv[i]);
            if(stat(path,&buf) == -1)
                my_err("stat",__LINE__);

            //判断是否为目录文件
            if(S_ISDIR(buf.st_mode)) {
                if(path[strlen(argv[i]) - 1] != '/') {
                    path[strlen(argv[i])]  = '/';
                    path[strlen(argv[i])+1] = 0;
                }
                else {
                    path[strlen(argv[i])] = 0;
                }
                display_dir(flag_param,path);//按照目录输出
                i++;
            } else {
                //按照文件输出
                display(flag_param,path);
                i++;
            }
        }
    } while(i < argc);

    return 0;
}
