#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define LINE "--------------------------------------------\n"
void printline(int n)
{
	long n1 = pow(2, n);
	double f3 = 1.0 / (double)n1;
	printf("%8ld\t%d\t%10.12f\n", n1, n, f3);
}
int main()
{
	int n;
	printf(LINE);
	printf("2 to power n\tn\t2 to power n-1\n");
	printf(LINE);
	for (n = 0; n <= 20; n++)
		printline(n);
	printf(LINE);
	system("pause");
	return 0;
}

