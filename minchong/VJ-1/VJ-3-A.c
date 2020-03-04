#include<stdio.h>
#include"queue"
#include<stdlib.h>
void bfs(int map[5][5]);
struct td
{
    int x,y,p;
}queue[100];
int front=0;
int rear=1;
int main()
{
    int map[5][5],i,q,t=0;
    int ansx[100],ansy[100];
    for(q=0;q<5;q++)
        for(i=0;i<5;i++)
        scanf("%d",&map[q][i]);
    bfs(map);
    for(i=rear-1;i!=-1;i=queue[i].p)
    {
        ansx[t]=queue[i].x;
        ansy[t]=queue[i].y;
        t++;
    }
    for(t--;t>=0;t--)
    printf("(%d, %d)\n",ansx[t],ansy[t]);
    return 0;
}
void bfs(int map[5][5])
{
    int i,newx,newy;
    int mov[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    int bio[5][5];
    queue[0].x=0;
    queue[0].y=0;
    queue[0].p=-1;
    bio[0][0]=1;
    while(front<rear)
    {
        for(i=0;i<4;i++)
        {
            newx=queue[front].x+mov[i][0];
            newy=queue[front].y+mov[i][1];
            if(newx<0||newx>4||newy<0||newy>4||map[newx][newy]==1||bio[newx][newy]==1)
            continue;
            queue[rear].x=newx;
            queue[rear].y=newy;
            queue[rear].p=front;
            rear++;
            bio[newx][newy]=1;
            if(newx==4&&newy==4)
            return;
        }
        front++;
    }
}
