#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_QUESTIONS_COUNT 98
#define STUDENT_FILE "student.txt"
#define QUESTION_FILE "test.txt"
#define RESULT_FILE "result.txt"
#define ADMIN "admin"

int use_questions_count = 3;
char username[50] = "";
typedef struct student
{
	char no[20];
	char name[20];
	char idcard[20];
}student;
student allstudents[20];
int allstudentscount = 0;

typedef struct question
{
	char title[50];
	char choices[4][50] = { "","", "", "", };
	int best;//1~4
}question;

question allquestions[100];
int allquestionscount = 0;

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

void login()
{
	printf("\n�������û���:");
	scanf("%s", &username);
	printf("��������û�����:%s", username);
}

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.no, part);
			break;
		case 2:
			strcpy(q.name, part);
			break;
		case 3:
			strcpy(q.idcard, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return q;
}


void readallstudents()
{
	char line[200];
	FILE *fp = fopen(STUDENT_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", STUDENT_FILE);
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
	printf("\n�Ѷ����ļ�!\n");

}

void appendstudent(student re)
{
	FILE *fp = fopen(STUDENT_FILE, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", STUDENT_FILE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%s\t%s\t%s\r\n", re.no, re.name, re.idcard);
	fclose(fp);
	printf("�ѱ���ѧ�����ļ���");
}

int checkstudentexists(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, name))
		{
			return 1;
		}
	}
	return 0;
}

void addstudent(char *no, char *name, char *idcard)
{
	int i;
	student re;
	char teamname[20] = "";
	if (checkstudentexists(name))
	{
		printf("ѧ��%s�Ѵ��ڲ����ظ���ӡ�\n", name);
		return;
	}
	strcpy(re.no, no);
	strcpy(re.name, name);
	strcpy(re.idcard, idcard);
	allstudents[allstudentscount++] = re;
	appendstudent(re);
}
void promptaddstudent()
{
	char no[20] = "";
	char name[20] = "";
	char idcard[20] = "";
	if (!streq(username, ADMIN))
	{
		printf("�����Թ���Ա��¼������ӿ�����Ϣ��");
		return;
	}
	printf("����������Ҫ��ӵ�ѧ�����š����������֤�ţ��������ո񣩣��ո�������س�����:\n");
	scanf("%s%s%s", no, name, idcard);
	fseek(stdin, 0, SEEK_END);
	addstudent(no, name, idcard);
}

void appendquestion(question re)
{
	FILE *fp = fopen(QUESTION_FILE, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", QUESTION_FILE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%d\r\n", re.title, re.choices[0], re.choices[1], re.choices[2], re.choices[3], re.best);
	fclose(fp);
	printf("�ѱ�����⵽�ļ���");
}

int checkquestionexists(char *title)
{
	int i;
	for (i = 0; i < allquestionscount; i++)
	{
		if (streq(allquestions[i].title, title))
		{
			return 1;
		}
	}
	return 0;
}

void addquestion(char *title, char *c1, char *c2, char *c3, char *c4, int best)
{
	int i;
	question re;
	char teamname[20] = "";
	strcpy(re.title, title);
	strcpy(re.choices[0], c1);
	strcpy(re.choices[1], c2);
	strcpy(re.choices[2], c3);
	strcpy(re.choices[3], c4);
	re.best = best;
	allquestions[allquestionscount++] = re;
	appendquestion(re);
}
void promptaddquestion()
{
	char title[20] = "";
	char c1[20] = "";
	char c2[20] = "";
	char c3[20] = "";
	char c4[20] = "";
	int best = 0;
	if (!streq(username, ADMIN))
	{
		printf("�����Թ���Ա��¼������ӿ�����Ϣ��");
		return;
	}
	printf("������Ҫ��ӿ�����⣨�����ո񣩻س�����:\n");
	scanf("%s", title);
	if (checkquestionexists(title))
	{
		printf("����%s�Ѵ��ڲ����ظ���ӡ�\n", title);
		return;
	}
	printf("�����������ĸ�ѡ�ѡ������ո�ѡ��֮���Կո�������س�����:\n");
	scanf("%s%s%s%s", c1, c2, c3, c4);
	printf("���������ţ�1��4���س�����:");
	scanf("%d", &best);
	fseek(stdin, 0, SEEK_END);
	addquestion(title, c1, c2, c3, c4, best);
}

