#include<stdio.h>
char a[]=" abcdefghijklmnopqrstuvwxyz";
int main (){
    int n,m,i,j=1;
    //char b[];
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) {
        printf("%c",a[j]);
        j++;
        if(i%m==0) j=1;
    }
}
  
