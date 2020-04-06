#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<dirent.h>
#include<limits.h>

#define MAXROWLEN 80

void err(const char *err_string,int line)
{
	printf("error :%d",line);
	perror(err_string);
	exit(1);
}

void gain(char *path,char *name)
{
	int i,j;
	for(i=0,j=0;i<strlen(path);i++){
		if(path[i]=='/'){
			j=0;
			continue;
		}
		name[j++]=path[i];
	}
	name[j]='\0';
}
void display_l(struct stat buf,char *name)
{
	char buf_time[32];
	struct passwd *psd;//获取文件所有者的用户名
	struct group *grp;//获取文件所有者所属的组名
	//打印文件类型
	if(S_ISLNK(buf.st_mode)){
		printf("1");
	}else if(S_ISREG(buf.st_mode)){
		printf("-");
	}else if(S_ISDIR(buf.st_mode)){
		printf("d");
	}else if(S_ISCHR(buf.st_mode)){
		printf("c");
	}else if(S_ISBLK(buf.st_mode)){
		printf("b");
	}else if(S_ISFIFO(buf.st_mode)){
		printf("f");
	}else if(S_ISSOCK(buf.st_mode)){
		printf("s");
	}
	//打印文件所有者权限
	if(buf.st_mode&S_IRUSR){
		printf("r");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IWUSR){
		printf("w");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IXUSR){
		printf("x");
	}else {
		printf("-");
	}
	//打印同组其他用户对该文件的操作权限
	if(buf.st_mode&S_IRGRP){
		printf("r");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IWGRP){
		printf("w");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IXGRP){
		printf("x");
	}else {
		printf("-");
	}
	//打印其他用户对该文件操作权限
	if(buf.st_mode&S_IROTH){
		printf("r");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IWOTH){
		printf("w");
	}else {
		printf("-");
	}
	if(buf.st_mode&S_IXOTH){
		printf("x");
	}else {
		printf("-");
	}

	printf(" ");

	//根据uid和gid获取文件所有者的用户名和组名
	psd=getpwuid(buf.st_uid);
	grp=getgrgid(buf.st_gid);
	printf("%5ld ",buf.st_nlink);//打印文件链接数
	printf("%-8s",psd->pw_name);
	printf("%-8s",grp->gr_name);

	printf("%6ld",buf.st_size);//打印文件大小
	strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1]='\0';//删除换行符
	printf("%s",buf_time);//打印时间信息
}

void display(int flag,char *pathname)
{
	void display_R(int flag,char *path);
	int i,j;
	struct stat buf;
	char name[260];

	if(lstat(pathname,&buf)==-1){
		err("stat",__LINE__);
	}

	gain(pathname,name);

	switch(flag){
		case 1:
			if(name[0]!='.'){
				printf("%-6s",name);
			}
			break;
		case 3:
			{
				printf("%-6s",name);
			}
			break;
		case 5:
			if(name[0]!='.'){
				display_l(buf,name);
				printf(" %-s\n",name);
			}
			break;
		case 7:
			display_l(buf,name);
			printf(" %-s\n",name);
			break;
		case 9:
			display_R(flag,pathname);
			break;
		case 11:
			printf(". ..\n");
			display_R(flag,pathname);
			break;
		case 13:
			display_l(buf,name);
			printf(" ");
			display_R(flag,pathname);
			break;
		case 15:
			display_l(buf,".");
			printf(" .\n");
			display_l(buf,"..");
			printf(" ..\n");
			display_R(flag,pathname);
			break;
		default:
			break;
	}
}

