#include <math.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <sys/ioctl.h> 
#include <net/if.h>
#include <signal.h>
#include <ncurses.h>
#include <math.h>

#define SEVR_IP     "127.0.0.1"
#define SEVR_PORT   9190
#define CNTNT_LEN   150
#define MSG_LEN     sizeof(struct msg)
#define ADDR_LEN    sizeof(struct sockaddr)
#define USR_LEN     sizeof(struct user)
#define PRT_LEN     8
#define HSTR_LEN    sizeof(struct chat_history)

int mainfd; 
int sockfd; 
int count;
struct sockaddr_in server;
int user_list_fd;

struct msg
{
	int flag; 
	int id_from;
	int id_to;
	char content[CNTNT_LEN];
};

struct user
{
	int id;
	char name[10];
	char password[10];
	char *p_chatlog;
	struct sockaddr user_addr;	
};

struct chat_history
{
	char content[CNTNT_LEN];
	char time[25];
	int to;
	int from;
	int count;
};

int i_print(char *pmsg, int size)
{
	int i = 1;

	for (i; i<= size; i++)
	{
		if (*pmsg != '\n')
		{
			printf("%c", *pmsg);
			pmsg ++;
		}
		else 
		{
			return(0);
		}
	}

	return(0);
}
int i_socket(int domain, int type, int protocol)
{
	int fd;	

	if ((fd = socket(domain, type, protocol)) == -1)
	{
		perror("creat socket error:");
		exit(1);
	}

	return(fd);	
}

int i_bind(int fd, const struct sockaddr *addr, int namelen)
{
	if (-1 == bind(fd, addr, namelen))
	{
		perror("i_bind error:");
		exit(1);
	}

	return (0);
}

int i_recvfrom(int fd, void *buf, size_t len, int flags, 
		struct sockaddr *addr, int *size)
{	
	if (-1 == recvfrom(fd, buf, len, flags, addr, size))
	{
		perror("i_recvfrom error:");
		exit(1);	
	}

	return(0);
}

int i_sendto(int fd, void *buf, size_t len, int flags,
		struct sockaddr *addr, int size)
{
	if (-1 == sendto(fd, buf, len, flags, addr, size))
	{
		perror("i_sendto error");
		exit(1);	
	}

	return (0);
}

int i_open(const char *pathname, int flags)
{
	int fd;
	if ((fd = open(pathname, flags)) == -1)
	{
		perror("open_failed");
		exit(1);
	}

	return (fd);
}
int i_read(int fd, void *msg, int len)
{
	if(-1 == read(fd, msg, len))
	{
		perror("i_read error");
		exit(1);
	}
	return(0);
}
int i_write(int fd, void *msg, int len)
{
	if (-1 == write(fd, msg, len))
	{
		perror("i_write error");
		exit(0);
	}
	return(0);
}

int i_init()
{
	mainfd = i_open("./chat_log", O_RDWR|O_CREAT);
	sockfd = i_socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	server.sin_port = htons(SEVR_PORT);

	perror("init");

	return (0);
}

char *i_get_time()
{
	time_t time_now;
	time(&time_now);

	return(ctime(&time_now));
}
int i_lseek(int fd, off_t size, int position)
{
	if (-1 == lseek(fd, size, position))
	{
		perror("seek error");
		exit(1);
	}
	return(0);
}
int i_saveto_chat(struct msg *pmsg)
{	
	struct chat_history hstr;


	bzero(&hstr, HSTR_LEN);
	count = count + 1;
	hstr.count =count;
	hstr.from = pmsg->id_from;
	hstr.to = pmsg->id_to;
	strncpy(hstr.content, pmsg->content, CNTNT_LEN);
	strncpy(hstr.time, i_get_time(), 25);

	i_lseek(mainfd, 0, SEEK_END);

	i_write(mainfd, &hstr, HSTR_LEN);

	return(0);
}



