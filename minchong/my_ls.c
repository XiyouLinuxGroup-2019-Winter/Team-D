#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<signal.h>
#define PRINMAX 160
int fx[5]={0};
int namemax=0;
int lenth=0;
char path[PATH_MAX+1]={'\0'};
int compare(const void *p1,const void *p2)
{
    return strcmp((char *)p1,(char *)p2);
}
void display(char *,int,int *,char [][PATH_MAX+1]);
void display_dir(int,int,int *,char[][PATH_MAX+1]);
int main(int argc,char **argv)
{
    signal(2,SIG_IGN);
    int i,j,k,lib=0,argcm=argc-1;
    char ch,ARGV[100][PATH_MAX+1]={'\0'};
    struct stat buf;
    if(argcm>100)
    {
        printf("参数过多!\n");
        exit(1);
    }
    for(i=0;i<argcm;i++)
    strcpy(ARGV[i],argv[i+1]);
    for(i=0;i<argcm;i++)
        if(ARGV[i][0]=='-')
        {
            lib++;
            for(j=1;j<strlen(ARGV[i]);j++)
            {
                ch=ARGV[i][j];
                switch(ch)
                {
                    case 'l':fx[0]=1;break;
                    case 'a':fx[1]=1;break;
                    case 'R':fx[2]=1;break;
                    default:printf("参数错误！\n");exit(1);
                }
            }
        }
    if(lib==argcm)
    {
        argcm++;
        strcpy(ARGV[argcm-1],"./");
    }
    for(i=0;i<argcm;i++)
    {
    namemax=0;
    if(ARGV[i][0]=='-')
    continue;
    for(k=0;k<PATH_MAX;k++)
    path[k]='\0';
    strcpy(path,ARGV[i]);
    if(fx[2]==1)
    printf("%s:\n",path);
    if(stat(path,&buf)==-1)
    {
        printf("目标文件不存在！\n");
        exit(1);
    }
    if(S_ISDIR(buf.st_mode))
    {
        k=strlen(path);
        if(path[k-1]!='/')
        {
            path[k]='/';
            path[k+1]='\0';
            k++;
        }
        else 
        path[k]='\0';
        display_dir(k,i,&argcm,ARGV);
    }
    else
    {
        int a;
        char finam[PATH_MAX];
        for(int q=0,a=0;q<strlen(path);q++)
        {
            if(path[q]=='/')
            {
                a=0;
                continue;
            }
            finam[a++]=path[q];
        }
        finam[a]='\0';
        if(fx[0]==0)
        display(path,i,&argcm,ARGV);
        else
        printf("%s",finam);
    }
    printf("\n");
    lenth=0;
  }
}
void display_dir(int len,int num,int *argcm,char ARGV[100][PATH_MAX+1])
{
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
    int count=0,i,lk,ak[256],lo=0,ctr=0,w;
    char filenames[256][PATH_MAX+1]={'\0'};
    dir=opendir(path);
    if(dir==NULL)
    {
    printf("文件打开失败！\n");
    exit(1);
    }
    while((ptr=readdir(dir))!=NULL)
    {
        namemax=(namemax>strlen(ptr->d_name)?namemax:strlen(ptr->d_name));
        count++;
        if(count>256)
        {
            printf("文件数量超载！\n");
            exit(1);
        }
        strncpy(filenames[count-1],path,len);
        filenames[count-1][len]=='\0';
        strcat(filenames[count-1],ptr->d_name);
        filenames[count-1][len+strlen(ptr->d_name)]='\0';
    }
    closedir(dir);
    qsort(filenames[0],count,sizeof(filenames[0]),compare);
    for(i=0;i<count;i++)
    display(filenames[i],num,argcm,ARGV);
}
void display(char *pathname,int num,int *argcm,char ARGV[][PATH_MAX+1])
{
    int i,j,blank=0;
    struct stat buf;
    char name[NAME_MAX+1];
    if(lstat(pathname,&buf)==-1)
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    for(i=0,j=0;i<strlen(pathname);i++)
    {
        if(pathname[i]=='/')
        {
            j=0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]='\0';
    if(fx[1]==0&name[0]=='.')
    return 0;
    if(fx[2]==1)
    {
        if(S_ISDIR(buf.st_mode))
        {
            for(int h=(*argcm)-1;h>num;h--)
            strcpy(ARGV[h+1],ARGV[h]);
            strcpy(ARGV[num+1],pathname);
            (*argcm)++;
        }
    }
    if(fx[0]==0)
    {
        if((PRINMAX-lenth)<(namemax+2))
        {
            lenth=0;
            printf("\n");
        }
        blank=(namemax-strlen(name))+2;
        printf("%s",name);
        for(i=0;i<blank;i++)
        printf(" ");
        lenth+=(namemax+2);
    }
    else
    {
    char buf_time[32];
    struct passwd *psd;
    struct group *grp;
    if(S_ISLNK(buf.st_mode))
    printf("l");
    else if(S_ISREG(buf.st_mode))
    printf("-");
    else if(S_ISDIR(buf.st_mode))
    printf("d");
    else  if(S_ISCHR(buf.st_mode))
    printf("c");
    else if(S_ISBLK(buf.st_mode))
    printf("b");
    else if(S_ISFIFO(buf.st_mode))
    printf("f");
    else if(S_ISSOCK(buf.st_mode))
    printf("s");
    if(buf.st_mode&S_IRUSR)
    printf("r");
    else
    printf("-");
    if(buf.st_mode&S_IWUSR)
    printf("w");
    else
    printf("-");
    if(buf.st_mode&S_IXUSR)
    printf("x");
    else
    printf("-");
    if(buf.st_mode&S_IRGRP)
    printf("r");
    else
    printf("-");
    if(buf.st_mode&S_IWGRP)
    printf("w");
    else
    printf("-");
    if(buf.st_mode&S_IXGRP)
    printf("x");
    else
    printf("-");
    if(buf.st_mode&S_IROTH)
    printf("r");
    else
    printf("-");
    if(buf.st_mode&S_IWOTH)
    printf("w");
    else
    printf("-");
    if(buf.st_mode&S_IXOTH)
    printf("x");
    else
    printf("-");
    printf("   ");
    psd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_gid);
    printf("%4d  ",buf.st_nlink);
    printf("%-8s  ",psd->pw_name);
    printf("%-8s  ",grp->gr_name);
    printf("%6d  ",buf.st_size);
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1]='\0';
    printf("  %s  ",buf_time);
    printf("  %s\n",name);
    }
}
