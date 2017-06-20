#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define FILE_BOOK "book.txt"
#define MAX_STRLEN 20
//计算的数的范围
#define MIN 1
#define MAX 100
#define TEST 0
#define NOANSWER 0 //不用用户回答，只显示题 1或者0
#define LESSLOOP 0 //减少循环次数 1或者0
//1

typedef struct single
{
	char name[MAX_STRLEN];
	int total;
}single;
single allsingles[100];
int allsinglescount = 0;
FILE *fp;
//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}
//字符串转整数
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

int randomminmax()//固定1-9
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
		printf("Right！\n\n");
		judge = 1;
	}
	else
	{
		printf("Wrong！should be %d\n\n", re);
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

	printf("总分=%d\n", total);
	return total;
}


void welcomesingle()
{
	int i;
	system("cls");
	printf("-----------四则运算考试开始---------\n");
	printf("所有%d名考试学生如下:\r\n", allsinglescount);
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allsinglescount; i++)
	{
		printf("%s\t", allsingles[i].name);
	}
	printf("\n--------------------------------------------------\r\n");
	printf("-----------按任意键开始，注意，一旦开始就必须做完依次10个题目---------\n");
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
		printf("-----------下面请学生 %s 答题---------\n",
			allsingles[i].name);
		total += testoneperson();
		allsingles[i].total = total;
	}
}


void displaysingleresult()
{
	int i;
	printf("-----------考试结果---------\n");
	single s = allsingles[0];
	printf("考生姓名：%s 总分：%d 正确率%.1f\n", s.name, s.total, s.total / 100.0);
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
	strcpy(allsingles[0].name, "匿名");
	allsingles[0].total = 0;
	allsinglescount = 1;
	fp = fopen(FILE_BOOK, "a+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BOOK);
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
	//printf("总分=%d\n", total);


	system("pause");
#endif


	while (choice != 0)
	{
		printf("\n\t 心算练习/竞赛系统");
		printf("\n\t 1. 退出");
		printf("\n\t 2. 单人考试");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '1':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			modulesingletest();
			break;

		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	fclose(fp);
	system("pause");
	return 0;
}