int init()
{
	i_init();

	user_list_fd = i_open("./user_list", O_RDWR|O_CREAT);

	struct user usr;
	/* init the user list file's fist user to 0*/
	memset((struct user*)&usr, '\0', sizeof(struct user));
	i_lseek(user_list_fd, 0, SEEK_SET);
	i_write(user_list_fd, (char*)&usr, USR_LEN);

	/* bind the struct sockaddr_in server to the sockfd */
	i_bind(sockfd, (struct sockaddr*)&server, ADDR_LEN);	

	struct chat_history apple;	

	bzero(&apple, HSTR_LEN);
	i_lseek(mainfd, 0, SEEK_SET);
	i_write(mainfd, &apple, HSTR_LEN);
	i_lseek(mainfd, -HSTR_LEN, SEEK_END);
	i_read(mainfd, &apple, HSTR_LEN);
	count = apple.count;

	return(0);
}
/* end:initialization */

/* start:message control */
int send_msg(struct msg *msg_recv, struct sockaddr *addr)
{
	int i;
	struct user usr;

	/* a common message come */	
	printf("a ordinar message come !\n");

	i = msg_recv->id_to;
	i_lseek(user_list_fd, i*USR_LEN, SEEK_SET);
	i_read(user_list_fd, &usr, USR_LEN);
	strncpy(msg_recv->append, usr.name, 10);

	i_sendto(sockfd, msg_recv, MSG_LEN, 0,
		&(usr.user_addr), ADDR_LEN);

	printf("id%d send a message to id%d sucess!\n", msg_recv->id_from, msg_recv->id_to);

	return(0);
}
int check_login(struct msg *msg_recv, struct sockaddr *addr)
{
	int i = msg_recv->id_from;;
	struct user usr;

	/* a login requet */
	printf("a login request come!\n");

	/* get the id's information */
	i_lseek(user_list_fd, i*USR_LEN, SEEK_SET);
	i_read(user_list_fd, &usr, USR_LEN);

	int n;
	n = strcmp(usr.password, msg_recv->content);
	/* 如果验证成功，则发送成功信息 */
	if (n == 0)
	{
		/* save user new address */
		i_lseek(user_list_fd, -USR_LEN, SEEK_CUR);
		usr.user_addr = *addr;
		i_write(user_list_fd, &usr, USR_LEN);
		/* tell user pass */
		i_sendto(sockfd, (struct msg*)msg_recv, sizeof(struct msg), 0,
			&(usr.user_addr), ADDR_LEN);

	}
	else
	{
		/* 出错的话的respond */
		if (0 != n)
		{
			printf("id %d login error.\n", i);
			bzero(msg_recv->content, CNTNT_LEN);			
			msg_recv->flag = -1;
			i_sendto(sockfd, (struct msg*)msg_recv, sizeof(struct msg), 0,
				&(usr.user_addr), ADDR_LEN);

		}
		return(1);
	}
	printf("Id %d login sucess!\n", i);	

	return(0);
}
int reg_user(struct msg *msg_recv, struct sockaddr *addr)
{
	struct user usr;

	printf("a regit requet come:\n");

	int n;
	i_lseek(user_list_fd, -USR_LEN, SEEK_END);
	i_read(user_list_fd, &usr, USR_LEN);
	const char *name;
	const char *password;

	name = &(msg_recv->content[0]);
	password = &(msg_recv->content[10]);
	strcpy((usr.name), name);
	strcpy(usr.password, password);
	memcpy(&(usr.user_addr),addr, ADDR_LEN);

	usr.id = (usr.id + 1);
	i_lseek(user_list_fd, 0, SEEK_END);
	i_write(user_list_fd, &usr, USR_LEN);

	msg_recv->id_from = usr.id;
	/* regist to the user list then tell the user reg success */
	i_sendto(sockfd, (struct msg*)msg_recv, sizeof(struct msg), 0,
		addr, ADDR_LEN); 

	printf("Id %d regist sucess!\n", usr.id);

	return(0);

}
int msg_cntl()
{
	struct msg msg_recv;
	struct sockaddr addr_recv;

	printf("begin listen input...\n");
	int size = ADDR_LEN;

	for (;;)
	{
		bzero(&msg_recv, MSG_LEN);
		i_recvfrom(sockfd, &msg_recv, sizeof(struct msg), 0,
			&addr_recv, &size);
		printf("message received...\n");

		i_saveto_chat(&msg_recv);

		switch (msg_recv.flag)
		{
			case 1 :
				send_msg(&msg_recv,(struct sockaddr*)&addr_recv);/* send ordinary chat */
				break;
			case 2 :
				check_login(&msg_recv, (struct sockaddr*)&addr_recv);
				break;			
			case 3 :
				reg_user(&msg_recv, (struct sockaddr*)&addr_recv);
				break;
			default :
				break;
		}
	}
	return(0);
}

