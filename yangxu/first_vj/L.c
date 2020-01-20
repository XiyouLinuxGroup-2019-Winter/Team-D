#include <stdio.h>
int main ()
{
    int n,i,sum=0;
   while(~scanf("%d",&n)){
        sum=0;
        if(n==3) sum=1;
        else if(n%2==0){
            for(i=1;i<=n/2-1;i++){
                sum=sum+i;
            }
            sum=sum*2;
        }else {
            for(i=1;i<=n/2-1;i++){
                sum=sum+i;
            }
            sum=sum*2+n/2;
        }
        printf("%d\n",sum);
    }
}

