#include<stdio.h>
#include<string.h>
int main ()
{
    int n,a,e,i,o,u,j;
    char k[1000];
    scanf("%d",&n);
    getchar();
    while(n--){
        a=0;
        e=0;
        i=0;
        o=0;
        u=0;
        for(i=0;;i++){
            scanf("%c",&k[i]);
            if(k[i]=='\n') break;
        }
        i=0;
        for(j=0;j<strlen(k);j++){
            if(k[j]=='a') a++;
            else if(k[j]=='e') e++;
            else if(k[j]=='i') i++;
            else if(k[j]=='o') o++;
            else if(k[j]=='u') u++;
        }
        printf("a:%d\ne:%d\ni:%d\no:%d\nu:%d\n",a,e,i,o,u);
        if(n!=0) printf("\n");
        memset(k,0,sizeof(char)*1000);
    }
}

