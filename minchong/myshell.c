#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<readline/readline.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#define ERROR(x)  {puts(#x);exit(1);}
void get_input(char *);
int find(char *); 
void explain_input(char *,int *,char [100][256]);
void do_cmd(int,char [100][256]);
int main()
{
	signal(2,SIG_IGN);
	int i,argcount=0;
	char arglist[100][256];
	char *buf=NULL;
	char **arg=NULL;
	buf=(char *)malloc(256);
	if(buf==NULL)
	{
		printf("malloc error\n");
		exit(-1);
	}
	while(1)
	{
		memset(buf,0,sizeof(buf));
		printf("myshell$$ ");
		get_input(buf);
		if(strcmp(buf,"exit")==0)
			break;
		for(i=0;i<100;i++)
			memset(arglist[i],0,sizeof(arglist[i]));
		argcount=0;
		explain_input(buf,&argcount,arglist);
		do_cmd(argcount,arglist);
	}
		if(buf!=NULL)
			free(buf);
		buf=NULL;
	exit(0);
}
void get_input(char *buf)
{
	int len=0,ch;
	ch=getchar();
	while(len<256&&ch!='\n')
	{
		buf[len++]=ch;
		ch=getchar();
	}
	if(len==256)
	ERROR(command is too long!)
	buf[len]='\0';
}
void explain_input(char *buf,int *argcount,char arglist[100][256])
{
	int i,k=0,m=0,l=0;
	char *p=buf,*q=buf;
	while(1)
	{
		if(p[0]=='\0')
			break;
		if(p[0]==' ')
			p++;
		else
		{
			q=p;
			m=0;
			while((q[0]!=' ')&&(q[0])!='\0')
			{
				m++;
				q++;
			}
			strncpy(arglist[*argcount],p,m+1);
			arglist[*argcount][m]='\0';
			*argcount=*argcount+1;
			p=q;
		}
	}
}
void do_cmd(int argcount,char arglist[100][256])
{
	int modl=0,background=0;
	int i,flag=0,status2;
	pid_t pid;
	char *arg[argcount+1],*argnext[argcount+1],*file;
	if(strcmp(arglist[0],"cd")==0)
	{
		chdir(arglist[1]);
		return 0;
	}
	for(i=0;i<argcount;i++)
		arg[i]=(char *)arglist[i];
	arg[argcount]=NULL;
	for(i=0;i<argcount;i++)
	{
		if(strncmp(arg[i],"&",1)==0)
		{
			if(i=argcount-1)
			{
				background=1;
				arg[argcount-1]=NULL;
				break;
			}
			else
				ERROR(wrong command!)
		}
	}
	for(i=0;arg[i]!=NULL;i++)
	{
		if(strcmp(arg[i],">")==0)
		{
			flag++;
			modl=1;
			if(arg[i+1]==NULL)
				flag++;
		}
		if(strcmp(arg[i],"<")==0)
		{
			flag++;
			modl=2;
			if(i==0)
				flag++;
		}
		if(strcmp(arg[i],"|")==0)
		{
			flag++;
			modl=3;
			if(arg[i+1]==NULL)
				flag++;
			if(i==0)
				flag++;
		}
	}
	if(flag>1)
	{
		printf("参数错误\n");
		return;
	}
	if(modl==1)
	{
		for(i=0;arg[i]!=NULL;i++)
		{
			if(strcmp(arg[i],">")==0)
			{
				file=arg[i+1];
				arg[i]=NULL;
			}
		}
	}
	if(modl==2)
	{
		for(i=0;arg[i]!=NULL;i++)
		{
			if(strcmp(arg[i],"<")==0)
			{
				file=arg[i+1];
				arg[i]=NULL;
			}
		}
	}
	if(modl==3)
	{
		int j;
		for(i=0;arg[i]!=NULL;i++)
		{
			if(strcmp(arg[i],"|")==0)
			{
				arg[i]=NULL;
				for(j=i+1;arg[j]!=NULL;j++)
					argnext[j-i-1]=arg[j];
				argnext[j-i-1]=arg[j];
				break;
			}
		}
	}
	if((pid=fork())<0)
		ERROR(fork error!)
	switch(modl)
	{
		int fd;
		case 0:if(pid==0)
		       {
		       if(find(arg[0])==0)
			   {
				   printf("404 NOT FOUND!\n");
				   exit(0);
			   }
		       execvp(arg[0],arg);
		       exit(0);
		       }
		       break;
		case 1:if(pid==0)
		       {
		       if(find(arg[0])==0)
			   {
				   printf("404 NOT FOUND!\n");
				   exit(0);
			   }
		       fd=open(file,O_WRONLY|O_CREAT,0644);
		       dup2(fd,STDOUT_FILENO);
		       execvp(arg[0],arg);
		       exit(0);
		       }
		       break;
		case 2:if(pid==0)
		       {
			   int  fd1=STDIN_FILENO;
		       if(find(arg[0])==0)
			   {
				   printf("404 NOT FOUND!\n");
				   break;
			   }
		       fd=open(file,O_RDONLY);
		       dup2(fd,STDIN_FILENO);
		       execvp(arg[0],arg);
		       exit(0);
		       }
		       break;
	        case 3:if(pid==0)
		       {
		       int pid2,status2,fd2;
		       if((pid2=fork())<0)
		       ERROR(fork2  error!)
		       else if(pid2==0)
		       {
		       if(find(arg[0])==0)
			   {
				   printf("404 NOT FOUND!\n");
				   break;
			   }
		       fd2=open("/tmp/youdonotknowfile",O_WRONLY|O_CREAT|O_TRUNC,0644);
		       dup2(fd2,1);
		       execvp(arg[0],arg);
		       exit(0);
		       }
		       if(waitpid(pid2,&status2,0)==-1)
		       ERROR(wait for chid process error!)
		       if(find(argnext[0])==0)
			   {
				   printf("404 NOT FOUND!\n");
				   break;
			   }
		       fd2=open("/tmp/youdonotknowfile",O_RDONLY);
		       dup2(fd2,0);
		       execvp(argnext[0],argnext);
		       if(remove("/tmp/youdonotknowfile"))
		       printf("remove error!\n");
		       exit(0);
		       }
		       break;
	       default:break;

	}
	if(background==1)
		return;
	if(waitpid(pid,&status2,0)==-1)
	ERROR(wait child process error!)
}
int find(char *command)
{
	DIR *dp;
	int i=0;
	struct dirent *dirp;
	char *path[]={"./","/bin","/usr/bin",NULL};
	if(strncmp(command,"./",2)==0)
		command=command+2;
	while(path[i]!=NULL)
	{
		if((dp=opendir(path[i]))==NULL)
		ERROR(can not open /bin)
		while((dirp=readdir(dp))!=NULL)
		{
			if(strcmp(dirp->d_name,command)==0)
			{
				closedir(dp);
				return 1;
			}
		}
		closedir(dp);
		i++;
	}
	return 0;
}
