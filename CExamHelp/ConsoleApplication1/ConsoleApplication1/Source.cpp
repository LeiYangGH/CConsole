#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int Leap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 100)) ? 1 : 0;
}
int DayOfYear(int year, int month, int day)
{
	int leap = Leap(year);
	int cnt = 0;
	switch (month - 1)
	{
	case 11:cnt += 30;
	case 10:cnt += 31;
	case 9:cnt += 30;
	case 8:cnt += 31;
	case 7:cnt += 31;
	case 6:cnt += 30;
	case 5:cnt += 31;
	case 4:cnt += 30;
	case 3:cnt += 31;
	case 2:cnt += 28 + leap;
	case 1:cnt += 31; break;
	}
	cnt += day;
	printf("第%d天\n", cnt);
}
int main()
{
	printf("\n\n按任意键退出\n");
	system("pause");
	return 0;
}