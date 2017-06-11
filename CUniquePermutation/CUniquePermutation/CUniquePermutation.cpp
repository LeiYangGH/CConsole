#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n = 0;
//Êä³öÊı×é
void print_arr(int arr[], int len)
{
	int i;
	//for (int i = 0; i < len; i++)
	//	printf("%d  ", arr[i]);
	//printf("\n");
	//  0 1 2
	//3 4 5 6
	//7 8 9
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

//  0 1 2
//3 4 5 6
//7 8 9

int isnear(int *a, int x, int y)
{
	return abs(a[x] - a[y]) == 1;
}
int shouldbreak(int *a)
{
	if (isnear(a, 0, 1)
		|| isnear(a, 1, 2)
		|| isnear(a, 2, 3)
		|| isnear(a, 3, 4)
		|| isnear(a, 4, 5)
		|| isnear(a, 5, 6)
		|| isnear(a, 6, 7)
		|| isnear(a, 7, 8)
		|| isnear(a, 8, 9)

		|| isnear(a, 3, 7)
		|| isnear(a, 0, 4)
		|| isnear(a, 4, 8)
		|| isnear(a, 1, 5)
		|| isnear(a, 5, 9)
		|| isnear(a, 2, 6)

		|| isnear(a, 0, 3)
		|| isnear(a, 1, 4)
		|| isnear(a, 4, 7)
		|| isnear(a, 2, 5)
		|| isnear(a, 5, 8)
		|| isnear(a, 6, 9)

		|| isnear(a, 3, 8)
		|| isnear(a, 4, 9)
		|| isnear(a, 0, 5)
		|| isnear(a, 1, 6)


		//  0 1 2
		//3 4 5 6
		//7 8 9
		)
		return 1;
	return 0;
}
void permute(int *array, int i, int length)
{
	if (length == i)
	{
		if (!shouldbreak(array))
			print_arr(array, length);
		return;
	}
	int j = i;
	for (j = i; j < length; j++)
	{

		swap(array + i, array + j);
		permute(array, i + 1, length);
		swap(array + i, array + j);
		/*	if (shouldbreak(array))
				break;*/
	}
	return;
}



int main()
{

	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	//input_array(arr, &len);
	permute(arr, 0, 10);
	//int a = 2, b = 3;
	//swap(&a, &b);

	//printf("%d %d",a,b);
	printf("n=%d\n",n);


	system("pause");
	return 0;
}