int exit_sys()
{
	close(sockfd);
	close(mainfd);
	close(user_list_fd);
	printf("exit system");
	kill(0, SIGABRT);

	exit(0);
}

int menu()
{
	sleep(1);

	printf("----------help----menu---------\n");
	printf("\t r--report to user\n");
	printf("\t c--chat history\n");
	printf("\t h--help menu\n");
	printf("\t e--exit the system\n");
	printf("----------help_menu---------\n");

	int command = 0;

	printf("input command>");
	command = getchar();
	switch(command)
	{

		case 'c':
			read_chat_history();
			break;
		case 'e':
			exit_sys();
			break;
		case 'r':
			//report();
			//break;
		default :
			menu();
			break;
	}
	getchar();

	return(0);
}
int main()
{
	init();
	pid_t pid;
	switch (pid = fork())
	{
		case -1 :
			perror("fork error\n");
			exit(1);
			break;
		case 0 :
			msg_cntl();
			break;
		default :
			menu();
			break;
	}

	return(0);
}

struct sockaddr_in my_addr;
int my_id;

int my_log();/* declare funtion*/

/* */
int i_send_msg()
{		
	int id;
	struct msg the_msg;
	char end = '@';

	printf("input recver id:");
	scanf("%d", &id);
	getchar();
	printf("\ninput content:");
	i_input(the_msg.content);	

	char flag = 'y';

	if (1)
	{
		the_msg.flag = 1;
		the_msg.id_from = my_id;
		the_msg.id_to = id;

		i_sendto(sockfd, &the_msg, sizeof(struct msg), 0,
			(struct sockaddr*)&server, sizeof(struct sockaddr));

		i_saveto_chat(&the_msg);

		printf("send to id:%d success.\n", my_id);
		return(0);
	}
	else
		return(1);

	return(0);
}

int print_menu()
{
	printf("\n--------------help--menu----------------\n");
	printf("\t h--help munu\n");
	printf("\t s--send message\n");
	printf("\t r--reply to\n");
	printf("\t c--chat history\n");
	printf("\t f--send files\n");
	printf("\t e--exit the system\n");
	printf("----------------help--menu----------------\n");
}

int ordnary_msg_recv(struct msg *pmsg)
{
	char time_info[25];
	char end_symble;
	end_symble = '&';

	printf("Message:from %s(id%d) to U:\n", pmsg->append, pmsg->id_from);
	i_print(pmsg->content, MSG_LEN);
	printf("\n\t%s", i_get_time());

	return(0);
}

int handle_msg(struct msg *pmsg)
{	
	if (pmsg->flag == 1)
	{
		ordnary_msg_recv(pmsg);
		return(0);
	}
	else if (pmsg->flag >= 4)
	{
		file_msg_recv(pmsg);
		return(0);
	}	
	return(0);
}
int listen_msg()
{
	struct msg msg_recv;
	struct sockaddr addr_recv;
	int len = ADDR_LEN;

	printf("begin listen...\n");

	for ( ; ; )
	{	
		i_recvfrom(sockfd, &msg_recv, MSG_LEN, 0, 
			 &addr_recv, &len);

		i_saveto_chat(&msg_recv); /* save to history */

		 ordnary_msg_recv(&msg_recv);
	}
}

int main()
{
	init();
	printf("\n************welcome!************\n");
	my_log();

	pid_t pid;

	switch (pid = fork())
	{
		case -1 :
			perror("fork error!\n");
			exit(1);
			break;
		case 0 :
			listen_msg();
			break;
		default :
			menu();
			break;
	}
}