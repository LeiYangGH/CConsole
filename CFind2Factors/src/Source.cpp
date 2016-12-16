#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000000

long factors_count(long num)
{
	long  i = 2, k = 0;
	while (num > 1)
	{
		if (num % i == 0)
		{
			k++;
			num /= i;
		}
		else i++;
	}
	return k;
}

long odd[N] = { 0 };
long faster_factors_count(long n)
{
	long d = 2, cnt = 0;
	double sqr = sqrt(n);
	while (d <= sqr)
	{
		if (n % d == 0)
		{
			switch (odd[d])
			{
			case 1:
				cnt++;
				if (odd[n / d] == 2)
					return 3;
				else if (cnt > 2)
					return 3;
				break;
			case 2:
				return 3;
				break;
			default:
				printf("case default= %ld \n", odd[d]);
				break;
			}
		}
		d++;
		//printf("d=%ld\t", d);
	}
	return cnt + 1;
}


void init()
{
	odd[0] = 0;
	odd[1] = 0;
	odd[2] = 1;
	odd[3] = 1;
	odd[4] = 2;
	odd[5] = 1;
}

int main()
{
	//long n = 100000;//23378
	long n = 50;//34
	long i, j = 0;
	init();
	//printf("input n:\n");
	//scanf("%ld", &n);
	if (n > 9999999)
	{
		printf("已经超过7个0，没有比较的意义:\n");
	}
	else
	{
		for (i = 1; i <= n; i++)
		{
			if ((odd[i] = faster_factors_count(i)) == 2)
				//if (factors_count(i) == 2)
			{
				printf("%ld\t", i);
				j++;
			}
		}
		printf("\ncount=%ld\n", j);
	}
	system("pause");
	return 0;
}
