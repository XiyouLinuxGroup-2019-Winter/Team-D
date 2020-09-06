/*************************************************************************
	> File Name: serve.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2020年07月20日 星期一 19时25分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
typedef struct bag
{
	char send_id[12];
	char recv_id[12];
	char send_nick[24];
	int cate;
	char buf[200];
}DATA;
typedef struct mass
{
	char buff[252];
	int  conn_fd;
	struct mass *next;
}QUEUE;
typedef struct files
{
	int cate;
	char send_id[12];
	char name[40];
	char buff[1004];
}FILES;
MYSQL  mysql;
char exit_str[200];
QUEUE *head_queue=NULL,*last_queue=NULL;
pthread_mutex_t  mutex;
pthread_cond_t cond;
int file_fd[100]={0};
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
#define ERROR(x)  {puts(#x);return -1;}
#define ERROR_INIT(x)  {puts(#x);continue;}
void *judge();
int  login(DATA *p,int con_fd);
int  regiest(DATA *p,int con_fd);
int  changeword(DATA *,int);
int  flist(DATA *,int );
int  fadd(DATA*,int);
int  freque(DATA *,int );
int  send_serve(int,int,char *,char *,char *,char *);
int  chat_check(DATA*,int );
int  chat(DATA *,int);
int  send_init(char *,int);
int  delete(DATA *,int);
void group_chatinit(DATA *,int);
void group_chat(DATA *,int);
void group_add(DATA *,int);
void group_init(DATA *,int);
void group_exit(DATA *,int);
void group_deletes(DATA *,int);
void group_list(DATA *,int);
void group_apply(DATA *,int);
void group_member(DATA *,int);
void deal_error(int);
void messages(DATA *,int);
void file_init(DATA *,int);
void file_send(DATA *,int);
void *send_file(void *);
int file_judge(int);
int epfd;
int main()
{
	int file_d;
	pthread_t thid[4],pid;
	struct epoll_event ev,events[100];
	int nfds,connect_size=0,connfd;
	QUEUE *q_p1;
	head_queue=last_queue=q_p1=(QUEUE *)malloc(sizeof(QUEUE));
	head_queue->next=NULL;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	for(int k=0;k<4;k++)
	pthread_create(&thid[k],NULL,judge,NULL);
	struct sockaddr_in serv_addr,cli_addr;
	 mysql_init(&mysql);
	 mysql_library_init(0,NULL,NULL);
	 if(mysql_real_connect(&mysql,"127.0.0.1","root","20011204","wetalk",0,NULL,0)==NULL)
		 ERROR(mysql connect error!)
	mysql_set_character_set(&mysql,"utf8");
	int sock_fd = socket(AF_INET,SOCK_STREAM,0);		
	int cli_len = sizeof(cli_addr);
	if(sock_fd < 0) 
		ERROR(socket error!)
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(7098);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0) 
		ERROR(bind error!)
	if(listen(sock_fd,100) < 0)
		ERROR(listen error!)
	epfd=epoll_create(1);
	if(epfd==-1)
		ERROR(epoll_create error!)
	ev.data.fd=sock_fd;
	ev.events=EPOLLIN|EPOLLERR|EPOLLHUP|EPOLLRDHUP;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sock_fd,&ev);
	while(1)
	{
		printf("epoll while\n");
		nfds=epoll_wait(epfd,events,1024,-1);
		printf("success nfds %d",nfds);
		for(int i=0;i<nfds;i++)
		{
			if(events[i].data.fd==sock_fd)
			{
				connfd=accept(events[i].data.fd,(struct sockaddr*)&cli_addr,&cli_len);
				if(connfd<=0)
					ERROR_INIT("accept error!")
				ev.data.fd=connfd;
				ev.events=EPOLLIN|EPOLLRDHUP;
				epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
				printf("welcome :%d\n",connfd);
			}
			else if(events[i].events&(EPOLLRDHUP|EPOLLHUP|EPOLLERR))
				deal_error(events[i].data.fd);
			else if(file_judge(events[i].data.fd)==1)
			{   
				file_d=events[i].data.fd;
	            if(pthread_create(&pid,NULL,send_file,(void *)&file_d)!=0)
					close(file_d);
			}
			else if(events[i].events&EPOLLIN)
	    	{
				printf("处理中\n");
				q_p1=(QUEUE *)malloc(sizeof(QUEUE));
				if(q_p1==NULL)
					printf("malloc error!");
				q_p1->next=NULL;
				if(recv(events[i].data.fd,q_p1->buff,sizeof(q_p1->buff),MSG_WAITALL)<0)
				{
					printf("recv error\n");
					free(q_p1);
					q_p1=NULL;
					continue;
				}
				printf("recv 成功\n");
				q_p1->conn_fd=events[i].data.fd;
				pthread_mutex_lock(&mutex);
				last_queue->next=q_p1;
				last_queue=q_p1;
				pthread_cond_signal(&cond);
				printf("唤醒！\n");
				pthread_mutex_unlock(&mutex);
			}
		}
	}
}
void *judge()
{
	printf("创建成功！\n");
	int con_fd,ctr,sum=0;
	QUEUE *key;
	char p1[252];
	char str[200];
	DATA  *p;
	while(1)
	{
		if(head_queue->next==NULL)
		{
			printf("消息为空\n");
		    pthread_cond_wait(&cond,&mutex);
			pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_lock(&mutex);
		printf("唤醒成功\n");
		key=head_queue->next;
		head_queue->next=head_queue->next->next;
		if(head_queue->next==NULL)
			last_queue=head_queue;
		pthread_mutex_unlock(&mutex);
		printf("解锁成功\n");
		con_fd=key->conn_fd;
		p=(DATA *)key->buff;
		printf("cate :%d\n",p->cate);
		switch(p->cate)
		{
			case 0:
				   memset(str,0,sizeof(str));
				   printf("BYE %d\n",con_fd);
				   send_serve(con_fd,0,"\0","\0","\0","\0");
		           sprintf(str,"update user set state=\"%d\" where socket=\"%d\"",0,con_fd);
	               if(mysql_query(&mysql,str)!=0)
		            ERROR(mysql  pw select error!)
					memset(str,0,sizeof(str));
		           sprintf(str,"update user set socket=\"%d\" where socket=\"%d\"",0,con_fd);
	               if(mysql_query(&mysql,str)!=0)
		            ERROR(mysql  pw select error!)
					close(con_fd);
				    break;
			case 1:ctr=login(p,con_fd);
				   break;
			case 2:ctr=regiest(p,con_fd);
				   break;
			case 3:ctr=changeword(p,con_fd);
				   break;
			case 4:ctr=flist(p,con_fd);
				   break;
			case 5:ctr=fadd(p,con_fd);
				   break;
			case 8:ctr=chat_check(p,con_fd);
				   break;
			case 9:ctr=chat(p,con_fd);
				   break;
			case 10:ctr=freque(p,con_fd);
					break;
			case 13:ctr=delete(p,con_fd);
					break;
			case 30:group_chatinit(p,con_fd);break;
			case 38:group_chat(p,con_fd);break;
			case 31:group_add(p,con_fd);break;
			case 32:group_init(p,con_fd);break;
			case 33:group_exit(p,con_fd);break;
			case 35:group_deletes(p,con_fd);break;
			case 36:group_list(p,con_fd);break;
			case 37:group_apply(p,con_fd);break;
			case 39:group_member(p,con_fd);break;
			case 41:messages(p,con_fd);break;
			case 50:file_init(p,con_fd);break;
			case 51:file_send(p,con_fd);break;
			default:memset(p,0,sizeof(struct bag));break;
		}
		p=NULL;
		free(key);
		key=NULL;
		con_fd=-1;
	}
}
int login(DATA *p,int con_fd)
{
	printf("login :%d\n",con_fd);
	puts("修改成功\n");
	DATA buff;
	char str[200];
	memset(&buff,0,sizeof(DATA));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from user where ID=\"%s\"",p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	printf("%s\n",(char *)row[2]);
	if(row==NULL)
		buff.cate=-1;
	else if(strcmp(p->buf,(char *)row[1])!=0)
		buff.cate=-2;
	else if(atoi((char *)row[3])==1)
		buff.cate=-3;
	else
	{
		printf("login 123\n");
		memset(str,0,sizeof(str));
		strcpy(buff.buf,(char *)row[2]);
		sprintf(str,"update user set socket=\"%d\" where ID=\"%s\"",con_fd,p->send_id);
	    if(mysql_query(&mysql,str)!=0)
		  ERROR(mysql  pw select error!)
		memset(str,0,sizeof(str));
		sprintf(str,"update user set state=\"%d\" where ID=\"%s\"",1,p->send_id);
	    if(mysql_query(&mysql,str)!=0)
		  ERROR(mysql  pw select error!)
	}
	if(send(con_fd,(char *)&buff,sizeof(DATA),0)<0)
		ERROR(send error!)
	if(buff.cate==0)
	{
		printf("buff.cate=0,run\n");
		if(send_init(p->send_id,con_fd)==-1)
			return -1;
	}
//	mysql_free_result(result);
	printf("login success\n");
   return 0;
}
int regiest(DATA *p,int con_fd)
{
	printf("regiest :%d\n",con_fd);
	DATA buff;
	char id[12];
	memset(id,0,sizeof(id));
	unsigned int n;
	char str[100],strs[500];
	MYSQL_RES *result;
	if(mysql_query(&mysql,"select *from user")!=0)
		ERROR(mysql nk  select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	n=mysql_num_rows(result);
	sprintf(id,"%010d",n);
	sprintf(str,"insert into user values(\"%s\",NULL,NULL,0,%d)",id,con_fd);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	memset(str,0,sizeof(str));
	sprintf(str,"update user set nickname=\"%s\" where ID=\"%s\"",p->send_nick,id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw1 select error!)
	sprintf(strs,"update user set password=\"%s\" where ID=\"%s\"",p->buf,id);
	if(mysql_query(&mysql,strs)!=0)
		ERROR(mysql  pw select error!)
	memset(&buff,0,sizeof(struct bag));
	strcpy(buff.buf,id);
	if(send(con_fd,(char *)&buff,sizeof(struct bag),0)<0)
			 ERROR(send error!)
	mysql_free_result(result);
	return 0;
}
int changeword(DATA *p,int con_fd)
{
	DATA buff;
	memset(&buff,0,sizeof(DATA));
	char str[500];
	sprintf(str,"update user set password=\"%s\" where ID=\"%s\"",p->buf,p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql   select error!)
	if(send_serve(con_fd,3,"\0","\0","\0","0")==-1)
		return -1;
	return 0;
}
int  flist(DATA *p,int con_fd)
{
	char str[200],str1[200],ch[5];
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from friends  where user_id=\"%s\"",p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while((row=mysql_fetch_row(result))!=NULL)
	{ 
	memset(str1,0,sizeof(str1));
	sprintf(str1,"select *from user  where ID=\"%s\"",(char *)row[0]);
	if(mysql_query(&mysql,str1)!=0)
		ERROR(mysql select error!)
	result1=mysql_store_result(&mysql);
	if(result1==NULL)
		ERROR(user NULL!)
	row1=mysql_fetch_row(result1);
		if(atoi((char *)row1[3])==1)
			ch[0]='1';
		else 
			ch[0]='0';
		ch[1]='\0';
		printf("%s  %s   %s\n",(char*)row[1],(char *)row1[2],ch);
	if(send_serve(con_fd,4,(char *)row[1],(char *)row1[2],"\0",ch)==-1)
		return -1;
	}
	if(send_serve(con_fd,4,"\0","\0","\0","q")==-1)
		return -1;
//	mysql_free_result(result);
//	mysql_free_result(result1);
	return 0;
}
int  fadd(DATA *p,int con_fd)
{
	char str[200],ch[5],str1[200];
	memset(str,0,sizeof(str));
	memset(str1,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from user where ID=\"%s\"",p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	sprintf(str1,"select *from friends where user_id=\"%s\" and friend_id=\"%s\"",p->recv_id,p->send_id);
	if(mysql_query(&mysql,str1)!=0)
		ERROR(mysql select error!)
	result1=mysql_store_result(&mysql);
	if(result1==NULL)
		ERROR(user NULL!)
	row1=mysql_fetch_row(result1);
	if(row==NULL)
		ch[0]='1';
	else if(row1!=NULL)
		ch[0]='2';
	else
		{
			ch[0]='0';
			memset(str,0,sizeof(str));
	        sprintf(str,"insert into massages values(\"%s\",\"%s\",NULL,NULL,\"%d\")",p->send_id,p->recv_id,2);
	        if(mysql_query(&mysql,str)!=0)
		       ERROR(mysql  pw select error!)
			if(atoi((char *)row[3])==0)
			{
			memset(str,0,sizeof(str));
	        sprintf(str,"insert into massages_send values(\"%s\",\"%s\",NULL,NULL,\"%d\")",p->send_id,p->recv_id,2);
	        if(mysql_query(&mysql,str)!=0)
		       ERROR(mysql  pw select error!)
			}
			else
				if(send_serve(atoi((char *)row[4]),10,p->send_id,p->send_nick,p->recv_id,"\0")==-1)
					return -1;
		}
	ch[1]='\0';
	if(send_serve(con_fd,5,"\0","\0","\0",ch)==-1)
		return -1;
//	mysql_free_result(result);
//	mysql_free_result(result1);
	return 0;
}
int send_serve(int con_fd,int type,char *s_id,char *s_nk,char *r_id,char *data)
{
	DATA buff;
	printf("send_serve :%d\n",con_fd);
	memset(&buff,0,sizeof(DATA));
	puts(s_id);
	puts(s_nk);
	puts(r_id);
	puts(data);
	buff.cate=type;
	printf("send_serve: type %d\n",type);
	strcpy(buff.send_id,s_id);
	strcpy(buff.send_nick,s_nk);
	strcpy(buff.recv_id,r_id);
	strcpy(buff.buf,data);
	if(send(con_fd,(char *)&buff,sizeof(DATA),0)<0)
			 ERROR(send error!)
	printf("send_serve success\n");
	return 0;
}
int  freque(DATA *p,int con_fd)
{
	char str[100];
	memset(str,0,sizeof(str));
	printf("%s\n",p->send_id);
	printf("%s\n",p->recv_id);
	sprintf(str,"insert into friends values(\"%s\",\"%s\",\"%d\")",p->send_id,p->recv_id,1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	memset(str,0,sizeof(str));
	sprintf(str,"insert into friends values(\"%s\",\"%s\",\"%d\")",p->recv_id,p->send_id,1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	return 0;
}
int chat_check(DATA *p,int con_fd)
{
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from friends where user_id=\"%s\" and friend_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		send_serve(con_fd,8,"NULL","\0","\0","\0");
	else
	{
	    sprintf(str,"select *from user where ID=\"%s\"",p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	    result=mysql_store_result(&mysql);
	    if(result==NULL)
		ERROR(user NULL!)
	    row=mysql_fetch_row(result);
		if((atoi((char *)row[3]))==1)
		send_serve(con_fd,8,"\0","\0","\0","1");
		else
		send_serve(con_fd,8,"\0","\0","\0","0");
	}
//	mysql_free_result(result);
	return 0;
}
int chat(DATA *p,int con_fd)
{
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"insert into massages values(\"%s\",\"%s\",\"%s\",NULL,\"%d\")",p->send_id,p->recv_id,p->buf,1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	memset(str,0,sizeof(str));
	sprintf(str,"select *from user where ID=\"%s\"",p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if((atoi((char *)row[3]))==0)
	{
	memset(str,0,sizeof(str));
    sprintf(str,"insert into massages_send values(\"%s\",\"%s\",NULL,\"%s\",\"%d\")",p->send_id,p->recv_id,p->buf,1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	}
	else
		send_serve(atoi((char *)row[4]),9,p->send_id,p->send_nick,p->recv_id,p->buf);
//	mysql_free_result(result);
    return 0;
}
int send_init(char *ID,int con_fd)
{
	printf("send_init run\n");
	char str[200],ch1[10],ch2[10],ch3[10],str1[200];
	int num[4];
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from massages_send where recv_id=\"%s\" and type=\"%d\"",ID,1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	num[0]=mysql_num_rows(result);
	memset(str,0,sizeof(str));
	sprintf(str,"select *from massages_send where recv_id=\"%s\" and type=\"%d\" or type=\"%d\"",ID,2,4);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	num[1]=mysql_num_rows(result);
	memset(str,0,sizeof(str));
	sprintf(str,"select *from massages_send where recv_id=\"%s\" and type=\"%d\"",ID,3);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	num[2]=mysql_num_rows(result);
	sprintf(ch1,"%d",num[0]);
	sprintf(ch2,"%d",num[1]);
	sprintf(ch3,"%d",num[2]);
	ch1[strlen(ch1)]='\0';
	ch2[strlen(ch2)]='\0';
	ch3[strlen(ch3)]='\0';
	send_serve(con_fd,20,ch1,ch2,ch3,"\0");
	memset(str,0,sizeof(str));
	sprintf(str,"select *from massages_send where recv_id=\"%s\"",ID);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while((row=mysql_fetch_row(result))!=NULL)
	{
		printf("发消息\n");
		memset(str1,0,sizeof(str1));
	    sprintf(str1,"select *from user where ID=\"%s\"",(char *)row[0]);
	   if(mysql_query(&mysql,str1)!=0)
		ERROR(mysql select error!)
	   result1=mysql_store_result(&mysql);
	   if(result1==NULL)
		ERROR(user NULL!)
		row1=mysql_fetch_row(result1);
	   if(atoi((char *)row[4])!=4)
	   {
	   if((char *)row[3]==NULL)
		send_serve(con_fd,(atoi((char*)row[4]))+8,(char *)row[0],(char *)row1[2],(char *)row[1],"\0");
	   else
		if(send_serve(con_fd,(atoi((char*)row[4]))+8,(char *)row[0],(char *)row1[2],(char *)row[1],(char *)row[3])==-1)
			return -1;
	   }
	   else
		   send_serve(con_fd,37,(char *)row[0],(char *)row1[2],(char *)row[1],(char *)row[3]);
	}
	send_serve(con_fd,10,"NULL","\0","\0","\0");
	memset(str,0,sizeof(str));
	sprintf(str,"delete from massages_send where recv_id=\"%s\"",ID);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	printf("send_init 1\n");
//	mysql_free_result(result);
//	mysql_free_result(result1);
	printf("send_init success\n");
	return 0;
}
int delete(DATA *p,int con_fd)
{	
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from friends where user_id=\"%s\" and friend_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		send_serve(con_fd,13,"NULL","\0","\0","\0");
	else
	{
		memset(str,0,sizeof(str));
	    sprintf(str,"delete from friends where user_id=\"%s\" and friend_id=\"%s\"",p->send_id,p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
		memset(str,0,sizeof(str));
	    sprintf(str,"delete from friends where user_id=\"%s\" and friend_id=\"%s\"",p->recv_id,p->send_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
		send_serve(con_fd,13,"\0","\0","\0","\0");
	}
	return 0;
}
void deal_error(int con_fd)
{
char str[200];
memset(str,0,sizeof(str));
printf("BYE %d\n",con_fd);
send_serve(con_fd,0,"\0","\0","\0","\0");
sprintf(str,"update user set state=\"%d\" where socket=\"%d\"",0,con_fd);
if(mysql_query(&mysql,str)!=0)
ERROR(mysql  pw select error!)
memset(str,0,sizeof(str));
sprintf(str,"update user set socket=\"%d\" where socket=\"%d\"",0,con_fd);
if(mysql_query(&mysql,str)!=0)
ERROR(mysql  pw select error!)
close(con_fd);
}				
void group_chatinit(DATA *p,int con_fd)
{
	char str[200],str1[10]={'\0'};
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		strcpy(str1,"NULL");
	send_serve(con_fd,30,str1,"\0","\0","\0");
}
void group_chat(DATA *p,int con_fd)
{
	char str[200],str1[200];
	int i,k;
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"insert into massages values(\"%s\",NULL,\"%s\",\"%s\",\"%d\")",p->send_id,p->buf,p->recv_id,3);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	memset(str,0,sizeof(str));
	sprintf(str,"select *from group_member where  group_id=\"%s\"",p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while(row=mysql_fetch_row(result))
	{
		if(strcmp((char *)row[0],p->send_id)==0)
			continue;
		memset(str1,0,sizeof(str1));
	    sprintf(str1,"select *from user where  ID=\"%s\"",(char *)row[0]);
	    if(mysql_query(&mysql,str1)!=0)
		   ERROR(mysql select error!)
	    result1=mysql_store_result(&mysql);
	    if(result1==NULL)
		   ERROR(user NULL!)
		row1=mysql_fetch_row(result1);
		if(atoi((char *)row1[3])==0)
		{
		     memset(str1,0,sizeof(str1));
	         sprintf(str1,"insert into massages_send values(\"%s\",\"%s\",\"%s\",\"%s\",\"%d\")",p->send_id,(char *)row1[0],p->recv_id,p->buf,3);
	         if(mysql_query(&mysql,str1)!=0)
		          ERROR(mysql select error!)
		}
		else
		{
			memset(str,0,sizeof(str));
			strcpy(str,p->buf);
			send_serve(atoi((char *)row1[4]),38,p->recv_id,p->send_nick,(char *)row1[0],str);
		}
	}
}
void group_add(DATA *p,int con_fd)
{
	char str[200],str1[10]={'\0'},str2[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1,*result2;
	MYSQL_ROW *row,*row1,*row2;
	sprintf(str,"select *from group_we where ID=\"%s\"",p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result1=mysql_store_result(&mysql);
	if(result1==NULL)
		ERROR(user NULL!)
	row1=mysql_fetch_row(result1);
	if(row1==NULL)
		str1[0]='1';
	else
	{
		memset(str,0,sizeof(str));
	sprintf(str,"select *from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row!=NULL)
		str1[0]='2';
	else
	{  
		str1[0]='0';
		memset(str,0,sizeof(str));
	    sprintf(str,"select *from group_member where status=\"%d\" or status=\"%d\"",2,3);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while(row=mysql_fetch_row(result))
	{
		memset(str2,0,sizeof(str2));
		sprintf(str2,"select *from user where ID=\"%s\"",(char *)row[0]);
	if(mysql_query(&mysql,str2)!=0)
		ERROR(mysql select error!)
	result2=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
		row2=mysql_fetch_row(result2);
	  if(atoi((char *)row2[3])==0)
	  {
		  memset(str,0,sizeof(str));
	         sprintf(str,"insert into massages_send values(\"%s\",\"%s\",\"%s\",\"%s\",\"%d\")",p->send_id,p->send_nick,(char *)row2[0],p->recv_id,4);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	  }
	  else
		  send_serve(atoi((char *)row2[4]),37,p->recv_id,row1[1],p->send_id,p->send_nick);
	}
	}
	}
	str1[1]='\0';
	send_serve(con_fd,31,"\0","\0",p->send_id,str1);
}
void group_init(DATA *p,int con_fd)
{
	int n;
	char id[12],str[200];
	MYSQL_RES *result;
	if(mysql_query(&mysql,"select *from group_we")!=0)
		ERROR(mysql nk  select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	n=mysql_num_rows(result);
	sprintf(id,"%010d",n);
	id[0]='1';
	id[1]='1';
	id[3]='1';
	sprintf(str,"insert into group_we values(\"%s\",\"%s\",\"%s\")",id,p->buf,p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	memset(str,0,sizeof(str));
	sprintf(str,"insert into group_member values(\"%s\",\"%s\",\"%s\",\"%s\",\"%d\")",p->send_id,p->send_nick,id,p->buf,3);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	send_serve(con_fd,32,id,"\0","\0","\0");
}
void group_apply(DATA *p,int con_fd)
{
	printf("group_apply init\n");
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
	{
	memset(str,0,sizeof(str));
	sprintf(str,"select *from group_we where ID=\"%s\"",p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	memset(str,0,sizeof(str));
	sprintf(str,"insert into group_member values(\"%s\",\"%s\",\"%s\",\"%s\",\"%d\")",p->send_id,p->send_nick,p->recv_id,(char *)row[1],1);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	printf("group_apply success\n");
	}
}
void group_exit(DATA *p,int con_fd)
{
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		send_serve(con_fd,33,"NULL","\0","\0","\0");
	else if(atoi((char *)row[4])==3)
		send_serve(con_fd,33,"owner","\0","\0","\0");
	else
	{
		memset(str,0,sizeof(str));
		sprintf(str,"delete from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
		send_serve(con_fd,33,"\0","\0","\0","\0");
	}
}
void group_deletes(DATA *p,int con_fd)
{
	char str[200];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from group_we where ID=\"%s\" and owner=\"%s\"",p->recv_id,p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		send_serve(con_fd,35,"NULL","\0","\0","\0");
	else
	{
		memset(str,0,sizeof(str));
		sprintf(str,"delete from group_we where ID=\"%s\"",p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
		memset(str,0,sizeof(str));
		sprintf(str,"delete from group_member where group_id=\"%s\"",p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
		send_serve(con_fd,35,"\0","\0","\0","\0");
	}
}
void group_list(DATA *p,int con_fd)
{
	char str[200],chk[5];
	memset(str,0,sizeof(str));
	MYSQL_RES *result;
	MYSQL_ROW *row;
	sprintf(str,"select *from group_member where ID=\"%s\"",p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while(row=mysql_fetch_row(result))
	{
		if(atoi((char *)row[4])==1)
			chk[0]='1';
		else if(atoi((char *)row[4])==2)
			chk[0]='2';
		else
			chk[0]='3';
		chk[1]='\0';
		send_serve(con_fd,36,(char *)row[2],(char *)row[3],chk,"\0");
	}
	send_serve(con_fd,36,"\0","\0","\0","q");
}
void group_member(DATA *p,int con_fd)
{
	char str[200],chk[5],ck[5];
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from group_member where ID=\"%s\" and group_id=\"%s\"",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==0)
		send_serve(con_fd,39,"NULL","\0","\0","\0");
	else
	{
		send_serve(con_fd,39,"\0","\0","\0","\0");
		memset(str,0,sizeof(str));
	    sprintf(str,"select *from group_member where  group_id=\"%s\"",p->recv_id);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
	    result=mysql_store_result(&mysql);
	    if(result==NULL)
		    ERROR(user NULL!)
	    while(row=mysql_fetch_row(result))
		{
		if(atoi((char *)row[4])==1)
			chk[0]='1';
		else if(atoi((char *)row[4])==2)
			chk[0]='2';
		else
			chk[0]='3';
		chk[1]='\0';
		memset(str,0,sizeof(str));
	    sprintf(str,"select *from user where ID=\"%s\"",(char *)row[0]);
	    if(mysql_query(&mysql,str)!=0)
		    ERROR(mysql select error!)
	    result1=mysql_store_result(&mysql);
	    if(result1==NULL)
		    ERROR(user NULL!)
		row1=mysql_fetch_row(result1);
		if(atoi((char *)row[3])==0)
			ck[0]='0';
		else
			ck[0]='1';
		ck[1]='\0';
		send_serve(con_fd,40,(char *)row[0],(char *)row[1],chk,ck);
		}
		send_serve(con_fd,40,"\0","\0","\0","q");
	}
}
void messages(DATA *p,int con_fd)
{
	char str[200],chk[5],ck[5];
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from messages where send_id=\"%s\" or send_id=\"%s\" and recv_id=\"%s\" or recv_id=\"%s\"",p->send_id,p->recv_id,p->recv_id,p->send_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	while(row=mysql_fetch_row(result))
	{
		memset(str,0,sizeof(str));
		sprintf(str,"select *from user where ID=\"%s\"",(char *)row[0]);
	    if(mysql_query(&mysql,str)!=0)
		   ERROR(mysql select error!)
	    result1=mysql_store_result(&mysql);
	    if(result1==NULL)
		    ERROR(user NULL!)
	    row1=mysql_fetch_row(result1);
		send_serve(con_fd,41,(char *)row[0],(char *)row1[2],"\0",(char *)row[2]);
	}
	send_serve(con_fd,41,"NULL","\0","\0","\0");
}
void file_init(DATA *p,int con_fd)
{
	char str[200],chk[5],ck[5];
	memset(str,0,sizeof(str));
	MYSQL_RES *result,*result1;
	MYSQL_ROW *row,*row1;
	sprintf(str,"select *from friends where user_id=\"%s\"  and friend_id=\"%s\" ",p->send_id,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql select error!)
	result=mysql_store_result(&mysql);
	if(result==NULL)
		ERROR(user NULL!)
	row=mysql_fetch_row(result);
	if(row==NULL)
		send_serve(con_fd,50,"NULL","\0","\0","\0");
	else
		send_serve(con_fd,50,"\0","\0","\0","\0");
}
void file_send(DATA *p,int con_fd)
{
	int num,i;
	FILE *fp;
	struct epoll_event evp;
	char str[200];
	MYSQL_RES *result;
	MYSQL_ROW *row;
	for( i=0;i<100;i++) 
		if(file_fd[i]==0)
			break;
	if(i==100)
	{
		printf("i=100\n");
		send_serve(con_fd,51,"error","\0","\0","\0");
		close(con_fd);
		return;
	}
	file_fd[i]=con_fd;
	printf("fiel _send :%s   %s\n",p->send_id,p->buf);
	if(mkdir(p->send_id,S_IRWXU)==-1)
	{
		printf("创建目录失败\n");
		send_serve(con_fd,51,"error","\0","\0","\0");
		close(con_fd);
		return;
	}
	sprintf(str,"insert into file_send values(\"%s\",\"%s\",\"%s\",\"%s\")",p->buf,p->send_id,p->send_nick,p->recv_id);
	if(mysql_query(&mysql,str)!=0)
		ERROR(mysql  pw select error!)
	send_serve(con_fd,51,"\0","\0","\0","\0");
}
void *send_file(void *c_fd)
{
	int con_fd=*(int *)c_fd;
	FILES *p;
	FILE *fp;
	char buf[1060],path;
	printf("文件接受中\n");
	if(recv(con_fd,buf,sizeof(buf),0)<0)
		ERROR(recv error!)
	p=(FILES *)buf;
	if(p->cate=1)
	{
		close(con_fd);
		for(int i=0;i<100;i++)
			if(file_fd[i]==con_fd)
				file_fd[i]=0;
		return;
	}
	sprintf(path,"%s/%s",p->send_id,p->name);
	fp=fopen(path,"a+");
	if(fp==NULL)
		printf("打开文件失败！\n");
	fwrite(p->buff,1,1000,fp);
	pthread_exit(0);
}
int  file_judge(int c_fd)
{
	int i;
	for(i=0;i<100;i++)
		if(file_fd[i]==c_fd)
			return 1;
 return 0;
}
