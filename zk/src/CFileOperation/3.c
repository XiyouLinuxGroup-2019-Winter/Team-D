#include <stdio.h>
#include <stdlib.h>

int main()
{
    // "w+"模式: 先写入后读出
    FILE *fp = fopen("test.txt", "w+");
    if (fp == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    char str[30];
    printf("请输入3个字符串.\n");
    int i;
    for (i = 0; i < 3; i++) {
        printf("字符串%d:", i+1);
        fgets(str, 30, stdin);
        // scanf("%s", str);
        fputs(str, fp);
    }
    rewind(fp);
    while (fgets(str, 30, fp) != NULL) {
        // 把字符串输出到屏幕
        fputs(str, stdout); 
    }
    fclose(fp);
    return 0;
}