void display_R(int flag,char *path)
{

    struct stat buf;
    struct stat buff;
    DIR *dir;
    struct dirent *ptr;
    char allname[256][260],name[256][260],a[260],b[260];
    int i,j,k,len,count;

    if(lstat(path,&buf) == -1){
        if(errno==13){
            return ;
        }
        else{
            printf("error di:  %s\n",path);
            return ;
        }
    }

    if(S_ISDIR(buf.st_mode)){
        printf("\n%s\n",path);
        count=0;
        dir=opendir(path);
        if(dir == NULL){
            err("display_R",__LINE__);
        }
        i=0;
        while((ptr = readdir(dir))!=NULL){
            len=0;
            count++;
            strncpy(allname[i],path,strlen(path));
            allname[i][strlen(path)]='/';
            allname[i][strlen(path)+1]='\0';
            strncat(allname[i],ptr->d_name,strlen(ptr->d_name));
            allname[i][strlen(allname[i])]='\0';
            i++;
        }
        for(i=0;i<count;i++)
            gain(allname[i],name[i]);

        for(i=0;i<count;i++){
            if(name[i][0] != '.'){
                if(lstat(allname[i],&buff) == -1){
                    printf("error242");
                }
                if(S_ISDIR(buff.st_mode)){
                       char *m=(char *)malloc(strlen(allname[i])*sizeof(char));
                        display_R(flag,m);
                        free(m);
                   }
                else{
                    if(flag > 11){
                        display_l(buff,allname[i]);
                    }
                    printf("  %s\n",name[i]);
                }
            }
            else{
                printf("\n");
                continue;
            }
        }

    }
    else {
        gain(path,a);
        if(a[0] != '.'){
            if(flag > 11){
                display_l(buff,allname[i]);
            }
            printf("  %-s\n",a);
        }
    }
}

void display_dir(int flag_param,char *path)
{
	void gain(char *path,char *name);
	DIR *dir;
	struct dirent *ptr;
	int count=0;
	char filenames[256][260],temp[PATH_MAX],fullname[256][260],name[256][260];
	int i=0,j,k,len;

	dir=opendir(path);
	if(dir==NULL){
		err("opendir",__LINE__);
	}
	while((ptr=readdir(dir))!=NULL){
		len=0;
		count++;
		strcpy(filenames[i],ptr->d_name);
		len=strlen(ptr->d_name);
		filenames[i][len]='\0';
		i++;
	}
	closedir(dir);

	if(count>256)
		err("too many files under this dir",__LINE__);

	for(i=0;i<count-1;i++){
		for(j=0;j<count-1;j++){
			if(strcmp(filenames[j],filenames[j+1])>0){
				strcpy(temp,filenames[j]);
				strcpy(filenames[j],filenames[j+1]);
				strcpy(filenames[j+1],temp);
			}
		}
        for(i=0;i<count;i++){
            strncat(fullname[i],path,strlen(path));
            fullname[i][strlen(path)]='/';
            fullname[i][strlen(path)+1]='\0';
            strncat(fullname[i],filenames[i],strlen(filenames[i]));
            fullname[i][strlen(fullname[i])]='\0';

        }
        for(i=0;i<count;i++){
            gain(fullname[i],name[i]);
        }


        for(i=0;i<count;i++){
            if(flag_param == 9 || flag_param == 11 || flag_param == 15 || flag_param == 13){
                int flag=1;
                if(name[i][0] == '.'){
		              flag=0;
                }
                if(flag == 1){
                      display(flag_param,fullname[i]);
				}
            }   
            else
            display(flag_param,fullname[i]);
            printf("\n");
		}
	}
}

int mian (int argc,char **argv)
{
	int i,j,k;
	char path[260];
	char param[32];
	int flag_param=1;
	struct stat buf;

	j=0;
	for(i=0;i<argc;i++){
		if(argv[i][0]=='-'){
			for(k=i;k<strlen(argv[i]);k++,j++){
				param[j]=argv[i][k];
			}
		}
	}

	for(i=0;i<j;i++){
		if(param[i]=='a'){
			flag_param+=2;
		}else if(param[i]=='l'){
			flag_param+=4;
		}else if(param[i]=='R'){
			flag_param+=8;
		}else {
			printf("my_ls: invalid option -%c\n",param[i]);
			exit(1);
		}
	}
	param[j]='\0';

	if(argc==1){
		strcpy(path,".");
		display_dir(flag_param,path);
		return 0;
	}else if(argc==2){
		if(flag_param==1){
			strcpy(path,argv[1]);
		}else {
			strcpy(path,".");
		}
	}else if(argc==3){
		strcpy(path,argv[2]);
	}

	if(stat(path,&buf)==-1){
		err("it does not exist",__LINE__);
	}
	if(S_ISDIR(buf.st_mode)){
		display_dir(flag_param,path);
	}else {
		display(flag_param,path);
	}
	return 0;
}
