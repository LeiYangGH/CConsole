#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>


//void swap(char *p, char *q)
//{
//	char temp;
//	temp = *p;
//	*p = *q;
//	*q = temp;
//}
//
//void arrange(char a[], char n)
//{
//	int i;
//	for (i = 0; i <= n - 2; i++)
//	{
//		int m;
//		m = index(a, n, i);
//		if (m != i)swap(a + i, a + m);
//	}
//}


//int s[3][5] = { { 1,2,3,4,5 },{ 2,3,4,5,1 },{ 3,4,5,1,2 } };
//int i, sum;
//for (sum = 0, i = 0; i < 3; i++)
//	sum += best(s[i], 5);
//printf("%d\n", sum);
//
//int best(int a[], int n)
//{
//	int m, i;
//	for (m = a[0], i = 1; i < n; i++)
//		if (a[i] > m)
//			m = a[i];
//	return m;
//}

int test()
{
	static int b = 1;
	b = !b;
	return b;
}
#define M 5
#define N 5
int main()
{
	int score[M][N];
	int i;
	//这是关键代码
	int j, sumi = 0;
	for (int m = 0; m < M; m++)
		sumi += score[m][i];
	printf("平均分%.2f\n",
		(double)sumi / (double)(M));
	//以上
	system("pause");
	return 0;
}

