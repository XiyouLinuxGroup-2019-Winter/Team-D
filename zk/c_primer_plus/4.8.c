#include <stdio.h>

int main()
{
    double distance, volume;
    scanf("%lf %lf", &distance, & volume);
    const double mile = distance / volume;
    printf("%.1lf\n", mile);
    double liter, kilometer;
    liter = volume * 3.785;
    kilometer = distance * 1.609;
    printf("%.1lf\n", liter / (100 * kilometer));
        
    
    return 0;
}

