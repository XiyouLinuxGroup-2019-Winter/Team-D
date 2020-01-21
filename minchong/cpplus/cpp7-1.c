#include<stdio.h>
int main()
{
    char p[100];
    int q=0,w,e=0,r=0;
    while(1)
    {
        p[q]=getchar();
        if(p[q]=='#')
        break;
        q++;
    }
    for(w=0;w<q;w++)
    {
        if(p[w]==' ')
        e++;
        else
        r++;
    }
    printf("%d %d",e,r);
}
