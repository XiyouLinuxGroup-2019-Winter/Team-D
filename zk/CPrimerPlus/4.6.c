#include <stdio.h>
#include <string.h>

int main()
{
    char name[10], surname[10];
    scanf("%s %s", name, surname);
    printf("%s %s\n", name, surname);
    int name_num, surname_num;
    name_num = strlen(name);
    surname_num = strlen(surname);
    printf("%*d %*d\n", name_num, name_num, surname_num, surname_num);
    printf("%s %s\n", name, surname);
    printf("%-*d %-*d\n", name_num, name_num, surname_num, surname_num);

    return 0;
}

