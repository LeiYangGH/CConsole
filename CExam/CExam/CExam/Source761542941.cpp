#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define TEST 0
//#define USE_QUESTIONS_COUNT 20
#define MAX_QUESTIONS_COUNT 20
#define FILE_SEL "file1.txt"
#define RESULT_FILE "result.txt"
#define FILE_SCORE "num_name.txt"
#define ADMIN "admin"

int use_questions_count = 3;
char username[50] = "";

typedef struct selectiveqestion
{
	char title[50];
	char choices[4][50] = { "","", "", "", };
	int best;//1~4
	//int userchoice;
}selq;

//typedef struct examscore
//{
//	int no;
//	char name[50];
//	int score;
//}escore;


selq allselqs[100];
//selq useselqs[MAX_QUESTIONS_COUNT];
//selq sortqs[MAX_QUESTIONS_COUNT];
int allselqcnt = 0;

//escore allescores[100];
//int allescorecnt = 0;

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

//���µĴ�����׷�ӵ��ļ�ĩβ
void appendresult(char *name, int allcount, int correctcount)
{
	FILE *fp = fopen(RESULT_FILE, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", RESULT_FILE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%s\t%d\t%d\n", name, allcount, allcount);
	fclose(fp);
	printf("�ѱ���ɼ����ļ���");
}

selq getselqfromline(char *line)
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



void readallselqs()
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
		allselqs[allselqcnt++] = getselqfromline(line);
	}
	printf("\n�Ѷ����ļ�!\n");

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

int testoneselq(selq *q)
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

int testallselqs(int usequestionscount)
{
	int i, score = 0;
	int useids[MAX_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, usequestionscount, useids);
	printf("----------��%d��-----------\n\n", usequestionscount);
	for (i = 0; i < usequestionscount; i++)
	{
		score += testoneselq(&allselqs[useids[i]]);
	}
	return score;

}

void login()
{
	printf("\n�������û���:");
	scanf("%s", &username);
}

int checklogin()
{
	if (strlen(username) == 0)
		return 0;
	else
		return 1;
}

void inputcountandexam()
{
	int i, usecnt, score = 0;
	if (!checklogin())
	{
		printf("\n���ȵ�¼!");
		return;
	}
	printf("\n������Ҫ��ȡ�Ŀ�������(2~%d)�����Իس�����:", allselqcnt - 2);
	scanf("%d", &usecnt);
	srand(time(NULL));

	//printf("\n�����뿼�����������ܴ��ո�Tab��س��������Իس�����:");
	//scanf("%s", name);
	readallselqs();
	testallselqs(usecnt);
	printf("----------��%d�⣬���%d��-----------\n\n", usecnt, score);
	appendresult(username, usecnt, score);
	//score = displayselqstestresult();
	//printf("\n��Ŀȫ�����꣬��ѡ���Ƿ񱣴�ɼ���ѡ1���棬�����Լ�¼������Իس�����:");
	//scanf("%d", &save);
	//if (save == 1)
	//{
	//	appendscores(no, name, score);
	//}
}





int main()
{
#if TEST
	strcpy(name, "ly");
	inputstudentandexam();
#else
	char choice = ' ';
	while (choice != 0)
	{
		printf("\n\t---����ϵͳ---\n");
		printf("\t 1. ��¼\n");
		printf("\t 2. ѧ������\n");
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
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			// 
			//	break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			// 
			//	break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
#endif // TEST
	system("pause");
	return 0;
}