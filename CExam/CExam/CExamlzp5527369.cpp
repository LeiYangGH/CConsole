#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define FILE_BOOK "book.txt"
#define MAX_STRLEN 20
//��������ķ�Χ
#define MIN 1
#define MAX 100
#define TEST 0
#define NOANSWER 0 //�����û��ش�ֻ��ʾ�� 1����0
#define LESSLOOP 0 //����ѭ������ 1����0
//1

typedef struct single
{
	char name[MAX_STRLEN];
	int total;
}single;
single allsingles[100];
int allsinglescount = 0;
FILE *fp;
//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}
//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}


int add(int a, int b)
{
	return a + b;
}
int minus(int a, int b)
{
	return a - b;
}
int multiply(int a, int b)
{
	return a * b;
}
int devide(int a, int b)
{
	return a / b;
}

typedef struct opr
{
	char str[2];
	int(*op)(int a, int b);
}opr;
opr alloprators[4];

int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int randomminmax()//�̶�1-9
{
	return rand() % (MAX - MIN + 1) + MIN;
}


void init()
{
	strcpy(alloprators[0].str, "+");
	strcpy(alloprators[1].str, "-");
	strcpy(alloprators[2].str, "*");
	strcpy(alloprators[3].str, "/");
	alloprators[0].op = add;
	alloprators[1].op = minus;
	alloprators[2].op = multiply;
	alloprators[3].op = devide;
}

void concatstringandint(char des[], int n)
{
	char str[10];
	itoa(n, str, 10);
	strcat(des, str);
}


int testone()
{
	int i, re, input, judge;
	int a = randomminmax();
	int b = randomminmax();
	int opidrange[4] = { 0,1,2,3, };
	opr op = alloprators[opidrange[random(0, 3)]];
	char exp[50] = "";
	char str[4] = "";
	itoa(a, str, 10);
	strcat(exp, str);
	strcat(exp, op.str);
	itoa(b, str, 10);
	strcat(exp, str);
	printf("%s =? ", exp);
#if NOANSWER
	printf("\n");

	return 0;
#else

	re = op.op(a, b);
	scanf("%d", &input);
	if (re == input)
	{
		printf("Right��\n\n");
		judge = 1;
	}
	else
	{
		printf("Wrong��should be %d\n\n", re);
		judge = 0;
	}
	fprintf(fp, "%d %s %d = %d\n", a, op.str, b, re);
	return judge;
#endif
}


int testoneperson()
{
	int i, op = 1, total = 0;
	int opidrange[4];

#if LESSLOOP
	for (i = 0; i < 2; i++)
#else
	for (i = 0; i < 10; i++)
#endif
	{
		if (testone())
		{
			total += 10;
		}
	}

	printf("�ܷ�=%d\n", total);
	return total;
}


void welcomesingle()
{
	int i;
	system("cls");
	printf("-----------�������㿼�Կ�ʼ---------\n");
	printf("����%d������ѧ������:\r\n", allsinglescount);
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allsinglescount; i++)
	{
		printf("%s\t", allsingles[i].name);
	}
	printf("\n--------------------------------------------------\r\n");
	printf("-----------���������ʼ��ע�⣬һ����ʼ�ͱ�����������10����Ŀ---------\n");
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void singletest()
{
	int i, j, k, total = 0;
	int opidrange[4] = { 0,1,2,3 };
	for (i = 0; i < allsinglescount; i++)
	{
		printf("-----------������ѧ�� %s ����---------\n",
			allsingles[i].name);
		total += testoneperson();
		allsingles[i].total = total;
	}
}


void displaysingleresult()
{
	int i;
	printf("-----------���Խ��---------\n");
	single s = allsingles[0];
	printf("����������%s �ܷ֣�%d ��ȷ��%.1f\n", s.name, s.total, s.total / 100.0);
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void modulesingletest()
{
	welcomesingle();
	singletest();
	displaysingleresult();
}

int main()
{
	int i, total = 0;
	char choice = -1;
	srand(time(NULL));
	init();
	strcpy(allsingles[0].name, "����");
	allsingles[0].total = 0;
	allsinglescount = 1;
	fp = fopen(FILE_BOOK, "a+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_BOOK);
		getchar();
		exit(1);
	}
#if TEST
	modulesingletest();
	//modulereadsortgroup();
	//readallgroups();
	//displayallgroups();
	//writeallgroups();
	//int opsids[] = { 0,1,2,3 };
	//int opsids[] = { 1,1,1,1 };
	//int useopids[4];
	//generateuseids(4, 4, useopids);
	//printf("useopids=%d %d %d %d\n",
	//	useopids[0], useopids[1], useopids[2], useopids[3]);
	//for (i = 0; i < 20; i++)
	//{
	//	total = module2or3_x(3, opsids);
	//	printf("\n");

	//}
	//total = module2or3(0);
	//printf("�ܷ�=%d\n", total);


	system("pause");
#endif


	while (choice != 0)
	{
		printf("\n\t ������ϰ/����ϵͳ");
		printf("\n\t 1. �˳�");
		printf("\n\t 2. ���˿���");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '1':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			modulesingletest();
			break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	fclose(fp);
	system("pause");
	return 0;
}