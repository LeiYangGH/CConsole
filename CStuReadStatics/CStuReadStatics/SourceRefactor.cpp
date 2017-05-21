#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct student
{
	char no[20];
	char name[20];
	int score;
}student;

student students[1005];
int renshu = 0;
FILE *fp;

void printf2(char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt); vfprintf(stdout, fmt, argp); va_end(argp);
	va_start(argp, fmt); vfprintf(fp, fmt, argp); va_end(argp);
}

void duruchengji()
{
	char str[50];
	FILE *fp = fopen("stuin.txt", "r");
	student stu;
	while (fgets(str, 80, fp) != NULL)
	{
		++renshu;
		sscanf(str, "%s%s%d", stu.no, stu.name, &stu.score);
		students[renshu - 1] = stu;
	}
}

int bijiao(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}

void zuigaofen()
{
	int i = 0;
	printf2("\n最高分同学:\n");
	qsort(students, renshu, sizeof(student), bijiao);
	while (students[i].score == students[0].score)
	{
		printf2("学号:%s 姓名:%s 分数:%d\n", students[i].no, students[i].name, students[i].score);
		i++;
	}
}

void pingjunchengjibijiao()
{
	int i, t, low = 0, high = 0;
	float sum = 0, averagescore = 0;
	for (i = 0; i < renshu; i++)
		sum += students[i].score;
	averagescore = sum / (float)renshu;
	for (i = 0; i < renshu; i++)
	{
		t = students[i].score;
		if (t < averagescore)
			low++;
		else if (t > averagescore)
			high++;
	}
	printf2("平均成绩高于平均成绩的人数：%d\n", high);
	printf2("平均成绩低于平均成绩的人数：%d\n", low);
	printf2("平均成绩等于平均成绩的人数：%d\n", renshu - (high + low));
}

int jisuanbaifenbi(int g)
{
	return (int)(g * 100 / (float)renshu);
}

void jisuandengjirenshuhebaifenbi()
{
	int i, g5 = 0, g6 = 0, g7 = 0, g8 = 0, g9 = 0;
	for (i = 0; i < renshu; i++)
	{
		if (students[i].score < 60)
			g5++;
		else if (students[i].score >= 60 && students[i].score <= 69)
			g6++;
		else if (students[i].score >= 70 && students[i].score <= 79)
			g7++;
		else if (students[i].score >= 80 && students[i].score <= 89)
			g8++;
		else if (students[i].score >= 90)
			g9++;
	}
	printf2("不及格(0～59)的%d人，占%d%%\n", g5, jisuanbaifenbi(g5));
	printf2("及格(60～69)的%d人，占%d%%\n", g6, jisuanbaifenbi(g6));
	printf2("中等(70～79)的%d人，占%d%%\n", g7, jisuanbaifenbi(g7));
	printf2("良好(80～89)的%d人，占%d%%\n", g8, jisuanbaifenbi(g8));
	printf2("优秀(90～100)的%d人，占%d%%\n", g9, jisuanbaifenbi(g9));
}

int main()
{
	fp = fopen("stuout.txt", "a+");
	if (fp == NULL)
	{
		printf("\n打开文件stuout.txt失败!");
		getchar();
		exit(1);
	}
	duruchengji();
	zuigaofen();
	pingjunchengjibijiao();
	jisuandengjirenshuhebaifenbi();
	fclose(fp);
	printf("数据已输出到文件stuout.txt\n");
	system("pause");
	return 0;
}
