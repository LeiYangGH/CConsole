#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define USE_QUESTIONS_COUNT 3
#define FILE_SEL "file1.txt"
#define FILE_TF "file2.txt"
#define FILE_SCORE "num_name.txt"
typedef struct selectiveqestion
{
	char title[50];
	char choices[4][50] = { "","", "", "", };
	int best;//1~4
	int userchoice;
}selq;

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


selq allselqs[100];
selq useselqs[USE_QUESTIONS_COUNT];
selq sortqs[USE_QUESTIONS_COUNT];
int allselqcnt = 0;

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

void countbygrades()
{
	int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt59 = 0;
	selq q;
	printf("�ַܷ���������ͳ��%d��������\r\n", allselqcnt);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allescorecnt; i++)
	{
		t = allescores[i].score;
		if (t >= 90)
			cnt90++;
		else if (t >= 75 && t <= 89)
			cnt7589++;
		else if (t >= 60 && t <= 74)
			cnt6074++;
		else if (t < 60)
			cnt59++;
	}
	printf("90������:%d��, 75~89:%d��, 60~74:%d��, 60������:%d��\r\n",
		cnt90, cnt7589, cnt6074, cnt59);
	printf("--------------------------------------------\r\n");
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

void testoneselq(selq *q)
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
	q->userchoice = answer;
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

void testallselqs()
{
	int i;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	printf("----------��ѡ��-----------\n\n");
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		useselqs[i] = allselqs[useids[i]];
		testoneselq(&useselqs[i]);
	}
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

int displayselqstestresult()
{
	int i, score = 0;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		printf("\n��%d�⣺%s\n", i + 1, useselqs[i].title);
		printf("��Ĵ𰸣�%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

		if (useselqs[i].userchoice == useselqs[i].best)
		{
			printf("\t\t\t\t��ȷ��\n");
			score += 5;
		}
		else
			printf("--������ȷ���ǣ�%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	}
	printf("\n����ܷ֣�%d\n", score);
	return score;
}

int displaytfqstestresult()
{
	int i, score = 0;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		printf("\n��%d�⣺%s\n", i + 1, useselqs[i].title);
		printf("��Ĵ𰸣�%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

		if (useselqs[i].userchoice == useselqs[i].best)
		{
			printf("\t\t\t\t��ȷ��\n");
			score += 5;
		}
		else
			printf("--������ȷ���ǣ�%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	}
	printf("\n����ܷ֣�%d\n", score);
	return score;
}

void appendscores(int no, char *name, int score)
{
	int i;
	selq q;
	FILE *fp = fopen(FILE_SCORE, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SCORE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%d\t%s\t%d\n", no, name, score);
	fclose(fp);
	printf("����ӳɼ����ļ���");
}

void inputstudentandexam()
{
	int i, no, score, save;
	char name[50] = "";
	srand(time(NULL));
	printf("\n������Ҫ����ѧ��(1~100)�����Իس�����:");
	scanf("%d", &no);
	printf("\n�����뿼�����������ܴ��ո�Tab��س��������Իس�����:");
	scanf("%s", name);
	readallselqs();
	readalltfqs();
	testallselqs();
	testalltfqs();
	score = displayselqstestresult() + displaytfqstestresult();
	printf("\n��Ŀȫ�����꣬��ѡ���Ƿ񱣴�ɼ���ѡ1���棬�����Լ�¼������Իس�����:");
	scanf("%d", &save);
	if (save == 1)
	{
		appendscores(no, name, score);
	}
	printf("\n\nҪѡ�����˵����밴�����\n");
	system("pause");
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

void escoresstatic()
{
	readallescores();
	sortanddisplayallescores();
	countbygrades();
	avehighlowescores();
}

int main()
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        ����ϵͳ          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. ����ѧ����Ϣ������\n");
		printf("\n\t 2. ͳ���ѿ���ѧ���ɼ�\n");
		printf("\n\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
		scanf("%1[012]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			inputstudentandexam();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			escoresstatic();
			printf("\n\nҪѡ�����˵����밴�����\n");
			system("pause");
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	system("pause");
	return 0;
}