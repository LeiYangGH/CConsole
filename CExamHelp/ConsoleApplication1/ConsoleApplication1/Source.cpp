#include <stdlib.h>
#include <stdio.h>
double func(int n)
{
	if (n == 1)
		return n;
	else
	{
		return func(n - 1)
			+ (1 / (double)n);
	}
}
int main()
{
	int n;
	double result;
	printf("������n���س�����:");
	scanf("%d", &n);
	result = func(n);
	printf("%lf\n", result);
	system("pause");
	return 0;
}

