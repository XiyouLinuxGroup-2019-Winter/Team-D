#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
int chops[5]={0},phil[5]={1,2,3,4,5},lock=0;
void *philos(void *);
int main()
{
	srand(time(NULL));
	int i;
	pthread_t  pthnum[5];
	void *stat;
	for(i=0;i<5;i++)
		if(pthread_create(&pthnum[i],NULL,philos,(void *)&phil[i])==-1)
		{
			printf("creat error!\n");
			exit(1);
		}
	for(i=0;i<5;i++)
		if(pthread_join(pthnum[i],(void *)&stat)==-1)
		{
			printf("pthread-join  error!\n");
			exit(1);
		}
	return 0;
}
void *philos(void *arg)
{
	int m=*(int *)arg;
	int left=m,right=(m+1)%5;
	while(1)
	{
		printf("哲学家%d正在思考问题\n",m);
		sleep(rand()%5);
		printf("哲学家%d饿了\n",m);
		while(lock==1);
		lock=1;
		while(chops[left]==1);
		chops[left]==1;
		printf("哲学家%d拿起了%d号筷子,现在只有一只筷子，不能进餐\n",m,left);
		while(chops[right]==1);
		chops[right]=1;
		printf("\033[0;45;47m哲学家%d拿起了%d号筷子，现在有两只筷子，开始进餐\033[0m\n",m,right);
		sleep(rand()%3);
		printf("\033[0;33;47m哲学家%d进餐完毕\033[0m\n",m);
		chops[left]=0;
		printf("哲学家%d放下了%d号筷子\n",m,left);
		chops[right]=0;
		printf("哲学家%d放下了%d号筷子\n",m,right);
		lock=0;

	}
}
