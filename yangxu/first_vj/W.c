#include<stdio.h>
#include<string.h>
int main ()
{
    char a[105][105];
    int b[105]={0};
    int n,m,i,j,max=0,k=0;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++) scanf("%s",a[i]);
    for(i=0;i<m;i++){
        max=0;
        for(j=0;j<n;j++){
            if(a[j][i]-'0'>max) max=a[j][i]-'0';
        }
        for(j=0;j<n;j++){
            if(a[j][i]-'0'==max) b[j]=1;
        }
    }
    for(i=0;i<n;i++){
        if(b[i]==1) k++;
    }
    printf("%d",k);
}

