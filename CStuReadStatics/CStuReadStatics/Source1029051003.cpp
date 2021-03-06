#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "stuin.txt"//
#define FILE_ALLOUTPUT "stuout.txt"
#define MAX_STRLEN 20 //最长字符串长度
#define GRADES_COUNT 5 //等级个数

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

//显示一个学生成绩
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score);
	fprintf(outfile, "%s\t%s\t%d\n", stu.no, stu.name, stu.score);
}

//显示所有学生成绩
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

//从一行文本拆分并组合出一个学生
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, " \n");//拆分函数，按空格和回车
	while (part != NULL)
	{
		switch (++index)//index是文本的列序号
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.score = toint(part);
		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return stu;
}

//计算总分和平均分
void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].score;
	}
	averagescore = sum / (float)allstudentscount;
}

//从文件读所有学生
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
		if (strlen(line) < 5)//如果有些行是空行或者不规范
			continue;
		++allstudentscount;
	//每行一个学生
		allstudents[allstudentscount - 1] = getstudentfromline(line);
	}
}

//固定格式，比较分数
int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}
//所有学生按分数排序
void sortstudetsbyscore()
{
	//qsort 快速排序函数，是标准c库里的函数
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
}

//显示最高分的学生
void displayhigheststudents()
{
	int i = 0;
	printf("\n最高分同学如下\r\n");
	fprintf(outfile, "最高分同学如下\r\n");
	sortstudetsbyscore();
	printf("学号\t姓名\t成绩\n");
	fprintf(outfile, "学号\t姓名\t成绩\n");
	printf("--------------------------------------------\r\n");
	while (allstudents[i].score == allstudents[0].score)
		displaystudent(allstudents[i++]);
	printf("--------------------------------------------\r\n");
}

//计算并显示平均分高于、等于、低于平均分的人数
void countanddisplaycompareaveragecount()
{
	int i, t, low = 0, eq = 0, high = 0;
	calctotalandave();
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score;
		if (t < averagescore)
			low++;
		else if (t == averagescore)
			eq++;
		else if (t > averagescore)
			high++;
	}
	//printf("\n平均成绩：%.2f\n", averagescore);
	printf("\n平均成绩高于平均成绩的人数：%d\n", high);
	fprintf(outfile, "\n平均成绩高于平均成绩的人数：%d\n", high);
	printf("平均成绩低于平均成绩的人数：%d\n", low);
	fprintf(outfile, "平均成绩低于平均成绩的人数：%d\n", low);
	printf("平均成绩等于平均成绩的人数：%d\n\n", eq);
	fprintf(outfile, "平均成绩等于平均成绩的人数：%d\n\n", eq);
}

//计算并显示各个分数段等级的人数和百分比
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

//主函数
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
	//displayallstudents();
	displayhigheststudents();
	countanddisplaycompareaveragecount();
	countanddisplaygradescountandpercent();
	fclose(outfile);
	printf("数据已输出到文件%s\n", FILE_ALLOUTPUT);
	system("pause");
	return 0;
}
