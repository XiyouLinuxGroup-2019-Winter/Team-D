#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "unistd.h"
#include <fcntl.h>
#include<sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define nomo 0
#define BACKG 1
#define out_redirect  2
#define in_redirect 3
#define PIPE 4
#define out_redirect_apend  5

void get_inpt(char *buf);
int divide(char *buf, char store[][256]);
void do_cmd(char store[255][256], int cnt);
int find_cmd(char *cmd);
void cd( int cnt, char arg[255][256]);


char pre_path[256];

int main(int argc, char **argv)
{		
//	setbuf(stdout,NULL);
	signal(SIGINT,SIG_IGN);
	int cnt = 0;
	char store[100][256];
	char *buf = malloc(sizeof(256));
	if(buf == NULL)	
		exit(1);
	
	getcwd(pre_path, 256);
	
	read_history(NULL);	//~/.history
	while (1) {
		memset(buf, 0, 256);
		get_inpt(buf);
		if (strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") == 0) {
			break;
		}
		if(strcmp(buf,"\n") == 0)   
				continue;  
		for (int i = 0; i < 100; i++) {
			store[i][0] = 0;
		}

		cnt = divide(buf, store);		
		do_cmd(store, cnt);

	}
	
	if (buf != NULL) {
		free(buf);
		buf = NULL;
	}	
		
		return 0;
}
void get_inpt(char *buf)
{	
	char *str;
	char cur[256];
	getcwd(cur, 256);
	printf("%s", cur);
	str = readline(" myshell$$ ");
	strcpy(buf, str);
	add_history(buf);
	buf[strlen(buf)] = '\n';
	write_history(NULL);
	free(str);
}

int divide(char *buf, char store[][256])
{
	int cnt = 0;
	int n = 0;
	char *pre = buf;
	char *tail = buf;
	
	while (1) {
		if(pre[0] == '\n') break;
		if(pre[0] == ' ')	pre++;
		else {
			tail = pre; 
			n = 0;
			while(tail[0] != ' ' && tail[0] != '\n')	n++, tail++;
			strncpy(store[cnt], pre, n + 1);
			store[cnt++][n] = '\0';
			pre = tail;
		}
	}
	
	return cnt;
}

