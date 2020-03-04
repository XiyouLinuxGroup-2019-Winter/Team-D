#include <stdio.h>

void Temperatures(double F_temperature);
int main()
{
    double F_temperature;
    while (scanf("%lf", &F_temperature) == 1) {
        Temperatures(F_temperature);
    } 
    return 0;
}
void Temperatures(double F_temperature) {
    double C_temperature, K_temperature;
    C_temperature = 5.0 / 9.0 * (F_temperature - 32.0);
    K_temperature = C_temperature + 273.16;
    printf("%.2lf %.2lf %.2lf\n", C_temperature, K_temperature, F_temperature);
}

