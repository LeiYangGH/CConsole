#include <stdio.h>
#include <string.h>
#include <math.h>
int login()
{
	int i = 3, ret = 0;
	char input[20], pw[] = "12345";

	printf("---------------------------------------\n");
	printf("             -欢迎进入系统-            \n");
	printf("---------------------------------------\n");
	while (i)
	{
		printf("请输入密码，你还有%d次机会：\n", i--);
		//gets(upw);有点编译器不支持gets
		scanf("%s", input);
		if (strcmp(input, pw) == 0)
		{
			ret = 1; break;
		}
	}
	return ret;
}

int menu()
{
	printf("---------------------------------------\n");
	printf("-            -趣味程序主菜单-         -\n");
	printf("-            1.生活中的趣味题         -\n");
	printf("-            2.数字趣味题             -\n");
	printf("-            3.乒乓球队比赛分组       -\n");
	printf("-            4.退出                   -\n");
	printf("---------------------------------------\n");
	int sub = 0; int s_ret;
	while (1)
	{
		printf("请输入1-4.\n");
		while (1)
		{
			s_ret = scanf("%d", &sub);
			if (s_ret != 1)
			{
				fflush(stdin);
				printf("输入格式错误，请重新输入\n");
			}
			else break;
		}
		if (1 <= sub && sub <= 4) break;
	}
	return sub;
}

void submenu_1()
{
	printf("---------------------------------------\n");
	printf("           -生活中的趣味题 -           \n");
	printf("---------------------------------------\n");

	int daysofmonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int totaldays = 0, i;
	int year, month, day;
	int s_ret;
	printf("请输入年月日\n");
	while (1)
	{
		printf("年: ");
		while (1)
		{
			s_ret = scanf("%d", &year);
			if (s_ret != 1)
			{
				fflush(stdin);
				printf("输入格式错误，请重新输入\n");
			}
			else break;
		}

		if (year < 0 || year>9999)
			printf("输入格式错误，请重新输入.\n");
		else
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))  daysofmonth[2]++;
			break;
		}
	}
	while (1)
	{
		printf("月: ");
		scanf("%d", &month);
		if (month < 1 || month>12)
			printf("输入格式错误，请重新输入.\n");
		else
		{
			for (i = 0; i < month; i++) totaldays += daysofmonth[i];
			break;
		}

	}
	while (1)
	{
		printf("日: ");
		scanf("%d", &day);
		if (day<0 || day>daysofmonth[month])
			printf("输入格式错误，请重新输入.\n");
		else
		{
			totaldays += day;
			break;
		}
	}
	printf("%d年%d月%d日是第%d天。\n", year, month, day, totaldays);
}

void submenu_2()
{
	printf("---------------------------------------\n");
	printf("             -数字趣味题 -             \n");
	printf("---------------------------------------\n");
	int x, i, ss = 1; int s_ret;
	printf("请输入一个整数：");
	while (1)
	{
		s_ret = scanf("%d", &x);
		if (s_ret != 1)
		{
			fflush(stdin);
			printf("输入格式错误，请重新输入\n");
		}
		else break;
	}
	for (i = 2; i < x; i++)
		if (x%i == 0)
		{
			ss = 0;
			break;
		}
	if (ss)
		printf("%d是素数。\n", x);
	else
		printf("%d不是素数。\n", x);
}

void submenu_3()
{
	printf("---------------------------------------\n");
	printf("          -乒乓球队比赛分组-           \n");
	printf("---------------------------------------\n");
	int i, j, k, found = 0;
	char a = ' ', b = ' ', c = ' ', ch[3] = { 'x','y','z' };
	for (i = 0; i < 3; i++)
	{
		if (found)break;
		a = ch[i];
		if (a != 'x')
		{
			for (j = 0; j < 3; j++)
			{
				if (found) break;
				c = ch[j];
				if (c != 'x'&& c != 'z')
				{
					for (k = 0; k < 3; k++)
						if (b != c && b != a && c != a)
						{
							b = ch[k];
							found = 1;
							break;
						}
				}
			}
		}
	}

	printf("a和%c比.\n", a);
	printf("b和%c比.\n", b);
	printf("c和%c比.\n", c);
}

void main()
{
	int choice = 0;
	if (login())
		while (1)
		{
			choice = menu();
			if (choice == 1)
				submenu_1();
			else if (choice == 2)
				submenu_2();
			else if (choice == 3)
				submenu_3();
			else if (choice == 4) break;
			printf("\n\n");
		}
}
