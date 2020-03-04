#include <stdio.h>
#include <stdlib.h>
#define N 3

typedef struct Animal {
    char name[10];
    int age;
    char duty[20];
}Animal;

int main()
{
    Animal a[N] = {
        {"兔朱迪", 5, "交通警察"},
        {"尼克", 8, "协警"},
        {"闪电", 10, "车管所职工"}
    };
    Animal t;
    int i;
    FILE *fp = fopen("test.txt", "wb+");
    if (fp == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    fwrite(a, sizeof(Animal), N, fp);
    printf("%s\t%s\t%s\n", "name", "age", "duty");
    for (i = 1; i <= N; i++) {
        fseek(fp, 0-i*sizeof(Animal), SEEK_END);
        fread(&t, sizeof(Animal), 1, fp);
        fprintf(stdout, "%s\t%d\t%s\n", t.name, t.age, t.duty);
    }
    fclose(fp);
    return 0;
}

