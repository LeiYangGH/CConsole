#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int index(char a[], int n, int i)
{
	int m, j;
	for (m = i, j = i + 1; j < n; j++)
		if (a[j] < a[m])
			m = j;
	return m;
}

void swap(char *p, char *q)
{
	char temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

void arrange(char a[], char n)
{
	int i;
	for (i = 0; i <= n - 2; i++)
	{
		int m;
		m = index(a, n, i);
		if (m != i)swap(a + i, a + m);
	}
}

int main()
{
	char s[] = "2017";
	arrange(s, strlen(s));
	puts(s);
	system("pause");
	return 0;
}

