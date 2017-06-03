#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <conio.h>
#include <time.h>
#define USE_QUESTIONS_COUNT 3
#define FILE_SEL "file1.txt"
#define FILE_TF "file2.txt"
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
//int(*op[4])(int a, int b) = { add ,minus ,multiply ,devide };



typedef struct truefalseqestion
{
	char title[50];
	int best;//0~1
	int userchoice;
}tfq;


typedef struct examscore
{
	int no;
	char name[50];
	int score;
}escore;




escore allescores[100];
int allescorecnt = 0;

tfq alltfqs[100];
tfq usetfqs[USE_QUESTIONS_COUNT];
int alltfqcnt = 0;

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

tfq gettfqfromline(char *line)
{
	char *part;
	int index = 0;
	tfq q;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.title, part);
			break;
		case 2:
			q.best = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return q;
}

escore getescorefromline(char *line)
{
	char *part;
	int index = 0;
	escore q;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			q.no = toint(part);
			break;
		case 2:
			strcpy(q.name, part);
			break;
		case 3:
			q.score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return q;
}



void readalltfqs()
{
	char line[200];
	FILE *fp = fopen(FILE_SEL, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SEL);
		getchar();
		exit(1);
	}
	alltfqcnt = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		alltfqs[alltfqcnt++] = gettfqfromline(line);
	}
	printf("\n�Ѷ����ļ�!\n");

}

void readallescores()
{
	char line[200];
	FILE *fp = fopen(FILE_SCORE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SCORE);
		getchar();
		exit(1);
	}
	allescorecnt = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allescores[allescorecnt++] = getescorefromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_SEL);

}

int cmpbyno(const void * a, const void * b)
{
	return  ((escore*)a)->no - ((escore*)b)->no;
}

int cmpbyscore(const void * a, const void * b)
{
	return  ((escore*)a)->score - ((escore*)b)->score;
}

void sortanddisplayallescores()
{
	int i;
	qsort(allescores, allescorecnt, sizeof(escore), cmpbyno);
	printf("���гɼ���ѧ�����������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allescorecnt; i++)
	{
		printf("%d  %s %d\n", allescores[i].no, allescores[i].name, allescores[i].score);
	}
	printf("--------------------------------------------\r\n");
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


void testonetfq(tfq *q)
{
	int i, b, r, answer = 0, repeat = -2;
	char o;
	printf("--%s--\n\n", q->title);
	printf("����������жϣ�0���Ǵ���1��ʾ��ȷ�������Իس�����:");
	scanf("%d", &answer);
	q->userchoice = answer;
}


void testalltfqs()
{
	int i;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(alltfqcnt, USE_QUESTIONS_COUNT, useids);
	printf("----------�ж���-----------\n\n");
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		usetfqs[i] = alltfqs[useids[i]];
		testonetfq(&usetfqs[i]);
	}
}

int displaytfqstestresult()
{
	int i, score = 0;
	//int useids[USE_QUESTIONS_COUNT] = { 0 };
	//generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	//for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	//{
	//	printf("\n��%d�⣺%s\n", i + 1, useselqs[i].title);
	//	printf("��Ĵ𰸣�%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

	//	if (useselqs[i].userchoice == useselqs[i].best)
	//	{
	//		printf("\t\t\t\t��ȷ��\n");
	//		score += 5;
	//	}
	//	else
	//		printf("--������ȷ���ǣ�%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	//}
	//printf("\n����ܷ֣�%d\n", score);
	return score;
}


void inputstudentandexam()
{
	//int i, no, score, save;
	//char name[50] = "";
	//srand(time(NULL));
	//printf("\n������Ҫ����ѧ��(1~100)�����Իس�����:");
	//scanf("%d", &no);
	//printf("\n�����뿼�����������ܴ��ո�Tab��س��������Իس�����:");
	//scanf("%s", name);
	//readallselqs();
	//readalltfqs();
	//testallselqs();
	//testalltfqs();
	//score = displayselqstestresult() + displaytfqstestresult();
	//printf("\n��Ŀȫ�����꣬��ѡ���Ƿ񱣴�ɼ���ѡ1���棬�����Լ�¼������Իس�����:");
	//scanf("%d", &save);
	//if (save == 1)
	//{
	//	appendscores(no, name, score);
	//}
	//printf("\n\nҪѡ�����˵����밴�����\n");
	//system("pause");
}

void avehighlowescores()
{
	int i;
	float sum = 0;
	qsort(allescores, allescorecnt, sizeof(escore), cmpbyscore);
	for (i = 0; i < allescorecnt; i++)
		sum += allescores[i].score;
	printf("%s\t%d\r\n", "���", allescores[allescorecnt - 1].score);
	printf("%s\t%d\r\n", "���", allescores[0].score);
	printf("%s\t%.1f\r\n", "ƽ��", sum / (float)allescorecnt);
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
		for (i = 0; i < 2; i++)
		{
			if (questionvaroplenandrange(1, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----4������������3λ����-------\n");
		for (i = 0; i < 4; i++)
		{
			if (questionvaroplenandrange(2, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----6������������4λ����-------\n");
		for (i = 0; i < 6; i++)
		{
			if (questionvaroplenandrange(3, opidrange))
			{
				total += 5;
			}
		}

		printf("\n-----8������������2-4λ����-------\n");
		for (i = 0; i < 8; i++)
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
	printf("�ܷ�=%d\n", total);

 
	system("pause");
#endif


	while (choice != 0)
	{
		printf("\n\t ������ϰ/����ϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ģ��2 ���������������");
		printf("\n\t 2. ģ��3 ���������������");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
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
			module2or3(1);
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			module2or3(0);
			break;
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			//	break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			//	break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}

	system("pause");
	return 0;
}