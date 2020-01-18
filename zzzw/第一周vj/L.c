/*
	所有人围成圆， 所以两两交换会从较短路径一边过去
	先列出简单的情况
			人数					次数
			1					-
			1 2 				1
			1 2 3 				1
			1 2 3 4 			2
			1 2 3 4 5 			交换过程 		1 5 交换， 接着2要到 1 的另一侧去， 所以2要连续交换 2两次， 接着3 要交换1次， 正好把4 换过来
								共1 + 2 + 1 = 4
			1 2 3 4 5 6			。。自己画一下吧
			
			最后得出的规律是  人数是奇数的时候就是		1 + 。。 + n / 2(向下取整) +.. + 1
							偶数		1 + 。。 + n / 2 - 1 + n / 2 - 1 +.. + 1
*/
#include <stdio.h>

int f(int n)
{	
	if(n == 1) return 1;
	return n + f(n - 1);
}

void ans(int n)
{	
	if(n == 2) printf("1\n");
	else if(n % 2 == 1)	printf("%d\n", 2 * f(n / 2) - n / 2);
	else 	printf("%d\n", 2 * f(n / 2 - 1));
	
}

int main(int argc, char *argv[]) {
	int n;
	
	while(scanf("%d", &n) != EOF)
		ans(n);
}