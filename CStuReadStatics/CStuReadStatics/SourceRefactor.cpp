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
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("ѧ��\t����\t�ɼ�\n");
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
	printf("\n��߷�ͬѧ:\n");
	fprintf(outfile, "��߷�ͬѧ:\n");
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
	while (allstudents[i].score == allstudents[0].score)
	{
		f2printf("ѧ��:%s ����:%s ����:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
		//printf("ѧ��:%s ����:%s ����:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
	//fprintf(outfile, "ѧ��:%s ����:%s ����:%d\n", allstudents[i].no, allstudents[i].name, allstudents[i].score);
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
	printf("ƽ���ɼ�����ƽ���ɼ���������%d\n", high);
	fprintf(outfile, "ƽ���ɼ�����ƽ���ɼ���������%d\n", high);
	printf("ƽ���ɼ�����ƽ���ɼ���������%d\n", low);
	fprintf(outfile, "ƽ���ɼ�����ƽ���ɼ���������%d\n", low);
	printf("ƽ���ɼ�����ƽ���ɼ���������%d\n", allstudentscount - (high + low));
	fprintf(outfile, "ƽ���ɼ�����ƽ���ɼ���������%d\n", allstudentscount - (high + low));
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
	printf("������(0��59)��%d�ˣ�ռ%d%%\n", g5, calcpercent(g5));
	fprintf(outfile, "������(0��59)��%d�ˣ�ռ%d%%\n", g5, calcpercent(g5));
	printf("����(60��69)��%d�ˣ�ռ%d%%\n", g6, calcpercent(g6));
	fprintf(outfile, "����(60��69)��%d�ˣ�ռ%d%%\n", g6, calcpercent(g6));
	printf("�е�(70��79)��%d�ˣ�ռ%d%%\n", g7, calcpercent(g7));
	fprintf(outfile, "�е�(70��79)��%d�ˣ�ռ%d%%\n", g7, calcpercent(g7));
	printf("����(80��89)��%d�ˣ�ռ%d%%\n", g8, calcpercent(g8));
	fprintf(outfile, "����(80��89)��%d�ˣ�ռ%d%%\n", g8, calcpercent(g8));
	printf("����(90��100)��%d�ˣ�ռ%d%%\n", g9, calcpercent(g9));
	fprintf(outfile, "����(90��100)��%d�ˣ�ռ%d%%\n", g9, calcpercent(g9));
}


int main()
{
	outfile = fopen(FILE_ALLOUTPUT, "a+");
	if (outfile == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_ALLOUTPUT);
		getchar();
		exit(1);
	}
	readallstudents();
	displayallstudents();
	displayhigheststudents();
	countanddisplaycompareaveragecount();
	countanddisplaygradescountandpercent();
	fclose(outfile);
	//printf("������������ļ�%s\n", FILE_ALLOUTPUT);
	system("pause");
	return 0;
}
