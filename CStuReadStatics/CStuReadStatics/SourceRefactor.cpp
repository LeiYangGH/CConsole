#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#define FILE_INPUT "stuin.txt"
#define FILE_ALLOUTPUT "stuout.txt"
#define MAX_STRLEN 20
#define GRADES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	int score;
}student;

student allstudents[1005];
int allstudentscount = 0;

float averagescore = 0;

FILE *outfile;

void f2printf(char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt); vfprintf(stdout, fmt, argp); va_end(argp);
	va_start(argp, fmt); vfprintf(outfile, fmt, argp); va_end(argp);
}

void displaystudent(student stu)
{
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score);
	fprintf(outfile, "%s\t%s\t%d\n", stu.no, stu.name, stu.score);
}

void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("学号\t姓名\t成绩\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
		displaystudent(allstudents[i]);
	printf("--------------------------------------------\r\n");
}

void readallstudents()
{
	char line[50];
	FILE *fp = fopen(FILE_INPUT, "r");
	student stu;
	allstudentscount = 0;//
	while (fgets(line, 80, fp) != NULL)
	{
		++allstudentscount;
		sscanf(line, "%s%s%d", stu.no, stu.name, &stu.score);
		allstudents[allstudentscount - 1] = stu;
	}
}

int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}

void displayhigheststudents()
{
	int i = 0;
	printf("\n最高分同学:\n");
	fprintf(outfile, "最高分同学:\n");
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
	while (allstudents[i].score == allstudents[0].score)
	{
		f2printf("学号:%s 姓名:%s 分数:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
		//printf("学号:%s 姓名:%s 分数:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
	//fprintf(outfile, "学号:%s 姓名:%s 分数:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
		i++;
	}
}

void countanddisplaycompareaveragecount()
{
	int i, t, low = 0, high = 0;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
		sum += allstudents[i].score;
	averagescore = sum / (float)allstudentscount;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score;
		if (t < averagescore)
			low++;
		else if (t > averagescore)
			high++;
	}
	printf("平均成绩高于平均成绩的人数：%d\n", high);
	fprintf(outfile, "平均成绩高于平均成绩的人数：%d\n", high);
	printf("平均成绩低于平均成绩的人数：%d\n", low);
	fprintf(outfile, "平均成绩低于平均成绩的人数：%d\n", low);
	printf("平均成绩等于平均成绩的人数：%d\n", allstudentscount - (high + low));
	fprintf(outfile, "平均成绩等于平均成绩的人数：%d\n", allstudentscount - (high + low));
}

int calcpercent(int g)
{
	return (int)(g * 100 / (float)allstudentscount);
}

void countanddisplaygradescountandpercent()
{
	int i, g5 = 0, g6 = 0, g7 = 0, g8 = 0, g9 = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].score < 60)
			g5++;
		else if (allstudents[i].score >= 60 && allstudents[i].score <= 69)
			g6++;
		else if (allstudents[i].score >= 70 && allstudents[i].score <= 79)
			g7++;
		else if (allstudents[i].score >= 80 && allstudents[i].score <= 89)
			g8++;
		else if (allstudents[i].score >= 90)
			g9++;
	}
	printf("不及格(0～59)的%d人，占%d%%\n", g5, calcpercent(g5));
	fprintf(outfile, "不及格(0～59)的%d人，占%d%%\n", g5, calcpercent(g5));
	printf("及格(60～69)的%d人，占%d%%\n", g6, calcpercent(g6));
	fprintf(outfile, "及格(60～69)的%d人，占%d%%\n", g6, calcpercent(g6));
	printf("中等(70～79)的%d人，占%d%%\n", g7, calcpercent(g7));
	fprintf(outfile, "中等(70～79)的%d人，占%d%%\n", g7, calcpercent(g7));
	printf("良好(80～89)的%d人，占%d%%\n", g8, calcpercent(g8));
	fprintf(outfile, "良好(80～89)的%d人，占%d%%\n", g8, calcpercent(g8));
	printf("优秀(90～100)的%d人，占%d%%\n", g9, calcpercent(g9));
	fprintf(outfile, "优秀(90～100)的%d人，占%d%%\n", g9, calcpercent(g9));
}


int main()
{
	outfile = fopen(FILE_ALLOUTPUT, "a+");
	if (outfile == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ALLOUTPUT);
		getchar();
		exit(1);
	}
	readallstudents();
	displayallstudents();
	displayhigheststudents();
	countanddisplaycompareaveragecount();
	countanddisplaygradescountandpercent();
	fclose(outfile);
	//printf("数据已输出到文件%s\n", FILE_ALLOUTPUT);
	system("pause");
	return 0;
}
