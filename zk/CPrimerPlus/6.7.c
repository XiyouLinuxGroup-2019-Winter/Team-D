#include <stdio.h>
#include <string.h>

int main()
{
    char word[10];
    scanf("%s", word);
    int i = strlen(word);
    for (int j = i; j >= 0; j--) {
        printf("%c", word[j]);
    }
    return 0;
}

