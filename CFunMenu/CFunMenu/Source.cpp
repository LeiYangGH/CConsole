#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int login()
{
	int tryleft = 3;//����ֵ0Ϊ��¼ʧ�ܣ�1Ϊ�ɹ�
	char input[20], pwd[] = "12345";//�ֱ�Ϊ�û����������Ҫ�������
	printf("---------------------------------------\n");
	printf("             -��ӭ����ϵͳ-            \n");
	printf("---------------------------------------\n");
	while (tryleft)
	{
		printf("���������룬�㻹��%d�λ��᣺\n", tryleft--);
		//gets(upw);�е��������֧��gets
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
	printf("           -�����е�Ȥζ�� -           \n");
	printf("---------------------------------------\n");

	int daysofmonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int totaldays = 0, i;
	int year, month, day;
	printf("������������\n");
	while (1)
	{
		printf("��: ");
		while (1)
		{
			if (scanf("%d", &year) == 1)
				break;
			else
			{
				fflush(stdin);
				printf("�����ʽ��������������\n");
			}
		}

		if (year < 0 || year>9999)
			printf("�����ʽ��������������.\n");
		else
		{
			if ((year % 4 == 0 && year % 100 != 0)
				|| (year % 400 == 0))  //����2������+1
				daysofmonth[2]++;
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
			for (i = 0; i < month; i++)
				totaldays += daysofmonth[i];
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

void prime()
{
	printf("---------------------------------------\n");
	printf("             -����Ȥζ�� -             \n");
	printf("---------------------------------------\n");
	int x, i, ss = 1;
	printf("������һ��������");
	while (1)
	{
		if (scanf("%d", &x) == 1)
			break;
		else
		{
			fflush(stdin);
			printf("�����ʽ��������������\n");
		}
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

void pingpang()
{
	printf("---------------------------------------\n");
	printf("          -ƹ����ӱ�������-           \n");
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
							printf("a��%c��.\n", a);
							printf("b��%c��.\n", b);
							printf("c��%c��.\n", c);
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
		printf("\n������󣬽��˳�����\n");
		system("pause");
		return 0;
	}
	while (choice != 0)
	{
		printf("\n\t Ȥζ����");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �����е�Ȥζ��");
		printf("\n\t 2. ����Ȥζ��");
		printf("\n\t 3. ƹ����ӱ�������");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);//������뻺��������������Ƿ����������ѭ��
		choice = getchar();//��������ַ�
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			calcdate();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			prime();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			pingpang();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}
