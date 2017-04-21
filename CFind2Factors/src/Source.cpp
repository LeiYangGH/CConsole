#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100000000

long type[N] = { 0 };
long p[N] = { 0 };
long pmaxindex = 0;

long gettype(long n)
{
	long d = 2, index;
	for (index = 0; d * d <= n; index++)
	{
		d = p[index];
		if (n % d == 0)
			return 1 + type[n / d];
	}
	p[++pmaxindex] = n;
	return 1;
}

void init()
{
	type[0] = 0;
	type[1] = 0;
	type[2] = 1;
	type[3] = 1;
	type[4] = 2;
	type[5] = 1;

	p[0] = 2;
	p[1] = 3;
	p[2] = 5;
	p[3] = 7;
	pmaxindex = 3;
}

int main()
{
	long n = 20000000;//3704340
	//long n = 1000000;//210035
	//long n = 100000;//23378
	//long n = 100;//34
	long i, j = 0;
	init();
	//printf("input n:\n");
	//scanf("%ld", &n);
	if (n > 99999999)
	{
		printf("已经超过8个0，没有比较的意义:\n");
	}
	else
	{
		for (i = 4; i <= n; i++)
		{
			if ((type[i] = gettype(i)) == 2)
				//if (factors_count(i) == 2)
			{
				//printf("%ld\t", i);
				j++;
			}
		}
		printf("\ncount=%ld\n", j);
	}
	system("pause");
	return 0;
}
