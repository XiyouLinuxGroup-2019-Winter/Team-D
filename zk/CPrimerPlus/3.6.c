#include <stdio.h>
#include <math.h>

int main()
{
    double water_num;
    scanf("%lf", &water_num);
    double water_molecule_weight = 3.0 * pow(10, -23);
    double water_molecule_num = water_num * 950 / water_molecule_weight;
    printf("%lf\n", water_molecule_num);
    return 0;
}

