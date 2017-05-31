#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int login()
{
	int tryleft = 3;//返回值0为登录失败，1为成功
	char input[20], pwd[] = "12345";//分别为用户输入密码和要求的密码
	printf("---------------------------------------\n");
	printf("             -欢迎进入系统-            \n");
	printf("---------------------------------------\n");
	while (tryleft)
	{
		printf("请输入密码，你还有%d次机会：\n", tryleft--);
		//gets(upw);有点编译器不支持gets
		scanf("%s", input);
		if (strcmp(input, pwd) == 0)
		{
			return 1;
			break;
		}
	}
	return 0;
}

void calcdate()
{
	printf("---------------------------------------\n");
	printf("           -生活中的趣味题 -           \n");
	printf("---------------------------------------\n");

	int daysofmonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int totaldays = 0, i;
	int year, month, day;
	printf("请输入年月日\n");
	while (1)
	{
		printf("年: ");
		while (1)
		{
			if (scanf("%d", &year) == 1)
				break;
			else
			{
				fflush(stdin);
				printf("输入格式错误，请重新输入\n");
			}
		}

		if (year < 0 || year>9999)
			printf("输入格式错误，请重新输入.\n");
		else
		{
			if ((year % 4 == 0 && year % 100 != 0)
				|| (year % 400 == 0))  //闰年2月天数+1
				daysofmonth[2]++;
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
			for (i = 0; i < month; i++)
				totaldays += daysofmonth[i];
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

void prime()
{
	printf("---------------------------------------\n");
	printf("             -数字趣味题 -             \n");
	printf("---------------------------------------\n");
	int x, i, ss = 1;
	printf("请输入一个整数：");
	while (1)
	{
		if (scanf("%d", &x) == 1)
			break;
		else
		{
			fflush(stdin);
			printf("输入格式错误，请重新输入\n");
		}
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

void pingpang()
{
	printf("---------------------------------------\n");
	printf("          -乒乓球队比赛分组-           \n");
	printf("---------------------------------------\n");
	int i, j, k;
	char a = ' ', b = ' ', c = ' ', ch[3] = { 'x','y','z' };
	for (i = 0; i < 3; i++)
	{
		a = ch[i];
		if (a != 'x')
		{
			for (j = 0; j < 3; j++)
			{
				c = ch[j];
				if (c != 'x'&& c != 'z')
				{
					for (k = 0; k < 3; k++)
						if (b != c && b != a && c != a)
						{
							b = ch[k];
							printf("a和%c比.\n", a);
							printf("b和%c比.\n", b);
							printf("c和%c比.\n", c);
							break;
						}
				}
			}
		}
	}
}

int main()
{
	int choice = -1;
	if (!login())
	{
		printf("\n密码错误，将退出程序！\n");
		system("pause");
		return 0;
	}
	while (choice != 0)
	{
		printf("\n\t 趣味程序");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 生活中的趣味题");
		printf("\n\t 2. 数字趣味题");
		printf("\n\t 3. 乒乓球队比赛分组");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);//清楚输入缓冲区，以免意外非法输入造成死循环
		choice = getchar();//获得输入字符
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			calcdate();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			prime();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			pingpang();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	printf("\n\n按任意键退出\n");
	system("pause");
	return 0;
}
