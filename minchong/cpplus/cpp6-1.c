#include<stdio.h>
int main()
{
    int i,h=0;
    char str[26];
    for(i='a';i<='z';i++)
    {
        str[h]=i;
        h++;
    }
    for(h=0;h<26;h++)
    printf("%c",str[h]);
}
