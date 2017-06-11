#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int n = 0;
void print_arr(int arr[], int len)
{
	int i;
	printf("  %d %d %d\n", arr[0], arr[1], arr[2]);
	printf("%d %d %d %d\n", arr[3], arr[4], arr[5], arr[6]);
	printf("%d %d %d\n", arr[7], arr[8], arr[9]);
	printf("\n\n");
	n++;
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int bad(int *a)
{
	int i;
	int p[23][2] = {
		{ 0,1 },{ 1,2 },{ 3,4 },{ 4,5 },{ 5,6 },{ 7,8 },{ 8,9 },
		{ 3,7 },{ 0,4 },{ 4,8 },{ 1,5 },{ 5,9 },{ 2,6 },
		{ 0,3 },{ 1,4 },{ 4,7 },{ 2,5 },{ 5,8 },{ 6,9 },
		{ 3,8 },{ 4,9 },{ 0,5 },{ 1,6 },
	};
	for (i = 0; i < 23; i++)
	{
		if (abs(a[p[i][0]] - a[p[i][1]]) == 1)
			return 1;
	}

	return 0;
}

void permute(int *a, int i, int len)
{
	if (len == i)
	{
		if (!bad(a))
			n++;
		return;
	}
	int j = i;
	for (j = i; j < len; j++)
	{
		swap(a + i, a + j);
		permute(a, i + 1, len);
		swap(a + i, a + j);
	}
	return;
}

int main()
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	permute(arr, 0, 10);
	printf("n=%d\n", n);
	system("pause");
	return 0;
}