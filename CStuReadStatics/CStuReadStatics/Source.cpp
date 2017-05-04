#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
//#define FILE_INPUT "sample.txt"
#define FILE_BEST "best.txt"
#define FILE_SCORES "scores.txt"
#define FILE_ANALYSIS "analysis.txt"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define COURSES_COUNT 5

char best[QUESTIONS_COUNT];
typedef struct student
{
	char name[MAX_STRLEN];
	//char choice[QUESTIONS_COUNT];
	int score[COURSES_COUNT];
	int total;
	float average;
}student;
student allstudents[100];
int allstudentscount = 0;
#define TEST 1
//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%s\t\%d\t\%d\t\%d\t\%d\t\%d\t%.1f\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average);
}

void displayallstudents()
{
	int i;
	printf("所有%d分数如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
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
			strcpy(stu.name, part);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			stu.score[index - 2] = toint(part);
			break;

		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			allstudents[i].total += allstudents[i].score[j];
		}
		allstudents[i].average = allstudents[i].total / (float)COURSES_COUNT;
	}
}


void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		++allstudentscount;
		allstudents[allstudentscount - 1] = getstudentfromline(line);
	}
	calctotalandave();
}


//
//int cmpfunc(const void * a, const void * b)
//{
//	return ((student*)a)->total - ((student*)b)->total;
//}
//void sorttotal()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
//}
//
//void writetotal()
//{
//	int i;
//	FILE *fp;
//	fp = fopen(FILE_SCORES, "wb");
//	if (fp == NULL)
//	{
//		printf("\n打开文件%s失败!", FILE_SCORES);
//		getchar();
//		exit(1);
//	}
//	sorttotal();
//	for (i = 0; i < allstudentscount; i++)
//	{
//		printf("%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
//		fprintf(fp, "%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
//	}
//	fclose(fp);
//}
//
// 
//float ave()
//{
//	int i;
//	float sum = 0;
//	for (i = 0; i < allstudentscount; i++)
//		sum += allstudents[i].total;
//	return sum / (float)allstudentscount;
//}






int main()
{
#if TEST
	readallstudents();
	displayallstudents();
#else

	int choice = -1;
	printf("\n开始读文件...\n");
	readallstudents();
	printf("\n读文件结束！\n");

	printf("\n开始统计最佳答案...\n");
	getbestchoices();
	writebestchoices();
	printf("\n统计最佳答案结束！\n");

	printf("\n开始计算每位同学总成绩...\n");
	calctotal();
	writetotal();
	printf("\n计算每位同学总成绩结束！\n");

	printf("\n开始统计所有成绩...\n");
	writeanalysis();
	printf("\n统计所有成绩结束！\n");

	while (choice != 0)
	{
		printf("\n\t---分数查询，输入q结束查询---\n");
		choice = promptsearchtotalbyname();
}
#endif
	system("pause");
	return 0;
}
