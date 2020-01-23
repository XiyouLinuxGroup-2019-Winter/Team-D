#include<stdio.h>
#include<string.h>
int main ()
{
    char a[5][7];
    char n;
    int x,y,f=0;
    for(int i=0;i<5;i++){
        fgets(a[i],7,stdin);
    }
    for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    if(a[i][j]==' '){
                x=i;
                y=j;
            }
                }
        }

    while(scanf("%c",&n)&&n!='0'){
        if(n=='A'){
            a[x][y]=a[x-1][y];
            a[x-1][y]=' ';
            x=x-1;
            y=y;
        }
        if(n=='B'){
                        a[x][y]=a[x+1][y];
                        a[x+1][y]=' ';
                        x=x+1;
                        y=y;
                }
        if(n=='L'){
                        a[x][y]=a[x][y-1];
                        a[x][y-1]=' ';
                        x=x;
                        y=y-1;
                }
        if(n=='R'){
                        a[x][y]=a[x][y+1];
                        a[x][y+1]=' ';
                        x=x;
                        y=y+1;
                }
        if(n!='A'&&n!='B'&&n!='L'&&n!='R'){
            printf("This puzzle has no final configuration.\n");
            f=1;
            break;
        }
    }
    if(f==0){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                printf("%c ",a[i][j]);
            }
            printf("\n");
        }
    }
}

