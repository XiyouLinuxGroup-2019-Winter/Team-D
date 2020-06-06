#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    char buf[1024];

    time(&t); // 获取当前时间的秒数
    ctime_r(&t, buf); // 把当前时间的秒数转换成正确的时间格式存到buf里面
    printf("%s\n", buf);
    return 0;
}