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

//字符串转整数
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
		printf("\n打开文件%s失败!", FILE_SEL);
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
	printf("\n已读入文件!\n");

}

void readalltfqs()
{
	char line[200];
	FILE *fp = fopen(FILE_SEL, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SEL);
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
	printf("\n已读入文件!\n");

}

void readallescores()
{
	char line[200];
	FILE *fp = fopen(FILE_SCORE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SCORE);
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
	printf("\n已读入文件!", FILE_SEL);

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
	printf("所有成绩按学好排序后如下\r\n");
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
	printf("总分分数段人数统计%d分数如下\r\n", allselqcnt);
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
	printf("90分以上:%d人, 75~89:%d人, 60~74:%d人, 60分以下:%d人\r\n",
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
	printf("请输入你的选项（1～4），并以回车结束:");

	scanf("%d", &answer);
	q->userchoice = answer;
}

void testonetfq(tfq *q)
{
	int i, b, r, answer = 0, repeat = -2;
	char o;
	printf("--%s--\n\n", q->title);
	printf("请输入你的判断（0表是错误，1表示正确），并以回车结束:");
	scanf("%d", &answer);
	q->userchoice = answer;
}

void testallselqs()
{
	int i;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	printf("----------单选题-----------\n\n");
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
	printf("----------判断题-----------\n\n");
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
		printf("\n第%d题：%s\n", i + 1, useselqs[i].title);
		printf("你的答案：%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

		if (useselqs[i].userchoice == useselqs[i].best)
		{
			printf("\t\t\t\t正确！\n");
			score += 5;
		}
		else
			printf("--错误，正确答案是：%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	}
	printf("\n你的总分：%d\n", score);
	return score;
}

int displaytfqstestresult()
{
	int i, score = 0;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		printf("\n第%d题：%s\n", i + 1, useselqs[i].title);
		printf("你的答案：%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

		if (useselqs[i].userchoice == useselqs[i].best)
		{
			printf("\t\t\t\t正确！\n");
			score += 5;
		}
		else
			printf("--错误，正确答案是：%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	}
	printf("\n你的总分：%d\n", score);
	return score;
}

void appendscores(int no, char *name, int score)
{
	int i;
	selq q;
	FILE *fp = fopen(FILE_SCORE, "a");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SCORE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%d\t%s\t%d\n", no, name, score);
	fclose(fp);
	printf("已添加成绩到文件。");
}

void inputstudentandexam()
{
	int i, no, score, save;
	char name[50] = "";
	srand(time(NULL));
	printf("\n请输入要考生学号(1~100)，并以回车结束:");
	scanf("%d", &no);
	printf("\n请输入考生姓名，不能带空格、Tab或回车符，并以回车结束:");
	scanf("%s", name);
	readallselqs();
	readalltfqs();
	testallselqs();
	testalltfqs();
	score = displayselqstestresult() + displaytfqstestresult();
	printf("\n题目全部做完，请选择是否保存成绩？选1保存，否则考试记录清除。以回车结束:");
	scanf("%d", &save);
	if (save == 1)
	{
		appendscores(no, name, score);
	}
	printf("\n\n要选其他菜单，请按任意键\n");
	system("pause");
}

void avehighlowescores()
{
	int i;
	float sum = 0;
	qsort(allescores, allescorecnt, sizeof(escore), cmpbyscore);
	for (i = 0; i < allescorecnt; i++)
		sum += allescores[i].score;
	printf("%s\t%d\r\n", "最高", allescores[allescorecnt - 1].score);
	printf("%s\t%d\r\n", "最低", allescores[0].score);
	printf("%s\t%.1f\r\n", "平均", sum / (float)allescorecnt);
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
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        考试系统          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. 输入学生信息并考试\n");
		printf("\n\t 2. 统计已考试学生成绩\n");
		printf("\n\t 0. 退出");
		printf("\n\n 请选择: ");
		scanf("%1[012]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			inputstudentandexam();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			escoresstatic();
			printf("\n\n要选其他菜单，请按任意键\n");
			system("pause");
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	system("pause");
	return 0;
}