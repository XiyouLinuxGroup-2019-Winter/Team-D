#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define N 2
#define M 10

int in=0;
int out=0;
int buff[M]={0};
sem_t empty_sem;
sem_t full_sem;
pthread_mutex_t mutex;
int product_id=0;
int consume_id=0;

void print()
{
	int i;
	for(i=0;i<M;i++){
		printf("%d",buff[i]);
		printf("\n");
	}
}

void *product()
{
	int id=++product_id;

	while(1){
		sleep(1);

		sem_wait(&empty_sem);
		pthread_mutex_lock(&mutex);

		in=in%M;
		printf("product %d in %d.like:\n",id,in);

		buff[in]=1;
		print();
		in++;

		pthread_mutex_unlock(&mutex);
		sem_post(&full_sem);
	}
}

void *consume()
{
	int id=++consume_id;
	while(1){
		sleep(1);

		sem_wait(&full_sem);
		pthread_mutex_lock(&mutex);

		out=out%M;
		printf("consume %d in %d.like:\n",id,out);

		buff[out]=0;
		print();
		out++;

		pthread_mutex_unlock(&mutex);
		sem_post(&empty_sem);
	}
}

int main(int argc,char **argv)
{
	pthread_t id1[N];
	pthread_t id2[N];
	int i;

	int ini1=sem_init(&empty_sem,0,M);
	int ini2=sem_init(&full_sem,0,0);
	int ini3=pthread_mutex_init(&mutex,NULL);

	for(i=0;i<N;i++){
		pthread_create(&id1[i],NULL,product,(void*)(&i));
	}

	for(i=0;i<N;i++){
		pthread_create(&id2[i],NULL,consume,NULL);
	}

	for(i=0;i<N;i++){
		pthread_join(id1[i],NULL);
		pthread_join(id2[i],NULL);
	}

	sem_destroy(&empty_sem);
	sem_destroy(&full_sem);

	pthread_mutex_destroy(&mutex);
}
