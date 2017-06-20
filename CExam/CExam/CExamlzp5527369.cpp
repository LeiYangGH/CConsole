#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define FILE_single "single.txt"
#define MAX_STRLEN 20
//��������ķ�Χ
#define MIN 1
#define MAX 100
#define TEST 0
#define NOANSWER 0 //�����û��ش�ֻ��ʾ�� 1����0
#define LESSLOOP 1 //����ѭ������ 1����0
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


int cmpfunc(const void * b, const void * a)
{
	return ((single*)a)->total - ((single*)b)->total;
}

void displaysingle(single s)
{
	printf("%s\t%d\n", s.name, s.total);
}

void displayallsingles()
{
	int i;
	qsort(allsingles, allsinglescount, sizeof(single), cmpfunc);
	printf("����%dλ�����ɼ�����\r\n", allsinglescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsinglescount; i++)
	{
		displaysingle(allsingles[i]);
	}
	printf("--------------------------------------------\r\n");
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


int getidexbyname(char name[50])
{
	int i;
	for (i = 0; i < allsinglescount; i++)
	{
		if (streq(allsingles[i].name, name))
			return i;
	}
	return -1;//û�ҵ�
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
	printf("-----------���������ʼ��ע�⣬һ����ʼ�ͱ�����������10����Ŀ---------\n");
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void singletest(int i)
{
	int  j, k, total = 0;
	//int opidrange[4] = { 0,1,2,3 };
	printf("-----------������ѧ�� %s ����---------\n",
		allsingles[i].name);
	total += testoneperson();
	allsingles[i].total = total;
}


void displaysingleresult(int i)
{
	printf("-----------���Խ��---------\n");
	single s = allsingles[i];
	printf("����������%s �ܷ֣�%d ��ȷ��%.1f\n", s.name, s.total, s.total / 100.0);
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
}

void modulesingletest()
{
	welcomesingle();
	singletest(0);
	displaysingleresult(0);
}

void modulemultitest()
{
	int i;
	char name[20];
	printf("\n�����뿼�����������ظ�������հ�ȡ����:\n");
	//scanf("%s", name);
	fseek(stdin, 0, SEEK_END);
	fgets(name, 80, stdin);
	name[strcspn(name, "\r\n")] = 0;//ɾ��ĩβ�Ļس����з�
	if (streq(name, ""))
	{
		printf("����Ŀ���Ϊ�գ�ȡ������\n");
		return;
	}
	i = getidexbyname(name);
	if (i >= 0)
	{
		if (allsingles[i].total > 0)
		{
			printf("����%s�Ѿ������������ظ�����\n", name);
			return;
		}
	}
	else
	{
		single s;
		strcpy(s.name, name);
		s.total = 0;
		allsingles[allsinglescount++] = s;
	}
	i = getidexbyname(name);
	welcomesingle();
	singletest(i);
	displaysingleresult(i);
}

void searchbyname(char name[20])
{
	int i, found = 0;
	for (i = 0; i < allsinglescount; i++)
		if (strstr(allsingles[i].name, name) != NULL)
		{
			displaysingle(allsingles[i]);
			found = 1;
		}
	if (!found)
		printf("û�ҵ���Ӧ��������Ϣ��\r\n");
}

void promptsearchbyname()
{
	char name[20];
	printf("������Ҫ���ҵĿ�������:");
	scanf("%s", name);
	searchbyname(name);
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
	fp = fopen(FILE_single, "a+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_single);
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
		printf("\n\t 2. ���ˣ�����������");
		printf("\n\t 3. ���˿���");
		printf("\n\t 4. ���˿��Ժ��ܷ��ɸߵ������");
		printf("\n\t 5. ��ѧ��������ѯ�������");
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
		case '3':
			printf("\n\n��ѡ���� 3\n");
			modulemultitest();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallsingles();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptsearchbyname();
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