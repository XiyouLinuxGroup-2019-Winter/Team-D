#include <stdio.h>
#define GRADE1 8.75
#define GRADE2 9.33
#define GRADE3 10.00
#define GRADE4 11.20

void menu();

int main()
{
    menu();
    int wages, taxes, income;
    int grade;
    int hour;
    int flag = 0;
    while (flag == 0) {
        scanf("%d", &grade);
        switch (grade) {
            case 1 :scanf("%d", &hour);
                    if (hour <= 40) {
                        wages = hour * GRADE1;
                    }
                    else {
                        wages = 40000 + (hour - 40) * 1.5 * GRADE1;
                    }
                    if (wages <= 300) {
                        taxes = wages * 0.15;
                    }
                    else if (wages <= 450) {
                        taxes = 300 * 0.15 + (wages - 300) * 0.20;
                    }
                    else {
                        taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
                    }
                    income = wages - taxes;
                    printf("%d %d %d\n", wages, taxes, income);
                    break;
            case 2 :scanf("%d", &hour);
                    if (hour <= 40) {
                        wages = hour * GRADE2;
                    }
                    else {
                        wages = 40000 + (hour - 40) * 1.5 * GRADE2;
                    }
                    if (wages <= 300) {
                        taxes = wages * 0.15;
                    }
                    else if (wages <= 450) {
                        taxes = 300 * 0.15 + (wages - 300) * 0.20;
                    }
                    else {
                        taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
                    }
                    income = wages - taxes;
                    printf("%d %d %d\n", wages, taxes, income);
                    break;
            case 3 :scanf("%d", &hour);
                    if (hour <= 40) {
                        wages = hour * GRADE3;
                    }
                    else {
                        wages = 40000 + (hour - 40) * 1.5 * GRADE3;
                    }
                    if (wages <= 300) {
                        taxes = wages * 0.15;
                    }
                    else if (wages <= 450) {
                        taxes = 300 * 0.15 + (wages - 300) * 0.20;
                    }
                    else {
                        taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
                    }
                    income = wages - taxes;
                    printf("%d %d %d\n", wages, taxes, income);
                    break;
            case 4 :scanf("%d", &hour);
                    if (hour <= 40) {
                        wages = hour * GRADE4;
                    }
                    else {
                        wages = 40000 + (hour - 40) * 1.5 * GRADE4;
                    }
                    if (wages <= 300) {
                        taxes = wages * 0.15;
                    }
                    else if (wages <= 450) {
                        taxes = 300 * 0.15 + (wages - 300) * 0.20;
                    }
                    else {
                        taxes = 300 * 0.15 + 150 * 0.2 + (wages - 450) * 0.25;
                    }
                    income = wages - taxes;
                    printf("%d %d %d\n", wages, taxes, income);
                    break;
            case 5 :flag = 1;break;
            default :printf("please input right number\n");
                     menu();break;
        }
   }
    return 0;
}

void menu() {
    printf("*************\n");
    printf("1) $8.75/hr\t2) $9.33/hr\n");
    printf("3) $10.00/hr\t4) $11.20/hr\n");
    printf("5) quit\n");
    printf("*************\n");
}

