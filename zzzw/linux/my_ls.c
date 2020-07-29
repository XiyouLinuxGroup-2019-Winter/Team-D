#pragma comment(linker, "/STACK:102400000,102400000")
#pragma ulimit -s 102400
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <signal.h>

#define PARAM_NONE 0
#define PARAM_a 1
#define PARAM_l 2
#define PARAM_R 32

#define MAXROWLEN 80

int g_leavelen = MAXROWLEN;
int g_maxlen;

void display_dir(int flag_param, char *path);
void my_err(const char *err_string, int line);
void print(char *name);
void display_attribute(struct stat buf, char *name);
void display_single(char *name);
void display_inode(char *name);
void display(int flag, char *pathname);
void display_dir(int flag_param, char *path);
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

    for(i = 1; i < argc;i++) {
        if(argv[i][0] == '-') {
            for(k = 1;k < (int)strlen(argv[i]);k++,j++) {
                param[j] = argv[i][k];
            }
            num++;
        }
    }
    for(i = 0;i < j;i++) {
        if(param[i] == 'a'){
            flag_param |= PARAM_a;
            continue;
        }
        else if(param[i] == 'l'){
            flag_param |= PARAM_l;
            continue;
        }
        else if(param[i] == 'R'){
            flag_param |= PARAM_R;
            continue;
        }
        else{
            printf("my_ls: no avail option -%c\n", param[i]);
            exit(1);
        }
    }
    param[j] = 0;

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
            strcpy(path, argv[i]);
            if(stat(path,&buf) == -1)
                my_err("stat",__LINE__);

            if(S_ISDIR(buf.st_mode)) {
                if(path[strlen(argv[i]) - 1] != '/') {
                    path[strlen(argv[i])]  = '/';
                    path[strlen(argv[i])+1] = 0;
                }
                else {
                    path[strlen(argv[i])] = 0;
                }
                display_dir(flag_param,path);
                i++;
            } else {
                display(flag_param,path);
                i++;
            }
        }
    } while(i < argc);

    return 0;
}
void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d", line);
    perror(err_string);
    if (errno != 13) {
        exit(0);
    } else {
        printf("无权限\n");
    }
}
void print(char *name) {
    printf(" %-s",name);
}

void display_attribute(struct stat buf, char *name) {
    char time_buf[32];
    struct passwd *psd;
    struct group *grp;

    if (S_ISLNK(buf.st_mode)) {
        printf("l");
    } else if (S_ISREG(buf.st_mode)) {
        printf("-");
    } else if (S_ISDIR(buf.st_mode)) {
        printf("d");
    } else if (S_ISCHR(buf.st_mode)) {
        printf("c");
    } else if (S_ISBLK(buf.st_mode)) {
        printf("b");
    } else if (S_ISFIFO(buf.st_mode)) {
        printf("f");
    } else if (S_ISSOCK(buf.st_mode)) {
        printf("s");
    }

    if (buf.st_mode & S_IRUSR)    printf("r");  else printf("-");
    if (buf.st_mode & S_IWUSR)    printf("w");  else printf("-");
    if (buf.st_mode & S_IXUSR)    printf("x");  else printf("-");
    if (buf.st_mode & S_IRGRP)    printf("r");  else printf("-");
    if (buf.st_mode & S_IWGRP)    printf("w");  else printf("-");
    if (buf.st_mode & S_IXGRP)    printf("x");  else printf("-");
    if (buf.st_mode & S_IROTH)    printf("r");  else printf("-");
    if (buf.st_mode & S_IWOTH)    printf("w");  else printf("-");
    if (buf.st_mode & S_IXOTH)    printf("x");  else printf("-");
    
    printf("\t");

    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);

    printf("%4hu ",buf.st_nlink);
    printf("%-8s  ",psd->pw_name);
    printf("%-8s", grp->gr_name);

    printf("%6lld", buf.st_size);
    strcpy(time_buf,ctime(&buf.st_mtime)); // 把时间转换成普通表示格式

    time_buf[strlen(time_buf)-1] = '\0'; // 去掉换行符
    printf("  %s", time_buf);

    print(name);
    printf("\n");
}
void display_single(char *name) {
    int i;
    int len;

    if (g_leavelen < g_maxlen) {
        printf("\n");
        g_leavelen = MAXROWLEN;
    }
    len = strlen(name);
    len = g_maxlen - len;
    print(name);
    for(i = 0;i < len;i++) {
        printf(" ");
    }
    printf(" ");
    g_leavelen -= (g_maxlen + 2);
}

