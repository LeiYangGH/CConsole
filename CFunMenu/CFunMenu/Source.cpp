#include <stdio.h>
#include <string.h>
#include <math.h>
int login()
{
	int i = 3, ret = 0;
	char input[20], pw[] = "12345";

	printf("---------------------------------------\n");
	printf("             -��ӭ����ϵͳ-            \n");
	printf("---------------------------------------\n");
	while (i)
	{
		printf("���������룬�㻹��%d�λ��᣺\n", i--);
		//gets(upw);�е��������֧��gets
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
	printf("-            -Ȥζ�������˵�-         -\n");
	printf("-            1.�����е�Ȥζ��         -\n");
	printf("-            2.����Ȥζ��             -\n");
	printf("-            3.ƹ����ӱ�������       -\n");
	printf("-            4.�˳�                   -\n");
	printf("---------------------------------------\n");
	int sub = 0; int s_ret;
	while (1)
	{
		printf("������1-4.\n");
		while (1)
		{
			s_ret = scanf("%d", &sub);
			if (s_ret != 1)
			{
				fflush(stdin);
				printf("�����ʽ��������������\n");
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
	printf("           -�����е�Ȥζ�� -           \n");
	printf("---------------------------------------\n");

	int daysofmonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int totaldays = 0, i;
	int year, month, day;
	int s_ret;
	printf("������������\n");
	while (1)
	{
		printf("��: ");
		while (1)
		{
			s_ret = scanf("%d", &year);
			if (s_ret != 1)
			{
				fflush(stdin);
				printf("�����ʽ��������������\n");
			}
			else break;
		}

		if (year < 0 || year>9999)
			printf("�����ʽ��������������.\n");
		else
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))  daysofmonth[2]++;
			break;
		}
	}
	while (1)
	{
		printf("��: ");
		scanf("%d", &month);
		if (month < 1 || month>12)
			printf("�����ʽ��������������.\n");
		else
		{
			for (i = 0; i < month; i++) totaldays += daysofmonth[i];
			break;
		}

	}
	while (1)
	{
		printf("��: ");
		scanf("%d", &day);
		if (day<0 || day>daysofmonth[month])
			printf("�����ʽ��������������.\n");
		else
		{
			totaldays += day;
			break;
		}
	}
	printf("%d��%d��%d���ǵ�%d�졣\n", year, month, day, totaldays);
}

void submenu_2()
{
	printf("---------------------------------------\n");
	printf("             -����Ȥζ�� -             \n");
	printf("---------------------------------------\n");
	int x, i, ss = 1; int s_ret;
	printf("������һ��������");
	while (1)
	{
		s_ret = scanf("%d", &x);
		if (s_ret != 1)
		{
			fflush(stdin);
			printf("�����ʽ��������������\n");
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
		printf("%d��������\n", x);
	else
		printf("%d����������\n", x);
}

void submenu_3()
{
	printf("---------------------------------------\n");
	printf("          -ƹ����ӱ�������-           \n");
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

	printf("a��%c��.\n", a);
	printf("b��%c��.\n", b);
	printf("c��%c��.\n", c);
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
