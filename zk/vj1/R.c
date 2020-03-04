#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    char str[100];
    int i, j;
    int a, e, i1, o, u;
    while (n--) {
        gets(str);
        a = 0;
        e = 0;
        i1= 0;
        o = 0;
        u = 0;
        for (i = 0; i < strlen(str); i++) {
            if (str[i] == 'a') {
                a++;
            }
            else if (str[i] == 'e') {
                e++;
            }
            else if (str[i] == 'i') {
                i1++;
            }
            else if (str[i] == 'o') {
                o++;
            }
            else if (str[i] == 'u') {
                u++;
            }
        }
        printf("a:%d\ne:%d\ni:%d\no:%d\nu:%d\n", a, e, i1, o, u);
        if (n != 0) {
            printf("\n");
        }
    } 
    return 0;
}

