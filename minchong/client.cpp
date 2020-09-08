/*************************************************************************
	> File Name: serve.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2020年07月18日 星期六 14时15分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include <time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <queue>
using namespace std;
typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];     
}MD5_CTX;
 
                         
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
          { \
          a += F(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define GG(a,b,c,d,x,s,ac) \
          { \
          a += G(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define HH(a,b,c,d,x,s,ac) \
          { \
          a += H(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define II(a,b,c,d,x,s,ac) \
          { \
          a += I(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }                                            
void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen);
void MD5Final(MD5_CTX *context,unsigned char digest[16]);
void MD5Transform(unsigned int state[4],unsigned char block[64]);
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len);
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len);
typedef  struct bag
{
	char send_id[12];
	char recv_id[12];
	char send_nick[24];
	int cate;
	char buf[200];
}DATA;
typedef struct fmes
{
	char g_id[12];
	char g_nk[24];
	char se_id[12];
	char se_nk[24];
	int type;
	char message[200];
}FMES;
typedef struct frequest
{
	int type;
	char g_id[12];
	char g_nk[24];
	char se_id[12];
	char se_nk[24];
}FREQ;
typedef struct friends
{
	int status;
	char friend_id[12];
	char friend_nick[24];
	int  state;
}FRIEND;
typedef struct group
{
	char g_id[12];
	char g_nk[24];
	int  status;
}GROUP;
typedef struct files
{
	int cate;
	char send_id[12];
	char name[40];
	char buff[1004];
}FILES;
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
#define ERROR(x)  {puts(#x);exit(1);}
#define PORT  7098
#define ADDRA 192.168.42.21
int sock_fd;
struct sockaddr_in serv_addr;
char id[12],nickname[21],f_id[12],g_id[12],file_id[12];
DATA recv_data;
pthread_t  pth_recv;
pthread_mutex_t mute;
queue<FMES> head_fmes;
queue<FREQ> head_freq;
queue<FRIEND> head_friend;
queue<GROUP> head_group;
queue<FRIEND> head_member;
queue<FMES> head_message;
int chat_stat=0;
int lock=1,lock_user=1;
void scan(int ,char *);
void init();
void send_init(int ,char *,char *,char *,char *);
void login();
void cexit();
void registe();
void *user_recv(void *);
void changeword();
void fadd();
void freque();
void flist();
void chat();
void lmes();
void user();
void deletes();
void group_chat();
void group_add();
void group_init();
void group_exit();
void group_root();
void group_deletes();
void group_list();
void group_apply();
void group_member();
void messages();
void file_send();
void *send_file(void *);
int main()
{
	int n;
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd < 0)
		ERROR(socket error!)
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_aton("ADDRA",&serv_addr.sin_addr);
	n=connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
	if(n < 0) 
	ERROR(connect error！)
	char ctr,ch;
	while(1)
	{
	init();
	while(1)
	{
		scan(1,&ctr);
		if(ctr=='0'||ctr=='1'||ctr=='2')
		break;
		printf("请输入正确选项：");
	}
	switch(ctr)
		{
			case '1':login();
					 break;
			case '2':registe();
					 break;
			case '0':cexit();
					 printf("3秒后退出！\n");
					 sleep(3);
					 close(sock_fd);ERROR(BYE!)
					 break;
		}
	}
}
void scan(int n,char *str)
{
	int i,ch;
	for(i=0;i<n;i++)
	{
		ch=getchar();
		if(ch=='\n')
		break;
		str[i]=ch;
	}
	str[i]='\0';
	if(ch!='\n')
		while(getchar()!='\n');
}
int set_disp_mode(int fd,int option)
{
   int err;
   struct termios term;
   if(tcgetattr(fd,&term)==-1){
     perror("Cannot get the attribution of the terminal");
     return 1;
   }
   if(option)
        term.c_lflag|=ECHOFLAGS;
   else
        term.c_lflag &=~ECHOFLAGS;
   err=tcsetattr(fd,TCSAFLUSH,&term);
   if(err==-1 && err==EINTR){
        perror("Cannot set the attribution of the terminal");
        return 1;
   }
   return 0;
}
void init()
{
	system("clear");
	printf(" ——————————————Welcome to wetalk———————————————————\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|               1)登陆                             |\n");
	printf("|               2)注册                             |\n");
	printf("|               0)退出                             |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf("|                                                  |\n");
	printf(" ——————————————Welcome to wetalk———————————————————\n");
    printf("请选择：");
}
void send_init(int ctr,char *s_id,char *s_nk,char *r_id,char *datas)
{
	DATA buff;
	memset(&buff,0,sizeof(DATA));
	buff.cate=ctr;
	strcpy(buff.send_id,s_id);
	strcpy(buff.send_nick,s_nk);
	strcpy(buff.recv_id,r_id);
	strcpy(buff.buf,datas);
	if(send(sock_fd,(char *)&buff,sizeof(DATA),0)<0)
		ERROR(send error!)
}
void login()
{
	     memset(id,0,sizeof(id));
		 memset(nickname,0,sizeof(nickname));
	     char password[12],ch,ctr,p1[252];
	     DATA buff,*p;
	     char  passmd5c[300],passmd5[130];
	     MD5_CTX md5;
	     int n;
	     MD5Init(&md5);
	     printf("请输入账号：\n");
		 scan(10,id);
		 printf("请输入密码：\n");
		 set_disp_mode(STDIN_FILENO,0);
		 scan(10,password);
		 set_disp_mode(STDIN_FILENO,1);
		 MD5Update(&md5,(unsigned char *)password,strlen(password));
		 MD5Final(&md5,(unsigned char *)passmd5);
		 n=strlen(passmd5);
		 for(int i=0;i<n;i++)
			 sprintf((passmd5c+2*i),"%02x",passmd5[i]);
		 send_init(1,id,"\0","\0",passmd5c);
	     if(recv(sock_fd,p1,sizeof(DATA),0)<0)
			 ERROR(recv error!)
		p=(DATA *)p1;
		 if(p->cate==-1)
		 {
			 printf("账号错误！\n");
			 printf("按回车键退出!\n");
			 scan(1,&ch);
		 }
		 else if(p->cate==-2)
		 {
			 printf("密码错误！\n");
			 printf("按回车键退出!\n");
			 scan(1,&ch);
		 }
		 else if(p->cate==-3)
		 {
			 printf("账号已登录！\n");
			 printf("按回车键退出！\n");
			 scan(1,&ch);
		 }
		else
		{
			strcpy(nickname,p->buf);
			user();
		}
		return;
}
void user()
{
	pthread_mutex_init(&mute,NULL);
	if(pthread_create(&pth_recv,NULL,user_recv,NULL)==-1)
		ERROR(pthread error!)
	while(lock_user);
	printf("欢迎回来！离线期间共有%d条好友消息，%d条好友请求，%d条群消息！快去消息盒子中查看吧！\n",atoi(recv_data.send_id),atoi(recv_data.send_nick),atoi(recv_data.recv_id));
	while(1)
	{
	char ctr=0;
	printf(" ——————————————————————欢迎回来———————————————————\n");
	printf("|                                                  |\n");
	printf("|               1)修改密码                         |\n");
	printf("|               2)加好友                           |\n");
	printf("|               3)删除好友                         |\n");
	printf("|               4)处理请求                         |\n");
	printf("|               5)显示好友列表                     |\n");
	printf("|               6)私聊                             |\n");
	printf("|               7)查看消息                         |\n");
	printf("|               8)群聊                             |\n");
	printf("|               9)加群                             |\n");
	printf("|               a)创建群聊                         |\n");
	printf("|               b)退群                             |\n");
	printf("|               c)设置管理员                       |\n");
	printf("|               d)解散群                           |\n");
	printf("|               e)查看我加入的群聊                 |\n");
	printf("|               f)发送文件                         |\n");
	printf("|               g)查看群成员                       |\n");
	printf("|               h)查看聊天记录                     |\n");
	printf("|               0)退出                             |\n");
	printf("|                                                  |\n");
	printf(" ——————————————————————欢迎回来———————————————————\n");
    printf("请选择：");
		scan(1,&ctr);
		while(1)
		{
			if(ctr>='0'&&ctr<='9'||ctr>='a'&&ctr<='h')
				break;
			scan(1,&ctr);
		}
		switch(ctr)
		{
			case '1':changeword();break;
			case '2':fadd();break;
			case '3':deletes();break;
			case '4':freque();break;
			case '5':flist();break;
			case '6':chat();break;
			case '7':lmes();break;
			case '8':group_chat();break;
			case '9':group_add();break;
			case 'a':group_init();break;
			case 'b':group_exit();break;
			case 'c':group_root();break;
			case 'd':group_deletes();break;
			case 'e':group_list();break;
			case 'f':file_send();break;
			case 'g':group_member();break;
			case 'h':messages();break;
			case '0':return;
	    }
	system("clear");
	}
}
void registe()
{
	DATA  buff,*p;
	char nicknames[21],password[12],password1[12],passmd5c[300],ch[11],key,p1[252],passmd5[130];
	MD5_CTX md5;
	int n;
	MD5Init(&md5);
	printf("请输入昵称：\n");
	scan(20,nicknames);
	while(1)
	{
	printf("请输入密码(7-10位)：\n");
	set_disp_mode(STDIN_FILENO,0);
	scan(10,password);
	set_disp_mode(STDIN_FILENO,1);
	printf("请再次输入密码：\n");
	set_disp_mode(STDIN_FILENO,0);
	scan(10,password1);
	set_disp_mode(STDIN_FILENO,1);
	if(strcmp(password,password1)==0)
	{
		 MD5Update(&md5,(unsigned char *)password,strlen(password));
		 MD5Final(&md5,(unsigned char *)passmd5);
		 n=strlen(passmd5);
		 for(int i=0;i<n;i++)
			 sprintf((passmd5c+2*i),"%02x",passmd5[i]);
		 send_init(2,"0",nicknames,"0",passmd5c);
	     if(recv(sock_fd,p1,sizeof(p1),0)<0)
			 ERROR(recv error!)
		break;
	}
	else
		printf("两次输入密码不一致，请重新输入！\n");
	}
	p=(DATA *)p1;
	printf("注册成功！您的账号为：\n");
	p->buf[10]='\0';
	puts(p->buf);
	printf("按任意键返回！");
	scan(1,&key);
}
void cexit()
{
	send_init(0,id,nickname,"\0","\0");
}
void * user_recv(void *)
{
	DATA *p;
	FMES p_fmes,p_message;
	FREQ p_freq;
	FRIEND p_friend,p_member;
	GROUP p_group;
	char p1[252];
	while(1)
	{   pthread_mutex_lock(&mute);
	     if(recv(sock_fd,p1,sizeof(p1),MSG_WAITALL)<0)
			 ERROR(recv error!)
		 p=(DATA *)p1;
		 switch(p->cate)
		 {
			 case 3:
			 case 5:
			 case 8:
			 case 13:
			 case 20:
			 case 30:
			 case 31:
			 case 32:
			 case 33:
			 case 34:
			 case 50:
			 case 35:
			 case 39:
					memset(&recv_data,0,sizeof(DATA));
					recv_data.cate=p->cate;
					strcpy(recv_data.send_id,p->send_id);
					strcpy(recv_data.send_nick,p->send_nick);
					strcpy(recv_data.recv_id,p->recv_id);
					strcpy(recv_data.buf,p->buf);
					break;
			 case 4:
					if(p->buf[0]=='q')
					{
						lock=0;
						break;
					}
					memset(&p_friend,0,sizeof(FRIEND));
					strcpy(p_friend.friend_id,p->send_id);
					strcpy(p_friend.friend_nick,p->send_nick);
					printf("p->buf : %c\n",p->buf[0]);
					if(p->buf[0]=='0')
						p_friend.state=0;
					else
						p_friend.state=1;
					head_friend.push(p_friend);
					break;
			 case 9:
				    if(chat_stat==1&&strcmp(p->send_id,f_id)==0)
					{
						printf("\t\t\t\t\t%s:\n",p->send_nick);
						printf("\t\t\t\t\t%s\n",p->buf);
					}
					else
					{
					memset(&p_fmes,0,sizeof(FMES));
					strcpy(p_fmes.se_id,p->send_id);
					strcpy(p_fmes.se_nk,p->send_nick);
					strcpy(p_fmes.message,p->buf);
					p_fmes.type=1;
					head_fmes.push(p_fmes);
					printf("有一条新的好友消息！\n");
					}
					break;
		    case 10:
					if(strcmp(p->send_id,"NULL")==0)
						lock_user=0;
					else
					{
					memset(&p_freq,0,sizeof(FREQ));
					strcpy(p_freq.se_id,p->send_id);
					strcpy(p_freq.se_nk,p->send_nick);
					p_freq.type=1;
					head_freq.push(p_freq);
					printf("有一条新的好友请求！\n");
					}
					break;
			case 38:
				    if(chat_stat==2&&strcmp(p->send_id,g_id)==0)
						printf("\t\t\t\t\t%s:%s\n",p->send_nick,p->buf);
					else
					{
					int k,i;
					memset(&p_fmes,0,sizeof(FMES));
					strcpy(p_fmes.g_id,p->send_id);
					strcpy(p_fmes.se_nk,p->send_nick);
					strcpy(p_fmes.message,p->buf);
					p_fmes.type=2;
					head_fmes.push(p_fmes);
					printf("有一条新的群消息！\n");
					}
					break;
			case 36:
					if(p->buf[0]=='q')
					{
						lock=0;
						break;
					}
					memset(&p_group,0,sizeof(GROUP));
					strcpy(p_group.g_id,p->send_id);
					strcpy(p_group.g_nk,p->send_nick);
					if(p->recv_id[0]=='1')
						p_group.status=1;
					else if(p->recv_id[0]=='2')
						p_group.status=2;
					else
						p_group.status=3;
					head_group.push(p_group);
					break;
			case 37:
					memset(&p_freq,0,sizeof(FREQ));
					strcpy(p_freq.g_id,p->send_id);
					strcpy(p_freq.g_nk,p->send_nick);
					strcpy(p_freq.se_id,p->recv_id);
					strcpy(p_freq.se_nk,p->buf);
					p_freq.type=2;
					head_freq.push(p_freq);
					printf("有一条新的群聊请求\n");
					break;
			case 40:
					if(p->buf[0]=='q')
					{
						lock=0;
						break;
					}
					memset(&p_member,0,sizeof(FRIEND));
					strcpy(p_member.friend_id,p->send_id);
					strcpy(p_member.friend_nick,p->send_nick);
					if(p->buf[0]=='0')
						p_member.state=0;
					else
						p_member.state=1;
					if(p->recv_id[0]=='1')
						p_member.status=1;
					else if(p->recv_id[0]=='2')
						p_member.status=2;
					else
						p_member.status=3;
					head_member.push(p_member);
					break;
			case 41:if(strcmp(p->send_id,"NULL")==0)
					{
						lock=0;
						break;
					}
					memset(&p_message,0,sizeof(FMES));
					strcpy(p_message.se_id,p->send_id);
					strcpy(p_message.se_nk,p->send_nick);
					strcpy(p_message.message,p->buf);
					head_message.push(p_message);
					break;
			case 0:pthread_exit(0);
			default :continue;break;
		 }
		 pthread_mutex_unlock(&mute);
		 sleep(0.01);
	}
}
void changeword()
{

	system("clear");
	char password[12],ch,ctr,password1[11],passmd5c[300];
     char passmd5[130];
	MD5_CTX md5;
	int n;
	MD5Init(&md5);
	while(1)
	{
	printf("请输入新密码(7-10位)：\n");
	set_disp_mode(STDIN_FILENO,0);
	scan(10,password);
	set_disp_mode(STDIN_FILENO,1);
	printf("请再次输入密码：\n");
	set_disp_mode(STDIN_FILENO,0);
	scan(10,password1);
	set_disp_mode(STDIN_FILENO,1);
	if(strcmp(password,password1)==0)
	{
		 MD5Update(&md5,(unsigned char *)password,strlen(password));
		 MD5Final(&md5,(unsigned char *)passmd5);
		 n=strlen(passmd5);
		 for(int i=0;i<n;i++)
			 sprintf((passmd5c+2*i),"%02x",passmd5[i]);
		 send_init(3,id,nickname,"\0",passmd5c);
		 pthread_mutex_lock(&mute);
		 pthread_mutex_unlock(&mute);
		 if(recv_data.cate==-1)
		 {
			 printf("修改失败！\n");
			 continue;
		 }
		break;
	}
	else
		printf("两次输入密码不一致!\n");
	}
	printf("修改成功！一秒后自动退出！\n");
	sleep(1);
}
void flist()
{
	system("clear");
	char ch;
	FRIEND  get_friend;
	send_init(4,id,nickname,"\0","\0");
	while(lock);
	lock=1;
	if(head_friend.empty())
		printf("您还没有好友，快去添加吧！\n");
	else
		while(!head_friend.empty())
		{
			memset(&get_friend,0,sizeof(FRIEND));
			get_friend=head_friend.front();
			printf("%s   \t     %s\t   ",get_friend.friend_id,get_friend.friend_nick);
			if(get_friend.state==0)
				printf("离线  \n");
			else
				printf("在线  \n");
			head_friend.pop();
		}
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void fadd()
{
	system("clear");
	char fid[12];
	printf("请输入要搜索的好友账号:\n");
	scan(10,fid);
	send_init(5,id,nickname,fid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(recv_data.buf[0]=='1')
		printf("未找到用户，请核实账号信息！\n");
	else if(recv_data.buf[0]=='2')
		printf("你们已经是好友了！\n");
	else
		printf("好友请求以发送成功，等待对方处理！\n");
}
void chat()
{
	chat_stat=1;
	char p1[200];
	system("clear");
	printf("请输入要私聊的好友账号：\n");
	scan(10,f_id);
	send_init(8,id,nickname,f_id,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("你们还不是好友，无法进行聊天！\n");
	else
	{
		system("clear");
		if(recv_data.buf[0]=='1')
		printf("与好友%s对话中，输入$quit离开\n\n",recv_data.send_nick);
		else
			printf("好友%s离线中，可发送离线消息，输入$quit离开\n\n",recv_data.send_nick);
		while(1)
		{
			//printf("%s:\n",id);
			memset(p1,0,sizeof(p1));
			scan(180,p1);
			if(strcmp(p1,"$quit")==0)
				break;
			send_init(9,id,nickname,f_id,p1);
		}
	}
	chat_stat=0;
	printf("BYE\n");
}
void lmes()
{
	char ch;
	system("clear");
	FMES get_fmes;
	if(head_fmes.empty())
		printf("无好友消息！\n");
	else
		while(!head_fmes.empty())
		{
			memset(&get_fmes,0,sizeof(FMES));
			get_fmes=head_fmes.front();
			if(get_fmes.type==1)
			{
				printf("(好友)%s:\n",get_fmes.se_nk);
				printf("%s\n",get_fmes.message);
			}
			else
			{
				printf("(群聊)%s————%s:\n",get_fmes.g_id,get_fmes.se_nk);
				printf("%s\n",get_fmes.message);
			}
			head_fmes.pop();
		}
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void freque()
{
	char str[12],ch;
	FREQ get_freq;
	if(head_freq.empty())
		printf("无好友请求！\n");
	else
		while(!head_freq.empty())
		{
			memset(&get_freq,0,sizeof(FREQ));
			get_freq=head_freq.front();
			if(get_freq.type==1)
			{
		         printf("ID为%s,昵称为%s的用户发来好友请求，是否同意（请输入y or n）？\n",get_freq.se_id,get_freq.se_nk);
				 memset(str,0,sizeof(str));
		         strcpy(str,get_freq.se_id);
		         while(1)
	 	         {
			         scan(1,&ch);
			         if(ch=='y'||ch=='n')
				         break;
			         else
				         printf("请输入正确选项！\n");
		         }
		         if(ch=='y')
			         send_init(10,id,nickname,str,"\0");
			}
			else
			{
		         printf("ID为%s,昵称为%s的用户申请加入ID为%s,名称为%s的群聊，是否同意（请输入y or n）？\n",get_freq.se_id,get_freq.se_nk,get_freq.g_id,get_freq.g_nk);
				 memset(str,0,sizeof(str));
				 strcpy(str,get_freq.g_id);
		         while(1)
	 	         {
			         scan(1,&ch);
			         if(ch=='y'||ch=='n')
				         break;
			         else
				         printf("请输入正确选项！\n");
		         }
		         if(ch=='y')
			             send_init(37,get_freq.se_id,get_freq.se_nk,str,"\0");
			}
			head_freq.pop();
		}
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void deletes()
{
	char fid[12],ch;
	system("clear");
	printf("请输入要删除的好友账号：\n");
	scan(10,fid);
	send_init(13,id,nickname,fid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("你们还不是好友！\n");
	else
		printf("删除成功！\n");
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_chat()
{
	char p1[200];
	system("clear");
	printf("请输入群账号：\n");
	scan(10,g_id);
	send_init(30,id,nickname,g_id,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("您还不是本群成员，无法进行聊天！\n");
	else
	{
	    chat_stat=2;
		system("clear");
		printf("与%s群好友聊天中，输入$quit离开\n\n",recv_data.send_nick);
		while(1)
		{
			printf("%s:\n",id);
			memset(p1,0,sizeof(p1));
			scan(180,p1);
			if(strcmp(p1,"$quit")==0)
				break;
			send_init(38,id,nickname,g_id,p1);
		}
	}
	chat_stat=0;
	printf("BYE\n");
}
void group_add()
{
	char gid[12],ch;
	system("clear");
	printf("请输入要加入的群账号：\n");
	scan(10,gid);
	send_init(31,id,nickname,gid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(recv_data.buf[0]=='1')
		printf("未找到信息，请核实账号！\n");
	else if(recv_data.buf[0]=='2')
		printf("您已经是群成员！\n");
	else
		printf("申请已发送成功，等待管理员处理！\n");
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_init()
{
	char g_nk[24],ch;
	system("clear");
	printf("请输入要创建的群名称：\n");
	scan(20,g_nk);
	send_init(32,id,nickname,"\0",g_nk);
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("创建失败\n");
	else
		printf("创建成功，您的群账号为：%s\n",recv_data.send_id);
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_exit()
{
	char gid[12],ch;
	system("clear");
	printf("请输入您要退出的群聊账号：\n");
	scan(10,gid);
	send_init(33,id,nickname,gid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("您还不是本群成员\n");
	else if(strcmp(recv_data.send_id,"owner")==0)
		printf("您是群主无法退出\n");
	else
		printf("退群成功\n");
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_root()
{
	char gid[12],fid[12],ch;
	system("clear");
	printf("请输入群账号：\n");
	scan(10,gid);
	printf("请输入要添加的管理员账号：\n");
	scan(10,fid);
	send_init(34,id,nickname,gid,fid);
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(recv_data.buf[0]=='1')
		printf("您不是本群群主，无权设置管理员！\n");
	else if(recv_data.buf[0]=='2')
		printf("该用户不是群成员，无法成为管理员！\n");
	else
		printf("设置成功！\n");
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_deletes()
{
	char gid[12],ch;
	system("clear");
	printf("请输入要解散的群账号：\n");
	scan(10,gid);
	send_init(35,id,nickname,gid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("您不是本群群主，无权解散！\n");
	else
		printf("解散成功！\n");
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_list()
{
	system("clear");
	char ch;
	printf("group_list init\n");
	GROUP  get_group;
	send_init(36,id,nickname,"\0","\0");
	while(lock);
	lock=1;
	if(head_group.empty())
		printf("您还没有加入群聊，快去加入吧！\n");
	else
		while(!head_group.empty())
		{
			memset(&get_group,0,sizeof(GROUP));
			printf("群账号：%s\t   群名称：%s\t  我的身份：",get_group.g_id,get_group.g_nk);
			if(get_group.status==1)
				printf("普通成员\n");
			else if(get_group.status==2)
				printf("管理员\n");
			else
				printf("群主\n");
			head_group.pop();
		}
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void group_member()
{
	system("clear");
	char gid[12],ch;
	FRIEND  get_member;
	printf("请输入要查看的群聊账号：\n");
	scan(10,gid);
	send_init(39,id,nickname,gid,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("您还不是此群的成员！\n");
	else
	{
	   while(lock);
	   lock=1;
	   if(head_member.empty())
		   printf("error!\n");
	   else
		   while(!head_member.empty())
		   {
			   memset(&get_member,0,sizeof(FRIEND));
			   get_member=head_member.front();
			   printf("%s\t   %s\t   ",get_member.friend_id,get_member.friend_nick);
			   if(get_member.state==0)
				   printf("离线\t");
			   else
				   printf("在线\t");
			   if(get_member.status==1)
				   printf("普通成员\n");
			   else if(get_member.status==2)
				   printf("管理员\n");
			   else
				   printf("群主\n");
			   head_member.pop();
		   }
	}
	printf("按回车键退出！\n");
	scan(1,&ch);
}
void messages()
{
	system("clear");
	char fid[12],ch;
	FMES get_message;
	printf("请输入要查看的好友账号：\n");
	scan(10,fid);
	send_init(41,id,nickname,fid,"\0");
	while(lock);
	lock=1;
	if(head_message.empty())
		printf("你们之间没有聊天记录！\n");
	else
	{
	while(!head_message.empty())
	{
		memset(&get_message,0,sizeof(FMES));
		get_message=head_message.front();
		printf("%s  :  %s\n",get_message.se_nk,get_message.message);
		head_message.pop();
	}
	}
	printf("按回车键退出\n");
	scan(1,&ch);
}
void file_send()
{
	system("clear");
	struct stat key;
	void *st;
	int i,j;
	char file[410],ch;
	printf("请输入接受方的账号！\n");
	scan(10,file_id);
	send_init(50,id,nickname,file_id,"\0");
	pthread_mutex_lock(&mute);
	pthread_mutex_unlock(&mute);
	if(strcmp(recv_data.send_id,"NULL")==0)
		printf("你们还不是好友，无法发送文件！\n");
	else
	{
	printf("请输入要发送的文件路径与文件名：\n");
	scan(400,file);
	if(lstat(file,&key)==-1)
		printf("文件不存在！\n");
	else
	{
	pthread_t  pthd;
	if(pthread_create(&pthd,NULL,send_file,(void *)file)==-1)
		ERROR(pthread error!)
	printf("文件发送中！\n");
	}
	}
	printf("按回车键返回！\n");
	scan(1,&ch);
}
void *send_file(void * files)
{
	printf("send_file init\n");
	char *file=(char *)files;
	printf("%s\n",file);
	int n,sock_file,i,k;
	char fname[38],buf[252];
	DATA *p;
	FILE *fp;
	FILES f_data;
	fp=fopen(file,"r");
	if(fp==NULL)
	{
		printf("打开文件出错！\n");
		pthread_exit(0);
	}
	for(i=0,k=0;i<strlen(file);i++)
    {
		if(k==37)
			break;
        if(file[i]=='/')
        {
            k=0;
            continue;
        }
        fname[k++]=file[i];
    }
    fname[k]='\0';
	puts(fname);
    struct sockaddr_in serv_file;
	sock_file = socket(AF_INET,SOCK_STREAM,0);
	if(sock_file < 0)
		ERROR(socket error!)
	memset(&serv_file,0,sizeof(struct sockaddr_in));
	serv_file.sin_family = AF_INET;
	serv_file.sin_port = htons(PORT);
	inet_aton("ADDRA",&serv_file.sin_addr);
	n=connect(sock_file,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
	if(n < 0) 
	ERROR(connect error！)
	send_init(51,id,nickname,file_id,fname);
	if(recv(sock_file,buf,sizeof(buf),0)<0)
		ERROR(recv error!)
	p=(DATA*)buf;
	if(strcmp(p->send_id,"error")==0)
		printf("文件发送失败\n");
	else
	{
	    memset(&f_data,0,sizeof(FILES));
		printf("开始发送\n");
		while(fread(f_data.buff,1,1000,fp)==0)
		{
			strcpy(f_data.send_id,id);
			strcpy(f_data.name,fname);
			f_data.cate=0;
			f_data.buff[1001]='\0';
			puts(f_data.buff);
	        if(send(sock_file,(char *)&f_data,sizeof(FILES),0)<0)
		         ERROR(send error!)
			memset(&f_data,0,sizeof(FILES));
		}
		f_data.buff[strlen(f_data.buff)]='\0';
		strcpy(f_data.send_id,id);
		strcpy(f_data.name,fname);
		f_data.cate=0;
		puts(f_data.buff);
	    if(send(sock_file,(char *)&f_data,sizeof(FILES),0)<0)
		    ERROR(send error!)
		memset(&f_data,0,sizeof(FILES));
		f_data.cate=1;
	if(send(sock_file,(char *)&f_data,sizeof(FILES),0)<0)
		 ERROR(send error!)
	fclose(fp);
	printf("文件发送完毕\n");
	}
    pthread_exit(0);
}
unsigned char PADDING[]={0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void MD5Init(MD5_CTX *context)
{
     context->count[0] = 0;
     context->count[1] = 0;
     context->state[0] = 0x67452301;
     context->state[1] = 0xEFCDAB89;
     context->state[2] = 0x98BADCFE;
     context->state[3] = 0x10325476;
}
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen)
{
    unsigned int i = 0,index = 0,partlen = 0;
    index = (context->count[0] >> 3) & 0x3F;
    partlen = 64 - index;
    context->count[0] += inputlen << 3;
    if(context->count[0] < (inputlen << 3))
       context->count[1]++;
    context->count[1] += inputlen >> 29;

    if(inputlen >= partlen)
    {
       memcpy(&context->buffer[index],input,partlen);
       MD5Transform(context->state,context->buffer);
       for(i = partlen;i+64 <= inputlen;i+=64)
           MD5Transform(context->state,&input[i]);
       index = 0;
    }
    else
    {
        i = 0;
    }
    memcpy(&context->buffer[index],&input[i],inputlen-i);
}
void MD5Final(MD5_CTX *context,unsigned char digest[16])
{
    unsigned int index = 0,padlen = 0;
    unsigned  char bits[8];
    index = (context->count[0] >> 3) & 0x3F;
    padlen = (index < 56)?(56-index):(120-index);
    MD5Encode(bits,context->count,8);
    MD5Update(context,PADDING,padlen);
    MD5Update(context,bits,8);
    MD5Encode(digest,context->state,16);
}
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len)
{
    unsigned int i = 0,j = 0;
    while(j < len)
    {
         output[j] = input[i] & 0xFF;
         output[j+1] = (input[i] >> 8) & 0xFF;
         output[j+2] = (input[i] >> 16) & 0xFF;
         output[j+3] = (input[i] >> 24) & 0xFF;
         i++;
         j+=4;
    }
}
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len)
{
     unsigned int i = 0,j = 0;
     while(j < len)
     {
           output[i] = (input[j]) |
                       (input[j+1] << 8) |
                       (input[j+2] << 16) |
                       (input[j+3] << 24);
           i++;
           j+=4;
     }
}
void MD5Transform(unsigned int state[4],unsigned char block[64])
{
     unsigned int a = state[0];
     unsigned int b = state[1];
     unsigned int c = state[2];
     unsigned int d = state[3];
     unsigned int x[64];
     MD5Decode(x,block,64);
     FF(a, b, c, d, x[ 0], 7, 0xd76aa478); /* 1 */
 FF(d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
 FF(c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
 FF(b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
 FF(a, b, c, d, x[ 4], 7, 0xf57c0faf); /* 5 */
 FF(d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
 FF(c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
 FF(b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
 FF(a, b, c, d, x[ 8], 7, 0x698098d8); /* 9 */
 FF(d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
 FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
 FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
 FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
 FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
 FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
 FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

 /* Round 2 */
 GG(a, b, c, d, x[ 1], 5, 0xf61e2562); /* 17 */
 GG(d, a, b, c, x[ 6], 9, 0xc040b340); /* 18 */
 GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
 GG(b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
 GG(a, b, c, d, x[ 5], 5, 0xd62f105d); /* 21 */
 GG(d, a, b, c, x[10], 9,  0x2441453); /* 22 */
 GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
 GG(b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
 GG(a, b, c, d, x[ 9], 5, 0x21e1cde6); /* 25 */
 GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
 GG(c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
 GG(b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
 GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
 GG(d, a, b, c, x[ 2], 9, 0xfcefa3f8); /* 30 */
 GG(c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
 GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

 /* Round 3 */
 HH(a, b, c, d, x[ 5], 4, 0xfffa3942); /* 33 */
 HH(d, a, b, c, x[ 8], 11, 0x8771f681); /* 34 */
 HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
 HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
 HH(a, b, c, d, x[ 1], 4, 0xa4beea44); /* 37 */
 HH(d, a, b, c, x[ 4], 11, 0x4bdecfa9); /* 38 */
 HH(c, d, a, b, x[ 7], 16, 0xf6bb4b60); /* 39 */
 HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
 HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
 HH(d, a, b, c, x[ 0], 11, 0xeaa127fa); /* 42 */
 HH(c, d, a, b, x[ 3], 16, 0xd4ef3085); /* 43 */
 HH(b, c, d, a, x[ 6], 23,  0x4881d05); /* 44 */
 HH(a, b, c, d, x[ 9], 4, 0xd9d4d039); /* 45 */
 HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
 HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
 HH(b, c, d, a, x[ 2], 23, 0xc4ac5665); /* 48 */

 /* Round 4 */
 II(a, b, c, d, x[ 0], 6, 0xf4292244); /* 49 */
 II(d, a, b, c, x[ 7], 10, 0x432aff97); /* 50 */
 II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
 II(b, c, d, a, x[ 5], 21, 0xfc93a039); /* 52 */
 II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
 II(d, a, b, c, x[ 3], 10, 0x8f0ccc92); /* 54 */
 II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
 II(b, c, d, a, x[ 1], 21, 0x85845dd1); /* 56 */
 II(a, b, c, d, x[ 8], 6, 0x6fa87e4f); /* 57 */
 II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
 II(c, d, a, b, x[ 6], 15, 0xa3014314); /* 59 */
 II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
 II(a, b, c, d, x[ 4], 6, 0xf7537e82); /* 61 */
 II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
 II(c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /* 63 */
 II(b, c, d, a, x[ 9], 21, 0xeb86d391); /* 64 */
     state[0] += a;
     state[1] += b;
     state[2] += c;
     state[3] += d;
}