void display_inode(char *name){
    int i;
    int len;
    struct stat buf;
    if(g_leavelen < g_maxlen) {
        printf("\n");
        g_leavelen = MAXROWLEN;
    }
    if(lstat(name,&buf) == -1) {
        my_err("lstat",__LINE__);
    }
    printf("%llu ",buf.st_ino);
    len = strlen(name);
    len  = g_maxlen - len;
    print(name);
    for(i = 0;i < len;i++) {
        printf(" ");
    }
    printf(" ");
    g_leavelen -= (g_maxlen + 2 + 8);
}
void display(int flag, char *pathname) {
    int i;
    int j;
    struct stat buf;
    char name[PATH_MAX + 1];
    int color = 0;
    
    for (i = 0, j = 0; i < (int)strlen(pathname); i++) {
        if (pathname[i] == '/') {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';

    lstat(pathname,&buf);
    
    if (flag & PARAM_R) {  
        flag -= PARAM_R;
    }
    switch (flag) {
        case PARAM_NONE:      
            if(name[0] != '.') { 
                display_single(name);
            }
            break;
        case PARAM_l:         
            if(name[0] != '.') { 
                display_attribute(buf,name);
            }
            break;
        case PARAM_a:          
            display_single(name); 
            break;
        case PARAM_a + PARAM_l:    
            display_attribute(buf,name);
            break;
        default:
            break;
    }
}

void display_dir(int flag_param, char *path) {
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    struct stat buf;
    char **filename;
    unsigned long long  size = 30000;
    
    filename = (char **)malloc(sizeof(char *) * size);
    int t;
    for (t = 0; t < size; ++t) {
        filename[t] = (char *)malloc(sizeof(char *) * size);
    }
    
    long *filetime;
    filetime = (long *)malloc(sizeof(long) * size);
    
    char temp[PATH_MAX];
    long timeTemp;

    dir = opendir(path);
    if(dir == NULL){
        my_err("opendir",__LINE__);
    }
    while((ptr = readdir(dir))!= NULL){
        if(g_maxlen < (int)strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }

    closedir(dir);

    if(count > size) {
        my_err("too many files under this directory",__LINE__);
    }

    int i;
    int j;
    int len = strlen(path);

    dir = opendir(path);

    for(i = 0;i < count;i++) {
        ptr = readdir(dir);
        if(ptr == NULL) {
            my_err("readdir",__LINE__);
        }

        strncpy(filename[i],path,len);
        filename[i][len] = 0;

        strcat(filename[i], ptr->d_name);
        filename[i][len + strlen(ptr->d_name)] = 0;
        lstat(filename[i], &buf);
        filetime[i] = buf.st_mtime;
    }

    closedir(dir);

    for(i = 0;i < count - 1;i++) {
            for(j = 0;j < count - 1 -i;j++) {
                if(strcmp(filename[j],filename[j+1]) > 0) {
                    strcpy(temp,filename[j]);
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }
    }
    

    if(flag_param & PARAM_R)    
        {   
            for(i = 0;i < count;i++) {
                stat(filename[i],&buf);
                if(S_ISDIR(buf.st_mode)) {
                    len = strlen(filename[i]);
                    if((filename[i][len-1] == '.' && filename[i][len-2] == '/') ||
                       (filename[i][len-1] == '.' && filename[i][len-2] == '.' && filename[i][len-3] == '/')) {
                        continue;
                    }
                    printf("\n\n%s:\n",filename[i]);

                    strcat(filename[i],"/"); 
                    display_dir(flag_param,filename[i]); 
                } else {
                    display(flag_param,filename[i]);
                }
            }
        }
    else { 
            for(i = 0;i < count;i++) {
                display(flag_param,filename[i]);
            }
        }
    
    if((flag_param & PARAM_l) == 0) {
        printf("\n");
    }
    for(i = 0;i < 20000;i++) {
        free(filename[i]);
    }
    free(filename);
    free(filetime);
}