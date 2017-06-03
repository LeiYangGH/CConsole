#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_STRLEN 20
#define FILE_GROUP "group.txt"
//��������ķ�Χ
#define MIN 2
#define MAX 9
#define TEST 0
#define NOANSWER 0 //�����û��ش�ֻ��ʾ�� 1����0
#define LESSLOOP 0 //����ѭ������ 1����0
//1
typedef struct group
{
	char gname[MAX_STRLEN];
	char players[MAX_STRLEN][3];
	int score[3];
	int total;
}group;
group allgroups[100];
int allgroupscount = 0;

typedef struct single
{
	char name[MAX_STRLEN];
	int total;
}single;
single allsingles[100];
int allsinglescount = 0;

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

int cmpgroupfunc(const void * b, const void * a)
{
	return ((group*)a)->total - ((group*)b)->total;
}

void displaygroup(group g)
{
	printf("%s\t%s\t%s\t%s\t%d\n", g.gname,
		g.players[0], g.players[1], g.players[2],
		g.total);
}

void displayallgroups()
{
	int i;
	printf("%s\t%s\t%s\t%s\t%s\n",
		"����", "ѡ��1", "ѡ��2", "ѡ��3", "�ܷ�");
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allgroupscount; i++)
	{
		displaygroup(allgroups[i]);
	}
	printf("--------------------------------------------------\r\n");
}

group getgroupfromline(char *line)
{
	char *part;
	int index = 0;
	group g;
	g.total = 0;
	part = strtok(line, " \n");//ͨ��\t���Ų�ֲ�ͬ����
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(g.gname, part);
			break;
		case 2:
			strcpy(g.players[0], part);
			break;
		case 3:
			strcpy(g.players[1], part);
			break;
		case 4:
			strcpy(g.players[2], part);
			break;
		case 5:
			g.total = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return g;
}

void readallgroups()
{
	char line[200];
	FILE *fp = fopen(FILE_GROUP, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_GROUP);
	}
	else
	{
		allgroupscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allgroupscount;
			allgroups[allgroupscount - 1] = getgroupfromline(line);
		}
	}

}
void writeallgroups()
{
	int i;
	group g;
	FILE *fp = fopen(FILE_GROUP, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_GROUP);
		getchar();
		exit(1);
	}
	for (i = 0; i < allgroupscount; i++)
	{
		g = allgroups[i];
		fprintf(fp, "%s %s %s %s %d\n", g.gname,
			g.players[0], g.players[1], g.players[2],
			g.total);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
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

//ʾ����1+2*3/4 n={1,2,3,4} op ={+,*,/} oplen =3
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
#if NOANSWER
	printf("\n");

	return 0;
#else

	re = calc(nums, opindex, oplen);
	scanf("%d", &input);
	if (re == input)
	{

		printf("��ȷ��\n\n");
		return 1;
	}
	else
	{
		printf("������ȷ��Ӧ���� %d\n\n", re);
		return 0;
	}
#endif
}

//ֻ��������
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
			printf("\n�������������������\n1 +\n2 -\n3 *\n4 /:");
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


		printf("\n-----2������������2λ����-------\n");
#if LESSLOOP
		for (i = 0; i < 2; i++)
#else
		for (i = 0; i < 2; i++)
