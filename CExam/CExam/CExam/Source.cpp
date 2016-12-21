#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#define TEST_QUESTIONS_COUNT 3

#define FILE_SEL "file1.txt"
#define FILE_TF "file2.txt"
#define FILE_SCORE "num_name.txt"
#define FORMATNET "%s\t%s\t%s\t%s\t%s\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_NET q.title, q.choices[0],  q.choices[1], q.choices[2], q.choices[3], q.best
typedef struct selectiveqestion
{
	char title[50];
	char choices[4][50] = { "","", "", "", };
	int best;//1~4
	int userchoice;
}selq;

selq allselqs[100];
selq useselqs[100];
selq sortqs[100];
int allselqcnt = 0;

typedef struct truefalseqestion
{
	char title[50];
	int best;//0~1
	int userchoice;
}tfq;

selq alltfqs[100];
int alltfqcnt = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "q.txt";
selq *head;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

int tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void displayquestion(selq q)
{
	printf("\r\n");
	printf(FORMATNET, STU_MEMBERS_NET);
}

void displayallquestions()
{
	int i;
	printf("����%d��������\r\n", allselqcnt);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allselqcnt; i++)
	{
		displayquestion(allselqs[i]);
	}
	printf("--------------------------------------------\r\n");
}

selq getquestionfromline(char *line)
{
	char *part;
	int index = 0;
	selq q;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.title, part);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			strcpy(q.choices[index - 2], part);
			break;
		case 6:
			q.best = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return q;
}

void readallquestions()
{
	char line[200];
	FILE *fp = fopen(FILE_SEL, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SEL);
		getchar();
		exit(1);
	}
	allselqcnt = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allselqs[allselqcnt++] = getquestionfromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_SEL);

}