void do_cmd(char store[100][256], int cnt)
{
	int flag = 0 ;
	int how = 0;
	int backg = 0;
	int status  = 0;
	int fd;
	char *arg[cnt + 1];
	char *file = NULL;
	pid_t pid;
	int cnt_pipe = 0;
	char *argnext[cnt + 1];
		
	for (int i = 0; i < cnt; i++) {
		arg[i] = (char *)store[i];
	}
	arg[cnt] = NULL;
	
	if(strcmp("cd", arg[0]) == 0){
		 cd(cnt, store);
		return ;
	}
	
	for(int i = 0; i < cnt; i++) {
		if(strcmp(arg[i], "&") == 0)	{
				if(i != cnt - 1)	{
					perror("syntax error\n");
						return ;
				}
				else {
					backg = 1;
					arg[cnt - 1] = NULL;
					break;
				}
		}
	}	
		for (int i = 0; i < cnt; i++) {
			if (strcmp(arg[i],  ">") == 0) {
					flag++;
					how = out_redirect;
					if(arg[i + 1] == NULL)	flag++;		
			}
				
			if (strcmp(arg[i],  ">>") == 0){
				flag++;
				how = out_redirect_apend;
				if(arg[i + 1] == NULL)	flag++;
			}
			
			if (strcmp(arg[i],  "<") == 0){
				flag++;
				how = in_redirect;
				if(i == 0)	flag++;
			}

			if (strcmp(arg[i],  "|") == 0){
				flag++;
				cnt_pipe++;
				how = PIPE;
				if(i == 0)	flag++;	
			}
		}	
			if(flag > 1 && cnt_pipe == 0){
				perror("wrong cmd\n");
				return ;
			}

			if(how == in_redirect){
				for (int i = 0; arg[i] != NULL; i++) {
					if(strcmp("<", arg[i]) == 0)	file = arg[i + 1], arg[i] = NULL;
				}
			}
			
			if (how == out_redirect_apend) {
				for (int i = 0; arg[i] != NULL; i++) {
					if (strcmp(">>",  arg[i]) == 0)  file = arg[i + 1], arg[i] = NULL;
				}
			}
			
			if (how == out_redirect) {
				for (int i = 0; arg[i] != NULL; i++) {
					if (strcmp(">",  arg[i]) == 0)	 file = arg[i + 1], arg[i] = NULL; 	
				}
			}			
//			if (how == PIPE) {
//					for(int i = 0; i < cnt; i++){
//					int k = 0 ;
//					int j;
//					if(arg[i][0] == '|') {
//					arg[i] = NULL;	 
//					for(j = i + 1; arg[j] != NULL; j++)	{
//							argnext[k++] = arg[j];
//					}
//					argnext[k] = NULL;
//				}
//			}
//		}
			if((pid = fork()) < 0){
				perror("fork():\n");
				exit(1);
			}
			
			switch (how) {
				case nomo:	if(pid == 0){
					if(find_cmd(arg[0]) == 0){
							printf("%s command not found!\n",arg[0]);
							return ;
						}
						
						execvp(arg[0],  arg);
						exit(0);
					}
					break;
				case in_redirect:	
					if(pid == 0){
								if(find_cmd(arg[0]) == 0){
									printf("%s command not found!\n",arg[0]);
									return ;
								}
									fd = open(file, O_RDONLY);
									dup2(fd, 0);
									execvp(arg[0], arg);
									exit(0);
								}
						break;
				case out_redirect:	
						if (pid == 0) {
							if (find_cmd(arg[0]) == 0) {
								printf("%s command not found!\n",arg[0]);
								return ;
							}
							if((fd = open(file, O_WRONLY)) < 0){
								printf("open failed\n");
								exit(-1);
							}
							
							dup2(fd, 1);
							execvp(arg[0], arg);
							exit(0);
						}
						break;
				case out_redirect_apend:	
						if(pid == 0){
							if(find_cmd(arg[0]) == 0){
								printf("%s command not found!\n",arg[0]);
								return ;
						}
							fd = open(file, O_APPEND);
							dup2(fd, 1);
							execvp(arg[0], arg);
							exit(0);
						}
						break;
				case PIPE:
					if(pid == 0)
					{	
						pid_t pid2;
						int status2;
						int fd2;
						if((pid2 = fork()) < 0){
								printf("fork error!\n");
								return;
							}
						else if(pid2 == 0)
						{	
							if(find_cmd(arg[0]) == 0)
								{
									printf("fork 2 error\n");
									return ;
								}
							fd2 = open("/tmp/here", O_WRONLY|O_CREAT|O_TRUNC,0644);
							dup2(fd2, 1);
							execvp(arg[0],arg);
							exit(0);
						}
							if(waitpid(pid2,&status2,0) == -1){
								printf("wait for child process error!\n");
								exit(0);
							}
					
							if(find_cmd(argnext[0]) == 0)
							{
								printf("cmd not found\n");
								exit(1);
							}
							fd2 = open("/tmp/here", O_RDONLY);
							dup2(fd2, 0);
							execvp(argnext[0], argnext);
							if(remove("/tmp/here"))	
								printf("remv err\n");
							exit(0);	
					}
//					if(pid == 0){
//						pid_t p_temp;
//						int stat;
//						int j;
//						char buf[255];
//						for (int i = 0; i < cnt; i++) {
//							argnext[i] =  store[i];
//						}
//						
//						for (int i = 1; i <= cnt_pipe; i++) {
//							
//							if((p_temp = fork()) == 0 ){
//								fd = open("/tmp/here", O_WRONLY|O_CREAT|O_TRUNC, 0644);
//								if(fd < 0){
//									perror("open failed \n");
//									exit(1);
//								}
//								j = 0;
//								for(; strcmp(argnext[j], "|") != 0; j++){
//										arg[j] = argnext[j];	
//								}
//								arg[j] = NULL;
//								if(i != 1){
//									arg[j++] = buf;
//									arg[j] = NULL;
//								}
//								for (int k = 0; j < cnt + 1; k++, j++) {
//									argnext[k] = argnext[j];
//								}
//								dup2(fd, 1);
//								execv(arg[0], arg);
//								exit(0);
//							}
//							
//							if(waitpid(p_temp,  &stat, 0) == -1){
//								printf("wait error\n");
//								exit(1);
//							}
//							fd = open("/tmp/here", O_RDONLY);
//							read(fd, buf, 256);
//							if(remove("/tmp/here"))	printf("remv err\n");
//						}
//					}
				
					break;
				default: break;
			}	

			if(backg == 1){
				printf("process id is %d\n", pid);
				return ;
			}
			printf("%d\n", pid);
			if(waitpid(pid, &status, 0) == -1)
				perror("wait cid error:\n");	
	}

int find_cmd(char *cmd)
{
	DIR *fd;
	struct dirent *stat;
	char *path[] = {"/bin", "/usr/bin", NULL};
	
	if (strncmp(cmd, "./", 2) == 0) {
		cmd += 2;
	}
	int i = 0;
	while(path[i] != NULL){
		if ((fd = opendir(path[i])) == NULL) {
			printf("cant open\n");
	}
	while((stat = readdir(fd)) != NULL) {
			if (strcmp(cmd, stat->d_name) == 0) {
				closedir(fd);
				return 1;
			}
		}
		i++;
		closedir(fd);
	}
	return 0;
}

void cd( int cnt, char arg[100][256])
{	
	char cur[256];
	getcwd(cur, 256);
	
	if(cnt == 2 && strcmp(arg[1], "-") == 0)	chdir(pre_path), strcpy(pre_path, cur);
	if(cnt == 1 || strcmp(arg[1], "~") == 0)	chdir("/User/admin");
	else chdir(arg[1]);
}