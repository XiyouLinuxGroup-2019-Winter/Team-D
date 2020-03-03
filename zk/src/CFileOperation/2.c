#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("test.txt", "w+");
    int c;
    if (fp == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    while ((c = fgetc(stdin)) != '\n') {
        fputc(c, stdout);
        fputc(c, fp);
    }
    fputc('\n', stdout);
    char str[100];
    fread(str, 1, 5, fp);
    printf("%s\n", str);
    fclose(fp);
    return 0;
}

