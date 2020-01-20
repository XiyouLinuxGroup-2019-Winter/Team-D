#include <stdio.h>

int main()
{
    int Daphne_dollar = 100, Deirdre_dollar = 100;
    double Daphne_yearsum = 100, Deirdre_sum = 100;
    double Daphne_sum = 100;
    int year = 0;
    while (Deirdre_sum <= Daphne_sum) {
        Daphne_yearsum = Daphne_dollar * 0.1;
        Daphne_sum += Daphne_yearsum;
        Deirdre_sum *= 1.05;
        year++;
    }
    printf("%d\n", year);
    printf("%lf %lf\n", Daphne_sum, Deirdre_sum);

    return 0;
}

