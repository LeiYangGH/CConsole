#include <stdlib.h>
#include <stdio.h>

//��������
void input_array(int arr[], int *len)
{
	int i;
	printf("������Ҫ����������ĸ�����3��19����");
	scanf("%d", len);
	for (i = 0; i < *len; i++)
	{
		printf("�������±�Ϊ%d��������", i);
		scanf("%d", &arr[i]);
	}
}
//�������
void print_arr(int arr[], int len)
{
	int i;
	for (int i = 0; i < len; i++)
		printf("%d  ", arr[i]);
	printf("\n");
}

//http://blog.csdn.net/changemyself/article/details/17145721
//http://c.biancheng.net/cpp/html/2443.html
//��������
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
//���ֲ��ң����ص����ҵ����±꣬û�ҵ���Ϊ-1
int binarySearch(int arr[], int len, int find)
{
	int low = 0;
	int high = len - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		int midVal = arr[mid];
		if (midVal < find)
			low = mid + 1;
		else if (midVal > find)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

//http://www.tuicool.com/articles/ZRfi22J
//��ԭ˳�����
void insert(int arr[], int len, int find)
{
	int i, j, t1, t2;
	int end = arr[len - 2];
	if (find >= end)
		arr[len - 1] = find;
	else
	{
		for (i = 0; i < len - 1; i++)
			if (arr[i] > find)
			{
				t1 = arr[i]; //�ȱ��浱ǰλ�õ�ֵ
				arr[i] = find; //������ֵ
				for (j = i + 1; j < len; j++)
				{ //�������н�����λ��֮�������������ƶ�
					t2 = arr[j];
					arr[j] = t1;
					t1 = t2;
				}
				break; //�ҵ����ʵ�λ�ú����ֹ���ѭ��
			}
	}
}

//�ж��Ƿ���ڣ������������
void insertinorder(int arr[], int len, int find, int *len1)
{
	//����Ѿ���������֣������ӳ���
	if (binarySearch(arr, len, find) >= 0)
	{
		*len1 = len;
	}
	else
	{
		//���򳤶�����1
		*len1 = len + 1;
		insert(arr, *len1, find);
	}
}

//http://c.biancheng.net/cpp/html/2810.html
//���������
void drawpyramid(int layer)
{
	int i, j, k, a[14][14];
	for (i = 1; i <= layer; i++)
		a[i][1] = a[i][i] = 1;  /*���ߵ�������Ϊ1����Ϊ����ѭ����1��ʼ������Ϊa[i][1]Ϊ��һ����*/
	for (i = 3; i <= layer; i++)
		for (j = 2; j <= i - 1; j++)
			a[i][j] = a[i - 1][j - 1] + a[i - 1][j];  /*�����ߵ����ⶼ������������֮��*/
	for (i = 1; i <= layer; i++)
	{
		for (k = 1; k <= layer - i; k++)
			printf("   ");  /*��һ����Ҫ���������֮ǰ���Ͽո�ռλ�����������������*/
		for (j = 1; j <= i; j++)  /*j<=i��ԭ���ǲ��������������ֻ���������Ҫ����*/
			printf("%6d", a[i][j]);
		printf("\n");  /*��һ��������Ժ��м�����һ�е����*/
	}
	printf("\n");
}

int main()
{
	int arr[20];// = { 2,5,4,7,4,4,2,65 };
	int len, len1, find;//len=8
	input_array(arr, &len);
	len1 = len;
	printf("����ǰ��");
	print_arr(arr, len);

	bubble_sort(arr, len);
	printf("�����");
	print_arr(arr, len);

	printf("������Ҫ���ҺͲ����������");
	scanf("%d", &find);
	insertinorder(arr, len, find, &len1);
	printf("�����");
	print_arr(arr, len1);

	printf("���ͼ�Σ�");
	drawpyramid(10);

	system("pause");
	return 0;
}