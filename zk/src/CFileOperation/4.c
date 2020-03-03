#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("test.txt", "w+");
    char name[10] = "张三";
    char num[10] = "2202202";
    int age = 18;
    if (fp == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    fprintf(fp, "%s\t%s\t%d\n", name, num, age);
    fscanf(fp, "%s\t%s\t%d\n", name, num, &age);
    printf("%s\t%s\t%d\n", name, num, age);
    fclose(fp);
    return 0;
}

