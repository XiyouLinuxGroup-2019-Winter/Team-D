#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp1, *fp2;
    fp1 = fopen("test.txt", "r");
    if (fp1 == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    fp2 = fopen("test.txt", "a");
    if (fp2 == NULL) {
        printf("Failed to open the file!\n");
        exit(0);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;

}

