#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <conio.h>
#include <time.h>
#define USE_QUESTIONS_COUNT 3
#define FILE_GROUP "group.txt"
 
#define FILE_SCORE "num_name.txt"
#define MIN 2
#define MAX 9
#define TEST 0

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

int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int randomminmax()
{
	return rand() % (MAX - MIN + 1) + MIN;
}

void generateuseids(int allcnt, int usecnt, int useids[])
{
	int i;
	int r, ri, ucnt = 0, tmp, top;
	int allids[100];
	for (i = 0; i < allcnt; i++)
	{
		allids[i] = i;
	}
	while (ucnt < usecnt)
	{
		ri = random(0, allcnt - ucnt);
		useids[ucnt++] = r = allids[ri];
		top = allcnt - ucnt - 1;
		if (r < top)
		{
			allids[r] = allids[top];
		}
	}
}

//1+2*3/4 n={1,2,3,4} op ={+,*,/} oplen =3
int calc(int n[], int opindex[], int oplen)
{
	int i, re = n[0];
	for (i = 0; i < oplen; i++)
	{
		re = alloprators[opindex[i]].op(re, n[i + 1]);
	}
	return re;
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

int testone(int nums[], int opindex[], int oplen)
{
	int i, re, input;
	char exp[50] = "";
	concatstringandint(exp, nums[0]);
	for (i = 0; i < oplen; i++)
	{
		strcat(exp, alloprators[opindex[i]].str);
		concatstringandint(exp, nums[i + 1]);
	}
	printf("%s =? ", exp);
#if TEST
	printf("\n");

	return 0;
#else

	re = calc(nums, opindex, oplen);
	scanf("%d", &input);
	if (re == input)
	{

		printf("正确！\n\n");
		return 1;
	}
	else
	{
		printf("错误！正确答案应该是 %d\n\n", re);
		return 0;
	}
#endif
}
void testop()
{
	int nums[] = { 1,2,3,4 };
	int opindex[] = { 1,2,3 };
	int len = 3;
	int c = calc(nums, opindex, len);
	printf("c=%d\n", c);
	testone(nums, opindex, len);
}

int questionvaroplenandrange(int oplen, int opidrange[])
{
	int i;
	int nums[4];
	int opindex[4];
	nums[0] = randomminmax();
	nums[1] = randomminmax();
	nums[2] = randomminmax();
	nums[3] = randomminmax();
	opindex[0] = opidrange[random(0, 3)];
	opindex[1] = opidrange[random(0, 3)];
	opindex[2] = opidrange[random(0, 3)];
	opindex[3] = opidrange[random(0, 3)];
	return testone(nums, opindex, oplen);
}

int module2or3(int issingleop)
{
	int i, op = 1, total = 0;
	int opidrange[4];
	while (1)
	{
		if (issingleop)
		{
			printf("\n请输入运算符（整数）\n1 +\n2 -\n3 *\n4 /:");
			scanf("%d", &op);
			opidrange[0] = op - 1;
			opidrange[1] = op - 1;
			opidrange[2] = op - 1;
			opidrange[3] = op - 1;
		}
		else
		{
			opidrange[0] = 0;
			opidrange[1] = 1;
			opidrange[2] = 2;
			opidrange[3] = 3;
		}


		printf("\n-----2题运算对象均是2位整数-------\n");
		for (i = 0; i < 2; i++)
		{
			if (questionvaroplenandrange(1, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----4题运算对象均是3位整数-------\n");
		for (i = 0; i < 4; i++)
		{
			if (questionvaroplenandrange(2, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----6题运算对象均是4位整数-------\n");
		for (i = 0; i < 6; i++)
		{
			if (questionvaroplenandrange(3, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----8题运算对象均是2-4位整数-------\n");
		for (i = 0; i < 8; i++)
		{
			if (questionvaroplenandrange(random(1, 3), opidrange))
			{
				total += 5;
			}
		}

		printf("总分=%d\n", total);
		if (total >= 60)
			break;
		else
		{
			printf("按q退出模块2，否则重新测试模块2:", total);
			fseek(stdin, 0, SEEK_END);
			if (getchar() == 'q')
			{
				break;
			}
		}
	}
	return total;
}

int main()
{
	int i, total = 0;
	char choice = -1;
	srand(time(NULL));
	init();
#if TEST
	int opsids[] = { 0,1,2,3 };
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
	total = module2or3(0);
	printf("总分=%d\n", total);

 
	system("pause");
#endif


	while (choice != 0)
	{
		printf("\n\t 心算练习/竞赛系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 模块2 单运算符四则运算");
		printf("\n\t 2. 模块3 多运算符四则运算");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
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
			module2or3(1);
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			module2or3(0);
			break;
			//case '3':
			//	printf("\n\n你选择了 3\n");
			//	break;
			//case '4':
			//	printf("\n\n你选择了 4\n");
			//	break;
			//case '5':
			//	printf("\n\n你选择了 5\n");
			//	break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}

	system("pause");
	return 0;
}