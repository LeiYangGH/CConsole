#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
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
	allstudentscount = 0;
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
	printf("\n最高分同学如下\r\n");
	fprintf(outfile, "最高分同学如下\r\n");
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
	printf("学号\t姓名\t成绩\n");
	fprintf(outfile, "学号\t姓名\t成绩\n");
	printf("--------------------------------------------\r\n");
	while (allstudents[i].score == allstudents[0].score)
		displaystudent(allstudents[i++]);
	printf("--------------------------------------------\r\n");
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
	printf("\n平均成绩高于平均成绩的人数：%d\n", high);
	fprintf(outfile, "\n平均成绩高于平均成绩的人数：%d\n", high);
	printf("平均成绩低于平均成绩的人数：%d\n", low);
	fprintf(outfile, "平均成绩低于平均成绩的人数：%d\n", low);
	printf("平均成绩等于平均成绩的人数：%d\n\n", allstudentscount - (high + low));
	fprintf(outfile, "平均成绩等于平均成绩的人数：%d\n\n", allstudentscount - (high + low));
}

void countanddisplaygradescountandpercent()
{
	int i, t;
	int count[GRADES_COUNT] = { 0 };
	char *grades[GRADES_COUNT] = { "不及格(0～59)","及格(60～69)", "中等(70～79)", "良好(80～89)", "优秀(90～100)", };
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score;
		if (t < 60)
			count[0]++;
		else if (t >= 60 && t <= 69)
			count[1]++;
		else if (t >= 70 && t <= 79)
			count[2]++;
		else if (t >= 80 && t <= 89)
			count[3]++;
		else if (t >= 90)
			count[4]++;
	}
	printf("分数段\t人数\t百分比\n");
	fprintf(outfile, "分数段\t人数\t百分比\n");
	for (i = 0; i < GRADES_COUNT; i++)
	{
		printf("%s\t%d\t%d%%\n", grades[i], count[i], (int)(count[i] * 100 / (float)allstudentscount));
		fprintf(outfile, "%s\t%d\t%d%%\n", grades[i], count[i], (int)(count[i] * 100 / (float)allstudentscount));
	}
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
