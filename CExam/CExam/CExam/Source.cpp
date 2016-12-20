#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#define QESTIONS_COUNT 3

#define FILE_STU "stu.txt"
//#define FILE_STU "sample.txt"
//#define FILE_BEST "best.txt"
//#define FILE_SCORES "scores.txt"
//#define FILE_ANALYSIS "analysis.txt"
#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c, stu.total, stu.average
#define STU_MEMBERS_NET stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c
typedef struct student
{
	int no;
	char name[50];
	int math;
	int english;
	int chinese;
	int c;
	int total;
	float average;
}student;

student allstudents[100];
student sortstudents[100];
int allstudentscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "stu.txt";
student *head;

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

void displaystudent(student stu)
{
	printf("\r\n");
	printf(FORMATNET, STU_MEMBERS_NET);
}

void displayallstudents()
{
	int i;
	printf("����%d��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			stu.no = toint(part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.math = toint(part);
			break;
		case 4:
			stu.english = toint(part);
			break;
		case 5:
			stu.chinese = toint(part);
			break;
		case 6:
			stu.c = toint(part);
			break;
		case 7:
			stu.total = toint(part);
			break;
		case 8:
			stu.average = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_STU);

}

int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		sortstudents[i] = allstudents[i];
	}
	qsort(sortstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("���������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(sortstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}



void countbygrades()
{
	int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt60 = 0;
	student stu;
	printf("�ַܷ���������ͳ��%d��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].average;
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
	for (i = 0; i < allstudentscount; i++)
		sum += allstudents[i].total;
	return sum / (float)allstudentscount;
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
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			displaystudent(allstudents[i]);
			return;
		}
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
	for (i = 0; i < allstudentscount; i++)
		if (allstudents[i].no == no)
		{
			displaystudent(allstudents[i]);
			return;
		}
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

void createsamplestudents()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMATNET, 33, "Smile", 13, 83, 63, 93);
	fprintf(fp, FORMATNET, 44, "Lukas", 14, 84, 64, 94);
	fprintf(fp, FORMATNET, 55, "Shawn", 15, 85, 65, 95);
	fprintf(fp, FORMATNET, 22, "Tony", 12, 82, 62, 92);
	fprintf(fp, FORMATNET, 11, "Flex", 11, 81, 61, 91);
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽student.txt��\n");
}

int getstudentidexbyid(int no)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (b.no == no)
			return i;
	}
}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
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

void addstudent(int no, char name[], int math, int english, int chinese, int c)
{
	student stu;
	stu.no = no;
	strcpy(stu.name, name);
	stu.math = math;
	stu.english = english;
	stu.chinese = chinese;
	stu.c = c;
	allstudents[allstudentscount++] = stu;
}

void calcanddisplaytotalandaverage()
{
	int i;
	student stu;
	printf("���и����ܷ֡�ƽ��������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		allstudents[i].total = stu.total = calctotal(stu.math, stu.english, stu.chinese, stu.c);
		allstudents[i].average = stu.average = calcave(stu.total);
		printf("%d\t%s\t%d\t%.1f\r\n", stu.no, stu.name, stu.total, stu.average);
	}
	printf("--------------------------------------------\r\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("��Ŀ:%s ƽ����%.1f�������ʰٷ�֮%.1f���������ʰٷ�֮%.1f\r\n", subuject,
		(sum / (float)allstudentscount),
		(1 - below60 / (float)allstudentscount)*100.0f,
		(below60 / (float)allstudentscount)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	int i, sum = 0, below60 = 0;
	int scores[100];
	student stu;
	printf("���п�Ŀ�ɼ�ͳ������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].math;
	}
	calcanddisplaysubject("��ѧ", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].english;
	}
	calcanddisplaysubject("Ӣ��", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].chinese;
	}
	calcanddisplaysubject("����", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].c;
	}
	calcanddisplaysubject("C����", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddstudent()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n������ѧ��\n");
	scanf("%d", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n��������ѧ��Ӣ����ġ�c���Գɼ������������ո����\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addstudent(no, name, math, english, chinese, c);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
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

void showresult(int score)
{
	if (score >= 90)
		printf("SMART!\n");
	else if (score >= 80 && score < 90)
		printf("GOOD\n");
	else if (score >= 70 && score < 80)
		printf("OK\n");
	else if (score >= 60 && score < 70)
		printf("PASS\n");
	else if (score < 60)
		printf("TRY AGAIN!\n");
}

int main()
{
	int t, m, first, score = 0;
	srand(time(NULL));
	for (t = 0; t < QESTIONS_COUNT; t++)
	{
		score += testone(t);
	}
	printf("---------\n");
	printf("%d\n", score);
	showresult(score);
	system("pause");
	return 0;
}