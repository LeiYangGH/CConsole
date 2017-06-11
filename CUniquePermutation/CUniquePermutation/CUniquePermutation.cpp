#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n = 0;//共多少个
//输出数组
void print_arr(int arr[], int len)
{
	int i;
	//横排输出
	//for (int i = 0; i < len; i++)
	//	printf("%d  ", arr[i]);
	//printf("\n");
	//根据下表显示
	//  0 1 2
	//3 4 5 6
	//7 8 9
	printf("  %d %d %d\n", arr[0], arr[1], arr[2]);
	printf("%d %d %d %d\n", arr[3], arr[4], arr[5], arr[6]);
	printf("%d %d %d\n", arr[7], arr[8], arr[9]);
	printf("\n\n");
	n++;
}

//交换两个值
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//  0 1 2
//3 4 5 6
//7 8 9
//数组a的x和y两个下标的元素相邻，也就是差的绝对值为1
int isnear(int *a, int x, int y)
{
	return abs(a[x] - a[y]) == 1;
}

//不合法
int bad(int *a)
{
	//横着
	if (isnear(a, 0, 1)
		|| isnear(a, 1, 2)
		|| isnear(a, 2, 3)
		|| isnear(a, 3, 4)
		|| isnear(a, 4, 5)
		|| isnear(a, 5, 6)
		|| isnear(a, 6, 7)
		|| isnear(a, 7, 8)
		|| isnear(a, 8, 9)

		//竖着
		|| isnear(a, 3, 7)
		|| isnear(a, 0, 4)
		|| isnear(a, 4, 8)
		|| isnear(a, 1, 5)
		|| isnear(a, 5, 9)
		|| isnear(a, 2, 6)

		//左下到右上
		|| isnear(a, 0, 3)
		|| isnear(a, 1, 4)
		|| isnear(a, 4, 7)
		|| isnear(a, 2, 5)
		|| isnear(a, 5, 8)
		|| isnear(a, 6, 9)

		//左上到右下
		|| isnear(a, 3, 8)
		|| isnear(a, 4, 9)
		|| isnear(a, 0, 5)
		|| isnear(a, 1, 6)
		)
		return 1;//至少两个相邻了
	return 0;//全部都不相邻
}
//排列算法，有了这个算法就不用写10个for循环了
//array是数组，i是排从i开始的下标到末尾的那一段，length是数组长度
//参考
//https://stackoverflow.com/questions/9148543/program-to-print-permutations-of-given-elements
void permute(int *array, int i, int length)
{
	if (length == i)
	{
		if (!bad(array))
			print_arr(array, length);
		return;
	}
	int j = i;
	for (j = i; j < length; j++)
	{

		swap(array + i, array + j);
		permute(array, i + 1, length);
		swap(array + i, array + j);
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