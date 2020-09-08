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
#define PRINMAX 150
int fx[5]={0};
int namemax=0;
int lenth,lenth_m;
typedef struct arg
{
	char name[1000];
	struct arg *next;
}ARGV;
ARGV *head=NULL;
char path[PATH_MAX+1]={'\0'};
int compare(const void *p1,const void *p2)
{
    return strcmp((char *)p1,(char *)p2);
}
void display(char *,ARGV *);
void display_dir(int,ARGV *);
int main(int argc,char **argv)
{
    signal(2,SIG_IGN);
    int i,j,k,lib=0;
    char ch,finame[1000];
    struct stat buf;
	ARGV *p,*p1,*p3;
	head=p=p1=(ARGV *)malloc(sizeof(ARGV));
	head->next=NULL;
    for(i=0;i<argc-1;i++)
	{
	p1=(ARGV*)malloc(sizeof(ARGV));
	p1->next=NULL;
    strcpy(p1->name,argv[i+1]);
	p->next=p1;
	p=p1;
	}
	p=head;
    for(p=p->next;p!=NULL;p=p->next)
        if(p->name[0]=='-')
        {
            lib++;
            for(j=1;j<strlen(p->name);j++)
            {
                ch=p->name[j];
                switch(ch)
                {
                    case 'l':fx[0]=1;break;
                    case 'a':fx[1]=1;break;
                    case 'R':fx[2]=1;break;
                    default:printf("参数错误！\n");exit(1);
                }
            }
        }
	for(p=head;p->next!=NULL;p=p->next);
    if(lib==argc-1)
    {
	p1=(ARGV*)malloc(sizeof(ARGV));
	p1->next=NULL;
    strcpy(p1->name,"./");
	p->next=p1;
	p=p1;
    }
	p=head;
    for(p=p->next;p!=NULL;p=p->next)
    {
    namemax=0;
    if(p->name[0]=='-')
	{
    head->next=p->next;
	free(p);
	p=head;
    continue;
	}
    for(k=0;k<PATH_MAX;k++)
    path[k]='\0';
    strcpy(path,p->name);
    if(fx[2]==1)
	{
	printf("\n");
    printf("\033[1;32;40m %s:\n\033[0m",path);
	}
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
        display_dir(k,p);
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
        display(path,p);
        else
        printf("%s",finam);
    }
    printf("\n");
    lenth=0;
    head->next=p->next;
	free(p);
	p=head;
  }
}
void display_dir(int len,ARGV * p)
{
    DIR *dir;
	int lent;
    struct dirent *ptr;
    struct stat buf;
    int count=0,i,lk,ak[256],lo=0,ctr=0,w;
	int qw,er;
    char **filenames;
	filenames=(char **)malloc(sizeof(char *)*20000);
	for (int t = 0; t < 20000; t++)
        filenames[t] = (char *)malloc(sizeof(char*) *PATH_MAX);
	for (int t=0;t<20000;t++)
		memset(filenames[t],0,sizeof(filenames[t]));
    dir=opendir(path);
    if(dir==NULL)
    {
    printf("目录打开失败！\n");
    return;
    }
    while((ptr=readdir(dir))!=NULL)
    {
        count++;
        if(count>20000)
        {
            printf("文件数量超载！\n");
            exit(1);
        }
	}
    closedir(dir);
    dir=opendir(path);
    if(dir==NULL)
    {
    printf("目录打开失败！\n");
    return;
    }
	for(i=0;i<count;i++)
	{
		ptr=readdir(dir);
		if(ptr==NULL)
			break;
        strcpy(filenames[i],path);
        filenames[i][len]='\0';
	    for(qw=0,er=len;ptr->d_name[qw]!='\0';qw++,er++)
			filenames[i][er]=ptr->d_name[qw];
        filenames[i][len+qw]='\0';
    }
    closedir(dir);
//    qsort(filenames[0],count,sizeof(filenames[0]),compare);
    for(i=0;i<count;i++)
    display(filenames[i],p);
	 for(int ki = 0;ki < 20000;ki++)
        free(filenames[ki]);
    free(filenames);
}
void display(char *pathname,ARGV *p)
{
    int i,j,blank=0;
    struct stat buf;
    char name[NAME_MAX+1];
	ARGV *p1;
    if(lstat(pathname,&buf)==-1)
    {
		printf("%s    :",pathname);
        printf("文件打开失败！\n");
        return;
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
	       p1=(ARGV*)malloc(sizeof(ARGV));
		   memset(p1,0,sizeof(p1));
	       p1->next=p->next;
           strcpy(p1->name,pathname);
	       p->next=p1;
        }
    }
    if(fx[0]==0)
    {
        printf("%s\n",name);
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
