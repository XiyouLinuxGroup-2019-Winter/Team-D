#include<stdio.h>
#include<string.h>
int main ()
{
    int n;
    scanf("%d",&n);
    while(n--){
        char a[82];
        scanf("%s",a);
        int sum=0,k=1;
        for(int i=0;i<strlen(a);i++){
            if(a[i]=='O'){
                sum+=k;
                k++;
            }
            if(a[i]=='X') k=1;
        }
        printf("%d\n",sum);
    }
}

