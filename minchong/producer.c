#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
int buf[50],ID=0,full=0,lock=0,empty=50;
void *producer();
void *consumer();
int main()
{
	pthread_t threadnum[15],temp;
	int i;
	for(i=0;i<10;i++)
	{
		if(pthread_create(&temp,NULL,producer,NULL)==-1)
		{
			printf("creat error!\n");
			exit(1);
		}
		threadnum[i]=temp;
	}
	for(i;i<15;i++)
	{
		if(pthread_create(&temp,NULL,consumer,NULL)==-1)
		{
			printf("creat error!\n");
			exit(1);
		}
		threadnum[i]=temp;
	}
	void **retval;
	for(i=0;i<15;i++)
	{
		if(pthread_join(threadnum[i],retval)==-1)
		{
			printf("fail to recollect!\n");
			exit(1);
		}
	}
	return 0;
}
void *producer()
{
	while(1)
	{
		while(empty<=0)
		{
			printf("缓冲区已满！\n");
		}
		while(lock==1);
		lock=1;
		ID++;
		buf[50-empty]=ID;
		printf("生产一个产品ID%d,缓冲区位置为%d\n",ID,50-empty);
		empty--;
		full++;
		lock=0;
		sleep(1);
	}
}
void *consumer()
{
	while(1)
	{
		while(full<=0)
			printf("缓冲区为空！\n");
		while(lock==1);
		lock=1;
		printf("\t\t\t\t消费了一个产品ID%d,缓冲区位置为%d\n",buf[full-1],full-1);
		buf[full-1]=0;
		full--;
		empty++;
		lock=0;
		sleep(1);
	}
}
