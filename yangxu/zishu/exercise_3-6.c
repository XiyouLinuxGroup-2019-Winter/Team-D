#include<stdio.h>
int main ()
{
    int x,y;
    scanf("%d %d",&x,&y);
    char a[10][12];
    int b[10][12]={0};
    for(int i=0;i<x;i++){
        scanf("%s",a[i]);
    }
    //printf("ok\n");
    int k=1;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i==0&&a[i][j]!='*'){
                b[i][j]=k++;
            }
            else if(j==0&&a[i][j]!='*'){
                b[i][j]=k++;
            }
            else if(a[i][j]!='*'&&(a[i][j-1]=='*'||a[i-1][j]=='*')){
                b[i][j]=k++;
            }
        }
    }
    printf("\n");
    printf("Across\n");
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(a[i][j]!='*'){
                if(j==0){
                    printf("%d.",b[i][j]);
                    for(int k=j;k<y;k++){
                        if(a[i][k]!='*') printf("%c",a[i][k]);
                        else break;
                    }
                    printf("\n");
                }
                else if(a[i][j-1]=='*'){
                    printf("%d.",b[i][j]);
                    for(int k=j;k<y;k++){
                                                if(a[i][k]!='*') printf("%c",a[i][k]);
                        else break;
                                        }
                    printf("\n");
                }
            }
        }
    }
    printf("\n");
    printf("Down\n");
     for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                        if(a[i][j]!='*'){
                                if(i==0){
                                      printf("%d.",b[i][j]);
                                        for(int k=i;k<x;k++){
                                                if(a[k][j]!='*') printf("%c",a[k][j]);
                                                else break;
                                        }
                                        printf("\n");
                                }
                                else if(a[i-1][j]=='*'){
                                        printf("%d.",b[i][j]);
                                        for(int k=i;k<x;k++){
                                                if(a[k][j]!='*') printf("%c",a[k][j]);
                                                else break;
                                        }
                                        printf("\n");
                                }
                        }
                }
        }

}

