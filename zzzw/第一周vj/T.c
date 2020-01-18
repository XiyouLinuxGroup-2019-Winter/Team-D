
//这题不会， 不能直观理解这个最优解情况
#include <stdio.h>
#define PI 3.1415926535897

int main(int argc, char *argv[]) {
	
	int r, v1, v2; 
	
	while(scanf("%d%d%d", &r, &v1, &v2) != EOF)
	{	
		if((double)PI * r / v2 > (double)(r - r *  (double)v1 / v2) / v1)
			printf("Yes\n");
		else printf("No\n");
		
	}
}