#include <stdio.h>

void chline(char ch[][5], int i , int j);
int main()
{
    char ch[5][5];
    char ch1 = 'a';
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            ch[i][j] = ch1++;
        }
    }
    j = 1, i = 2;
    chline(ch, i, j);
    return 0;
}

void chline(char ch[][5], int i, int j) {
    printf("%c\n", ch[j][i]);
}

