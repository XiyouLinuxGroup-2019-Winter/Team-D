#include <stdio.h>

int main()
{
    char name[10] , surname[10];
    printf("please input name and surname");
    scanf("%s %s", name, surname);
    printf("%s,%s", name, surname);
    return 0;
}

