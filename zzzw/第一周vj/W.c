#include <stdio.h>

int main(int argc, char *argv[]) {
	int a[1050][1050];
	
	int n, m;
	scanf("%d%d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int  t;
			scanf("%1d", &t);
						
			a[i][j] = t;
		}
	}
	
	int r[10050] = { 0 };
	
	for(int j = 0; j < m; j++)
	{	
		int max = a[0][j];
		
		for (int i = 0; i < n; i++) {
			if(a[i][j] > max)
				max = a[i][j];
		}
		
		for (int i = 0; i < n; i++) {
			if(a[i][j] == max)
				r[i] = 1;
		}
	}
	
	int cnt = 0;
	
	for (int i = 0; i < n; i++) {
		if(r[i] == 1) cnt++;
	}
	
	printf("%d", cnt);
}