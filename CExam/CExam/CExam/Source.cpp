#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#define USE_QUESTIONS_COUNT 3

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
selq sortqs[USE_QUESTIONS_COUNT];
int allselqcnt = 0;

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


selq alltfqs[100];
int alltfqcnt = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "q.txt";
selq *head;

//字符串转整数
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
	printf("所有%d分数如下\r\n", allselqcnt);
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


void readallquestions()
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
		allselqs[allselqcnt++] = getquestionfromline(line);
	}
	printf("\n已读入文件!");

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



int cmpfunc(const void * a, const void * b)
{
	return  ((escore*)a)->no - ((escore*)b)->no;
}

void sortanddisplayallescores()
{
	int i;
	qsort(allescores, allescorecnt, sizeof(escore), cmpfunc);
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
	int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt60 = 0;
	selq q;
	printf("总分分数段人数统计%d分数如下\r\n", allselqcnt);
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
	printf("90分以上:%d人, 75~89:%d人, 60~74:%d人, 60分以下:%d人\r\n",
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
		printf("请输入姓名:");
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
	printf("没找到对应学生的信息。\r\n");
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
	printf("没找到对应学生的信息。\r\n");
}

void promptsearchtotalbyno()
{
	int no;
	printf("请输入要查询的学号:");
	scanf("%d", &no);
	searchtotalbyno(no);
}

//输入成绩信息
void inputname(char str[])
{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	scanf("%s", str);
	printf("您输入的姓名为为 %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("请输入分数1～100:");
		scanf("%d", &n);
	}
	return n;
}



void writeallquestions()
{
	int i;
	selq q;
	FILE *fp = fopen(FILE_SEL, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SEL);
		getchar();
		exit(1);
	}


	for (i = 0; i < allselqcnt; i++)
	{
		q = allselqs[i];
		fprintf(fp, FORMATNET, STU_MEMBERS_NET);
	}
	fclose(fp);
	printf("已保存记录到文件。");
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
	printf("所有各科总分、平均分如下\r\n");
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
	printf("科目:%s 平均分%.1f、及格率百分之%.1f、不及格率百分之%.1f\r\n", subuject,
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
	printf("所有科目成绩统计如下\r\n");
	printf("--------------------------------------------\r\n");

	/*for (i = 0; i < allquestionscount; i++)
	{
		scores[i] = allquestions[i].c;
	}*/
	calcanddisplaysubject("C语言", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddquestion()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n请输入学号\n");
	scanf("%d", &no);
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入数学、英语、语文、c语言成绩（整数），空格隔开\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addquestion(no, name, math, english, chinese, c);
	printf("完成第%d个入库录入!\r\n", allselqcnt);
}

int repeatscore[3] = { 10,7,5 };

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

void testallselqs()
{
	int i;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		useselqs[i] = allselqs[useids[i]];
		testoneselq(&useselqs[i]);
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
			score++;
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
	fprintf(fp, "%d\t%s\t%d", no, name, score);
	fclose(fp);
	printf("已添加成绩到文件。");
}

void inputstudentandexam()
{
	int i, no, score;
	char name[50] = "";
	srand(time(NULL));
	readallquestions();
	printf("\n请输入要考生学号(1~100)，并以回车结束:");
	scanf("%d", &no);
	printf("\n请输入考生姓名，不能带空格、Tab或回车符，并以回车结束:");
	scanf("%s", name);

	testallselqs();
	score = displayselqstestresult();
	appendscores(no, name, score);
}

int main()
{
	//int i, no, score;
	//char name[50] = "";


	readallescores();
	sortanddisplayallescores();
	//inputstudentandexam();
	system("pause");
	return 0;
}