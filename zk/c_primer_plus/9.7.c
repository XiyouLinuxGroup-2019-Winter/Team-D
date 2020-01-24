#include <stdio.h>

double power(double num, int x);

int main()
{
    double num;
    int x;
    scanf("%lf %d", &num, &x);
    printf("%lf\n", power(num, x));

    return 0;
}

double power(double num, int x) {
    int flag = 0;
    if (num == 0) {
        if (x == 0) {
            printf("0 power 0 undefine, so return 1\n");
            return 1;
        }
        else {
            return 0; 
        }
    }
    else if (x == 0) {
        return 1;
    }
    else {
        int i;
        double sum = 1;
        if (x < 0) {
            x = -x;
            flag = 1;
        }
        for (i = 0; i < x; i++) {
            sum *= num;
        }
        if (x > 0 && flag == 0) {
            return sum;
        }
        else {
            sum = 1 / sum;
            return sum;
        }
    }
}
