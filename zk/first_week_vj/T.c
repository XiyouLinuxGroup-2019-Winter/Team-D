#include <stdio.h>
#define PI 3.14159265358

int main()
{
	double r,v1,v2;
	while(~scanf("%d%d%d", &r, &v1, &v2)){
		double r1 = v1 * r / v2;
		double t1 = (r-r1) / v1;
		double t2 = PI * r / v2;
        if (t1 < t2) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        } 
		
	}
	return 0;
}

