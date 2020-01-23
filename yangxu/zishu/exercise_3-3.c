#include<stdio.h>
#include<string.h>
char a[82];
int b[10];
int main ()
{
    int n,m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int k=i,q=0;
        while(k>0){
            k=k/10;
            q++;
        }
        m=m+q-1;
        k=i;
        for(int j=0;j<q;j++){
            a[m]=k%10+'0';
            k=k/10;
            if(j!=q-1) m--;
        }
        m=m+q;
    }
    for(int i=0;i<strlen(a);i++){
        b[a[i]-'0']++;
    }
    for(int i=0;i<10;i++) printf("%d ",b[i]);
    printf("\n");
}

