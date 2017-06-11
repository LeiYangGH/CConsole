#include <stdlib.h>
#include <stdio.h>

//输入数组
void input_array(int arr[], int *len)
{
	int i;
	printf("请输入要排序的整数的个数（3～19）：");
	scanf("%d", len);
	for (i = 0; i < *len; i++)
	{
		printf("请输入下标为%d的整数：", i);
		scanf("%d", &arr[i]);
	}
}
//输出数组
void print_arr(int arr[], int len)
{
	int i;
	for (int i = 0; i < len; i++)
		printf("%d  ", arr[i]);
	printf("\n");
}

//http://blog.csdn.net/changemyself/article/details/17145721
//http://c.biancheng.net/cpp/html/2443.html
//插入排序
void bubble_sort(int arr[], int len)
{
	int i, j;
	for (j = 0; j < len - 1; j++)
	{
		for (i = 0; i < len - 1 - j; i++)
		{

			if (arr[i] > arr[i + 1])
			{
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

//http://blog.csdn.net/u014136713/article/details/50879476
//http://c.biancheng.net/cpp/html/2744.html
//二分查找，返回的是找到的下标，没找到则为-1
int binarySearch(int a[], int len, int key)
{
	int low = 0;
	int high = len - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		int midVal = a[mid];
		if (midVal < key)
			low = mid + 1;
		else if (midVal > key)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

//http://www.tuicool.com/articles/ZRfi22J
//按原顺序插入
void insert(int arr[], int len, int num)
{
	int i, j, t1, t2;
	int end = arr[len - 2];
	if (num >= end)
		arr[len - 1] = num;
	else
	{
		for (i = 0; i < len - 1; i++)
			if (arr[i] > num)
			{
				t1 = arr[i]; //先保存当前位置的值
				arr[i] = num; //插入数值
				for (j = i + 1; j < len; j++)
				{ //以下三行将插入位置之后的数依次向后移动
					t2 = arr[j];
					arr[j] = t1;
					t1 = t2;
				}
				break; //找到合适的位置后就终止外层循环
			}
	}
}

//判断是否存在，不存在则插入
void insertinorder(int arr[], int len, int key, int *len1)
{
	//如果已经有这个数字，则不增加长度
	if (binarySearch(arr, len, key) >= 0)
	{
		*len1 = len;
	}
	else
	{
		//否则长度增加1
		*len1 = len + 1;
		insert(arr, *len1, key);
	}
}

//http://c.biancheng.net/cpp/html/2810.html
//画杨辉三角
void drawpyramid(int n)
{
	int i, j, k, a[14][14];
	for (i = 1; i <= n; i++)
		a[i][1] = a[i][i] = 1;  /*两边的数令它为1，因为现在循环从1开始，就认为a[i][1]为第一个数*/
	for (i = 3; i <= n; i++)
		for (j = 2; j <= i - 1; j++)
			a[i][j] = a[i - 1][j - 1] + a[i - 1][j];  /*除两边的数外都等于上两顶数之和*/
	for (i = 1; i <= n; i++)
	{
		for (k = 1; k <= n - i; k++)
			printf("   ");  /*这一行主要是在输出数之前打上空格占位，让输出的数更美观*/
		for (j = 1; j <= i; j++)  /*j<=i的原因是不输出其它的数，只输出我们想要的数*/
			printf("%6d", a[i][j]);
		printf("\n");  /*当一行输出完以后换行继续下一行的输出*/
	}
	printf("\n");
}

int main()
{
	int arr[20];// = { 2,5,4,7,4,4,2,65 };
	int len, len1, find;//len=8
	input_array(arr, &len);
	len1 = len;
	printf("排序前：");
	print_arr(arr, len);
	bubble_sort(arr, len);
	printf("排序后：");
	print_arr(arr, len);
	printf("请输入要查找和插入的整数：");
	scanf("%d", &find);
	insertinorder(arr, len, find, &len1);
	printf("插入后：");
	print_arr(arr, len1);
	printf("输出图形：");
	drawpyramid(10);
	system("pause");
	return 0;
}