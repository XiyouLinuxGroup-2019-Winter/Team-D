#include <stdio.h>

int main()
{
    int hour = 0;
    int wages = 0;
    int taxes = 0;
    int income = 0;
    scanf("%d", &hour);
    if (hour <= 40) {
        wages = hour * 1000;
        if (wages <= 300) {
            taxes = wages * 0.15;
        }
        else if (wages <= 450) {
            taxes = 300 * 0.15 + (wages - 300) * 0.2;
        }
        else {
            taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
        }
        income = wages - taxes;
    } 
    else {
        wages = 40000 + (hour - 40) * 1.5 * 1000;
        if (wages <= 300) {
            taxes = wages * 0.15;
        }
        else if (wages <= 450) {
            taxes = 300 * 0.15 + (wages - 300) * 0.2;
        }
        else {
            taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
        }
        income = wages - taxes; 
    }
    printf("%d %d %d", wages, taxes, income);
    return 0;

}