#endif
		{
			if (questionvaroplenandrange(1, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----4������������3λ����-------\n");
#if LESSLOOP
		for (i = 0; i < 2; i++)
#else
		for (i = 0; i < 4; i++)
#endif
		{
			if (questionvaroplenandrange(2, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----6������������4λ����-------\n");
#if LESSLOOP
		for (i = 0; i < 2; i++)
#else
		for (i = 0; i < 6; i++)
#endif
		{
			if (questionvaroplenandrange(3, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----8������������2-4λ����-------\n");
#if LESSLOOP
		for (i = 0; i < 2; i++)
#else
		for (i = 0; i < 8; i++)
#endif		
		{
			if (questionvaroplenandrange(random(1, 3), opidrange))
			{
				total += 5;
			}
		}

		printf("�ܷ�=%d\n", total);
		if (total >= 60)
			break;
		else
		{
			printf("��q�˳�ģ��2���������²���ģ��2:", total);
			fseek(stdin, 0, SEEK_END);
			if (getchar() == 'q')
			{
				break;
			}
		}
	}
	return total;
}

void welcomegroup()
{
	readallgroups();
	system("cls");
	printf("-----------��ӭ����С����---------\n");
	printf("����%d�����С����Ϣ����:\r\n", allgroupscount);
	displayallgroups();
	printf("-----------���������ʼ��ע�⣬һ����ʼ�ͱ��������������ѡ�ֱ���---------\n");
	printf("-----------�����ʾ����Ϣ���Ѿ��з�������ô�±����ķ����Ḳ��ԭ���ķ���---------\n");
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void grouptest()
{
	int i, j, k, total = 0;
	int opidrange[4] = { 0,1,2,3 };
	for (i = 0; i < allgroupscount; i++)
	{
		for (j = 0; j < 3; j++)
		{
			total = 0;
			printf("-----------������ %s С���ѡ�� %s ����---------\n",
				allgroups[i].gname, allgroups[i].players[j]);
#if LESSLOOP
			for (k = 0; k < 2; k++)
#else
			for (k = 0; k < 10; k++)
#endif
			{
				if (questionvaroplenandrange(random(1, 3), opidrange))
				{
					total += 10;
				}
			}
			allgroups[i].total = total;
		}
	}
}

void modulegrouptest()
{
	welcomegroup();
	grouptest();
	printf("����%d�����С��÷�����:\r\n", allgroupscount);
	displayallgroups();
	writeallgroups();
}

void modulereadsortgroup()
{
	readallgroups();
	system("cls");
	printf("----����%d�����С�鰴�ֵܷ���������Ϣ����:----\r\n", allgroupscount);
	qsort(allgroups, allgroupscount, sizeof(group), cmpgroupfunc);
	displayallgroups();
	printf("-----------������������˵�---------\n");
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void readallsingles()
{
	readallgroups();
	int i, j, k, total = 0;
	int opidrange[4] = { 0,1,2,3 };
	for (i = 0; i < allgroupscount; i++)
	{
		for (j = 0; j < 3; j++)
		{
			single s;
			strcpy(s.name, allgroups[i].players[j]);
			s.total = 0;
			allsingles[allsinglescount++] = s;
		}
	}
}

void welcomesingle()
{
	int i;
	system("cls");
	printf("-----------��ӭ���������---------\n");
	printf("����%d��������ѡ������:\r\n", allsinglescount);
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allsinglescount; i++)
	{
		printf("%s\t", allsingles[i].name);
	}
	printf("\n--------------------------------------------------\r\n");
	printf("-----------���������ʼ��ע�⣬һ����ʼ�ͱ��������������ѡ�ֱ���---------\n");
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
		printf("-----------������ѡ�� %s ����---------\n",
			allsingles[i].name);
#if LESSLOOP
		for (k = 0; k < 2; k++)
#else
		for (k = 0; k < 20; k++)
#endif
		{
			if (questionvaroplenandrange(random(1, 3), opidrange))
			{
				total += 5;
			}
		}
		allsingles[i].total = total;
	}
}


void displaysingleresult()
{
	int i;
	printf("-----------��������̭����---------\n");
	for (i = 0; i < allsinglescount; i++)
	{
		if (allsingles[i].total < 60)
			printf("%s\n", allsingles[i].name);
	}
	printf("-----------��������Χ����---------\n");
	for (i = 0; i < allsinglescount; i++)
	{
		if (allsingles[i].total > 90)
			printf("%s\n", allsingles[i].name);
	}
	printf("-----------��������ص�������---------\n");
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void modulesingletest()
{
	readallsingles();
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
		printf("\n\t 2. ģ��2 ���������������");
		printf("\n\t 3. ģ��3 ���������������");
		printf("\n\t 4. ģ��4 ���������������");
		printf("\n\t 5. ģ��5 �ӷ��������ļ���ò���С��ɼ������������");
		printf("\n\t 6. ģ��6 ������");
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
			module2or3(1);
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			module2or3(0);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			modulegrouptest();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			modulereadsortgroup();
			break;
		case '6':
			printf("\n\n��ѡ���� 5\n");
			modulesingletest();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}

	system("pause");
	return 0;
}