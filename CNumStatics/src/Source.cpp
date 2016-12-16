#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
void isPerfectNum(int a)
{
	int i;
	int iArr[20] = { 0 };                     /*当我把数组的下标改小时，比如20，程序会出现错误*/
	int *pi = iArr;
	for (i = 1; i < a; i++)
	{
		if (a%i == 0)
		{
			*pi = i;
			pi++;
		}
		else
			continue;
	}
	int sum = 0;
	for (; pi >= iArr; pi--)
		sum += *pi;
	if (sum == a)
		printf("%d\n", a);
	else
		printf("\0");
}
int main()
{
	int i;
	for (i = 1; i <= 1000; i++)
		isPerfectNum(i);

	system("pause");
	return 0;
}