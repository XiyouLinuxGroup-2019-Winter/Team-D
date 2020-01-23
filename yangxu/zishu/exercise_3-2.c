include<stdio.h>
#include<string.h>
#include<math.h>
char a[6]="CHON";
double b[4]={12.01,1.008,16.00,14.01};
int main ()
{
    int n;
    scanf("%d",&n);
    while(n--){
        double sum=0;
        char c[82];
        scanf("%s",c);
        for(int i=0;i<strlen(c);i++){
            for(int j=0;j<4;j++){
                if(c[i]==a[j]){
                    int k=0;
                    for(int q=i+1;q<strlen(c);q++){
                        if('1'<=c[q]&&c[q]<='9') k++;
                        else break;
                    }
                    int m=0;
                    if(k!=0){
                        for(int q=i+1;q<=i+k;q++){
                            m+=(c[q]-'0')*pow(10,i+k-q);
                        }
                        sum+=b[j]*m*1.0;
                    }else sum+=b[j]*1.0;
                    printf("%d ",m);
                }
            }
        }
        printf("\n");
        printf("%.3f\n",sum);
    }
}