int cmpfunc(const void * a, const void * b)
{
	return 0;// ((selectiveq*)a)->total - ((selectiveq*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allselqcnt; i++)
	{
		sortqs[i] = allselqs[i];
	}
	qsort(sortqs, allselqcnt, sizeof(selq), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("���������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allselqcnt; i++)
	{
		displayquestion(sortqs[i]);
	}
	printf("--------------------------------------------\r\n");
}



void countbygrades()
{
	int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt60 = 0;
	selq q;
	printf("�ַܷ���������ͳ��%d��������\r\n", allselqcnt);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allselqcnt; i++)
	{
		t = 0;//allquestions[i].average;
		if (t >= 90)
			cnt90++;
		else if (t >= 75 && t <= 89)
			cnt7589++;
		else if (t >= 60 && t <= 74)
			cnt6074++;
		else if (t < 60)
			cnt60++;
	}
	printf("90������:%d��, 75~89:%d��, 60~74:%d��, 60������:%d��\r\n",
		cnt90, cnt7589, cnt6074, cnt60);
	printf("--------------------------------------------\r\n");
}



float ave()
{
	int i;
	float sum = 0;
	/*for (i = 0; i < allquestionscount; i++)
		sum += allquestions[i].total;*/
	return sum / (float)allselqcnt;
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("����������:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

void searchtotalbyname(char *name)
{
	int i;
	/*for (i = 0; i < allquestionscount; i++)
		if (strcmp(name, allquestions[i].name) == 0)
		{
			displayquestion(allquestions[i]);
			return;
		}*/
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	searchtotalbyname(name);
	return strcmp(name, "q");
}



void searchtotalbyno(int no)
{
	int i;
	/*for (i = 0; i < allquestionscount; i++)
		if (allquestions[i].no == no)
		{
			displayquestion(allquestions[i]);
			return;
		}*/
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

void promptsearchtotalbyno()
{
	int no;
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%d", &no);
	searchtotalbyno(no);
}

//����ɼ���Ϣ
void inputname(char str[])
{
	printf("����������(2-45���ַ�)�����ܴ��ո�Tab��س���:");
	scanf("%s", str);
	printf("�����������ΪΪ %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("���������1��100:");
		scanf("%d", &n);
	}
	return n;
}

//void createsamplequestions()
//{
//	FILE *fp = fopen(file, "wb");
//	printf("����ʾ���ɼ�����...");
//	if (fp == NULL)
//	{
//		printf("\nerror on open file!");
//		getchar();
//		exit(1);
//	}
//	fprintf(fp, FORMATNET, 33, "Smile", 13, 83, 63, 93);
//	fprintf(fp, FORMATNET, 44, "Lukas", 14, 84, 64, 94);
//	fprintf(fp, FORMATNET, 55, "Shawn", 15, 85, 65, 95);
//	fprintf(fp, FORMATNET, 22, "Tony", 12, 82, 62, 92);
//	fprintf(fp, FORMATNET, 11, "Flex", 11, 81, 61, 91);
//	fclose(fp);
//	printf("5��ʾ���ɼ������ѱ��浽question.txt��\n");
//}

void writeallquestions()
{
	int i;
	selq q;
	FILE *fp = fopen(FILE_SEL, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SEL);
		getchar();
		exit(1);
	}


	for (i = 0; i < allselqcnt; i++)
	{
		q = allselqs[i];
		fprintf(fp, FORMATNET, STU_MEMBERS_NET);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}

void addquestion(int no, char name[], int math, int english, int chinese, int c)
{
	selq q;
	/*q.no = no;
	strcpy(q.name, name);
	q.math = math;
	q.english = english;
	q.chinese = chinese;
	q.c = c;*/
	allselqs[allselqcnt++] = q;
}

void calcanddisplaytotalandaverage()
{
	int i;
	selq q;
	printf("���и����ܷ֡�ƽ��������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allselqcnt; i++)
	{
		q = allselqs[i];
		//allquestions[i].total = q.total = calctotal(q.math, q.english, q.chinese, q.c);
		//allquestions[i].average = q.average = calcave(q.total);
		//printf("%d\t%s\t%d\t%.1f\r\n", q.no, q.name, q.total, q.average);
	}
	printf("--------------------------------------------\r\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allselqcnt; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("��Ŀ:%s ƽ����%.1f�������ʰٷ�֮%.1f���������ʰٷ�֮%.1f\r\n", subuject,
		(sum / (float)allselqcnt),
		(1 - below60 / (float)allselqcnt)*100.0f,
		(below60 / (float)allselqcnt)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	int i, sum = 0, below60 = 0;
	int scores[100];
	selq q;
	printf("���п�Ŀ�ɼ�ͳ������\r\n");
	printf("--------------------------------------------\r\n");

	/*for (i = 0; i < allquestionscount; i++)
	{
		scores[i] = allquestions[i].c;
	}*/
	calcanddisplaysubject("C����", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddquestion()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n������ѧ��\n");
	scanf("%d", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n��������ѧ��Ӣ����ġ�c���Գɼ������������ո����\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addquestion(no, name, math, english, chinese, c);
	printf("��ɵ�%d�����¼��!\r\n", allselqcnt);
}

int repeatscore[3] = { 10,7,5 };

int random(int min, int max)
{
	return rand() % (max - min) + min;
}

int testone(int qid)
{
	int a, b, r, answer = 0, repeat = -2;
	char o;
	a = random(15, 25);
	b = random(1, 15);
	o = a % 2;
	printf("-----Test %d----\n\n", qid + 1);
	printf("%d %c %d =\n", a, o ? '+' : '-', b);
	r = o ? a + b : a - b;
	while (++repeat < 2 && answer != r)
	{
		printf("Input your answer:");
		scanf("%d", &answer);
	}
	if (answer == r)
		return repeatscore[repeat];
	else
		return 0;
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
		printf("r=%d\t", r);
	}
	printf("\n", r);
}

int main()
{
	int i;
	int allcnt = 20;
	int usecnt = 10;
	int useids[10] = { 0 };
	srand(time(NULL));
	/*readallquestions();
	displayallquestions();*/

	for (i = 0; i < 20; i++)
	{
		generateuseids(allcnt, usecnt, useids);
	}


	system("pause");
	return 0;
}