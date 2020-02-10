#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int ch;

    if (argc != 3) {
        fprintf(stderr, "输入形式:copyFile 原文件名 目标文件名\n");
        exit(EXIT_FAILURE);
    }
    if ((in = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "打不开文件:%s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((out = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "打不开文件:%s\n", argv[2]);
        fclose(in); //注意
        exit(EXIT_FAILURE);
    }
    while ((ch = getc(in)) != EOF) {
        if (putc(ch, out) == EOF) {
            break;
        }    //出现EOF条件有两个:一个是读到文件末尾,一个是出现错误

    }
    if (ferror(in)) {  //用来判断是不是出现错误导致而不是读到末尾
        printf("读取文件%s失败!\n", argv[1]);
    }
    if (ferror(out)) {
        printf("写入文件%s失败!\n", argv[2]);
    }
    printf("复制一个文件成功!\n");
    fclose(in);
    fclose(out);
    return 0;
}

