#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct Student {
    char name[10];
    char no[15];
    int sc[3];
    double ave;
}stu;

void inputInfo(stu a[], int n);
void writeInfo(stu a[], int n);

int main()
{
    int n;
    stu a[N];
    scanf("%d", &n);
    inputInfo(a, n);
    writeInfo(a, n);
    return 0;
}

void inputInfo(stu a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%s%s%d%d%d", a[i].name, a[i].no, &a[i].sc[0], &a[i].sc[1], &a[i].sc[2]);
        a[i].ave = (a[i].sc[0] + a[i].sc[1] + a[i].sc[2]) / 3.0;
    }
}

void writeInfo(stu a[], int n) {
    FILE *fp = fopen("test.txt", "wb");
    if (fp == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    fwrite(a, sizeof(stu), n, fp);
    fclose(fp);
}

