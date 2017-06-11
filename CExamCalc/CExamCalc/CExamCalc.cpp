#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "sample.txt"//编译后放exe旁边运行，调试时放cpp旁边
#define FILE_BEST "best.txt"
#define FILE_SCORES "scores.txt"
#define FILE_ANALYSIS "analysis.txt"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35

char best[QUESTIONS_COUNT];//每个问题最佳答案
typedef struct student
{
	char name[MAX_STRLEN];//姓名
	char choice[QUESTIONS_COUNT];//该学生每题的选项
	int total;//总分
}student;
student allstudents[100];//所有学生
int allstudentscount = 0;//所有学生数量

//从一行文本拆分并组合student
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student rec;
	rec.total = 0;
	part = strtok(line, " \t\n");//按空格或tab拆分
	while (part != NULL)
	{
		switch (++index)//列序号
		{
		case 1:
			break;
		case 2:
			strcpy(rec.name, part);
			break;
		case 3:
			strcpy(rec.choice, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return rec;
}

//读入所有学生
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
}

//得出每题的最佳答案
void getbestchoices()
{
	int i, j, t, cnt[100] = { 0 };
	char c, b;
	for (i = 0; i < QUESTIONS_COUNT; i++)
	{
		for (c = 'A'; c <= 'D'; c++)
			cnt[c] = 0;
		for (j = 0; j < allstudentscount; j++)
			cnt[allstudents[j].choice[i]]++;
		t = 0;
		for (c = 'A'; c <= 'D'; c++)
			if (cnt[c] > t)
			{
				t = cnt[c];
				b = c;
			}
		best[i] = b;
	}
}

//每题最佳答案写入文件
void writebestchoices()
{
	int i;
	FILE *fp = fopen(FILE_BEST, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BEST);
		getchar();
		exit(1);
	}
	for (i = 0; i < QUESTIONS_COUNT; i++)
	{
		printf("%d\t%c\r\n", i + 1, best[i]);
		fprintf(fp, "%d\t%c\r\n", i + 1, best[i]);
	}
	fclose(fp);
}

//计算每个学生的总分
void calctotal()
{
	int i, q, sum;
	for (i = 0; i < allstudentscount; i++)
	{
		sum = 0;
		for (q = 0; q < QUESTIONS_COUNT; q++)
		{
			if (allstudents[i].choice[q] == best[q])
			{
				if (q < 15)
					sum += 2;
				else if (q < 25)
					sum += 3;
				else
					sum += 4;
			}
		}
		allstudents[i].total = sum;
	}
}

//比较两个学生的总分
int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
//按总分把学生排序
void sorttotal()
{
	//qsort是stdlib.h里的标准函数，快速排序
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

//把每个学生的总分写入文件
void writetotal()
{
	int i;
	FILE *fp;
	fp = fopen(FILE_SCORES, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SCORES);
		getchar();
		exit(1);
	}
	sorttotal();
	for (i = 0; i < allstudentscount; i++)
	{
		printf("%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
		fprintf(fp, "%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
	}
	fclose(fp);
}

//低于60分的人数
int below60()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total < 60)
			c++;
	}
	return c;
}
//60-80分的人数
int below60_80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 60 && allstudents[i].total < 80)
			c++;
	}
	return c;
}


//大于80分的人数
int above80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 80)
			c++;
	}
	return c;
}

//计算所有学生的平均分
float ave()
{
	int i;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
		sum += allstudents[i].total;
	return sum / (float)allstudentscount;
}

//计算所有各个分数段的学生的分布
void writeanalysis()
{
	int i;
	FILE *fp;
	fp = fopen(FILE_ANALYSIS, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ANALYSIS);
		getchar();
		exit(1);
	}
	printf("%s\t%d\r\n", "<60", below60());
	printf("%s\t%d\r\n", "60~80", below60_80());
	printf("%s\t%d\r\n", ">80", above80());
	printf("%s\t%d\r\n", "最高", allstudents[allstudentscount - 1].total);
	printf("%s\t%d\r\n", "最低", allstudents[0].total);
	printf("%s\t%f\r\n", "平均", ave());
	printf("%s\t百分之%d\r\n", "及格率", (int)(100 * (float)(below60_80() + above80()) / (float)allstudentscount));

	fprintf(fp, "%s\t%d\r\n", "<60", below60());
	fprintf(fp, "%s\t%d\r\n", "60~80", below60_80());
	fprintf(fp, "%s\t%d\r\n", ">80", above80());
	fprintf(fp, "%s\t%d\r\n", "最高", allstudents[allstudentscount - 1].total);
	fprintf(fp, "%s\t%d\r\n", "最低", allstudents[0].total);
	fprintf(fp, "%s\t%f\r\n", "平均", ave());
	fprintf(fp, "%s\t百分之%d\r\n", "及格率", (int)(100 * (float)(below60_80() + above80()) / (float)allstudentscount));
	fclose(fp);
}

//输入字符串
void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入姓名,输入q退出查询:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

//根据姓名查找某个学生
int searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
			return allstudents[i].total;
	printf("没找到对应学生的信息。\r\n");
	return 0;
}

//提示输入姓名并查找学生
int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	printf("学生%s的成绩为%d：", name, searchtotalbyname(name));
	return strcmp(name, "q");
}

//主函数
int main()
{
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

	system("pause");
	return 0;
}
