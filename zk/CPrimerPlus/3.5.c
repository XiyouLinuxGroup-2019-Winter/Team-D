#include <stdio.h>
#include <math.h>

int main()
{
    int age;
    scanf("%d", &age);
    double sec;
    sec = 3.156 * pow(10, 7);    
    printf("This age is %lf second\n", age * sec);
    return 0;
}