int checklogin()
{
	if (strlen(username) == 0)
	{
		printf("\n���ȵ�¼!");
		return 0;
	}
	else
		return 1;
}

void appendresult(char *name, int allcount, int correctcount)
{
	FILE *fp = fopen(RESULT_FILE, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", RESULT_FILE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%s\t%d\t%d\n", name, allcount, correctcount);
	fclose(fp);
	printf("�ѱ���ɼ����ļ���");
}

void displayallresults()
{
	FILE *fp;
	char line[50];
	if (!checklogin())
	{
		return;
	}
	else if (!streq(username, ADMIN))
	{
		printf("�����Թ���Ա��¼���ܲ�ѯ");
		return;
	}
	fp = fopen(RESULT_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", RESULT_FILE);
		getchar();
		exit(1);
	}
	printf("\n���п��Խ��\n");
	printf("����\t������\t���\n");
	printf("-------------------\n");
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 3)
			continue;
		printf("%s", line);
	}
	printf("-------------------\n");
}

question getquestionfromline(char *line)
{
	char *part;
	int index = 0;
	question q;
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
	FILE *fp = fopen(QUESTION_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", QUESTION_FILE);
		getchar();
		exit(1);
	}
	allquestionscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allquestions[allquestionscount++] = getquestionfromline(line);
	}
	printf("\n�Ѷ������п����ļ�!\n");

}


int random(int min, int max)
{
	return rand() % (max - min) + min;
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

int testonequestion(question *q)
{
	int i, b, r, answer = 0, repeat = -2;
	char o;
	printf("--%s--\n\n", q->title);
	for (i = 0; i < 4; i++)
	{
		printf("%d  %s \n", i + 1, q->choices[i]);
	}
	printf("���������ѡ�1��4�������Իس�����:");

	scanf("%d", &answer);
	if (answer == q->best)
	{
		printf("\t\t\t\t��ȷ��\n");
		return 1;
	}
	else
	{
		printf("--������ȷ���ǣ�%s\n\n", q->choices[q->best - 1]);
		return 0;
	}
}

int testallquestions(int usequestionscount)
{
	int i, score = 0;
	int useids[MAX_QUESTIONS_COUNT] = { 0 };
	generateuseids(allquestionscount, usequestionscount, useids);
	printf("----------��%d��-----------\n\n", usequestionscount);
	for (i = 0; i < usequestionscount; i++)
	{
		score += testonequestion(&allquestions[useids[i]]);
	}
	return score;

}

void inputcountandexam()
{
	int i, usecnt, score = 0;
	if (!checklogin())
	{
		return;
	}
	else if (!checkstudentexists(username))
	{
		printf("��ǰ��¼�û�%sû�Ǽǣ�����ϵ����Ա��", username);
		return;
	}
	printf("\n������Ҫ��ȡ�Ŀ�������(2~%d)�����Իس�����:", allquestionscount - 2);
	scanf("%d", &usecnt);
	srand(time(NULL));
	testallquestions(usecnt);
	printf("----------��%d�⣬���%d��-----------\n\n", usecnt, score);
	appendresult(username, usecnt, score);
}


int main()
{
	char choice = ' ';
	readallstudents();
	readallquestions();
	while (choice != 0)
	{
		printf("\n\n\t---����ϵͳ---\n");
		printf("\t 1. ��¼\n");
		printf("\t 2. ѧ������\n");
		printf("\t 3. �鿴���гɼ�\n");
		printf("\t 4. ��ӿ�����Ϣ\n");
		printf("\t 5. ��ӿ���\n");
		printf("\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
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
			login();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			inputcountandexam();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayallresults();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptaddstudent();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptaddquestion();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
	system("pause");
	return 0;
}