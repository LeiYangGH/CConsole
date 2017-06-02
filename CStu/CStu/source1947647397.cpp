// CProj.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5

typedef struct student
{
	char name[MAX_STRLEN];//姓名
	int score[COURSES_COUNT];//分数
	int total;//总分
	float average;//平均
}student;
student allstudents[100];//所有学生
int allstudentscount = 0;//学生数量


typedef struct course//课程
{
	int oldindex;//课程在input.txt里的序号
	float average;//平均分
}course;
course allcourses[COURSES_COUNT];//5门课程


//int cmpcourseindex;//排序的课程下标（0～4）
				   //字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}
//显示一个学生成绩
void displaystudent(student stu)
{
	printf("%s\t%d\t%d\t%d\t%d\t%d\t%.1f\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average);
}

//显示所有学生成绩
void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行拆分构造出一个学生
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");//通过\t符号拆分不同分数
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

//计算总分和平均分
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

//读文件到学生数组
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


//下面两个函数是快速排序qsort要求的格式，按总分排学生
int cmptotalfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sorttotal()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmptotalfunc);
}

////按某科目排所有成绩
//int cmponecoursefunc(const void * a, const void * b)
//{
//	return ((student*)a)->score[cmpcourseindex] - ((student*)b)->score[cmpcourseindex];
//}
//void sortonecourse()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmponecoursefunc);
//}

//计算每个科目的平均分
void calceachcourseave()
{
	int i, j;
	float sum;
	for (j = 0; j < COURSES_COUNT; j++)
	{
		sum = 0;
		for (i = 0; i < allstudentscount; i++)
		{
			sum += allstudents[i].score[j];
		}
		allcourses[j].oldindex = j;
		allcourses[j].average = sum / (float)COURSES_COUNT;
	}
}

//科目平均分排序
int cmpcoursesavefunc(const void * a, const void * b)
{
	return  ((course*)a)->average > ((course*)b)->average;
}
void sortcoursesave()
{
	qsort(allcourses, COURSES_COUNT, sizeof(course), cmpcoursesavefunc);
}


//提示输入要排序的科目
int promptaskcmpcourseindex()
{
	int courseid;
	printf("\n请输入要排序的课程序号(1~5)，以回车结束：");
	scanf("%d", &courseid);
	return courseid - 1;
}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_INPUT, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\r\n", stu.name,
			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void addstudent(char no[], char name[], int s0, int s1, int s2, int s3, int s4)
{
	student stu;
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.score[3] = s3;
	stu.score[4] = s4;
	allstudents[allstudentscount++] = stu;
	calctotalandave();
	writeallstudents();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n请输入学生姓名\n");
	scanf("%s", name);
	printf("\n请输入5科成绩（整数），空格隔开\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("完成第%d个学生成绩录入!\r\n", allstudentscount);
}

void calcdisplayhighlowave(int courseid)
{
	int i, t, h = 0, l = 100, sum = 0;
	float ave;
	int  below60stuindexes[20], belowcount = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score[courseid];
		h = h < t ? t : h;
		l = l > t ? t : l;
		sum += t;
		if (t < 60)
			below60stuindexes[belowcount++] = i;
	}
	ave = sum / (float)allstudentscount;
	printf("第%d门课程统计信息：\r\n", courseid + 1);
	printf("平均分:%.1f、最高分%d、最低分%d\n", ave, h, l);
	printf("补考名单:", ave, h, l);
	for (i = 0; i < belowcount; i++)
	{
		printf("%s\t", allstudents[below60stuindexes[i]].name);
	}
	printf("\n");
}

int main()
{
#if 1
	readallstudents();
	displayallstudents();
	calcdisplayhighlowave(promptaskcmpcourseindex());
	system("pause");

#endif
	int choice = -1;
	printf("\n开始读文件...\n");
	readallstudents();
	printf("\n读文件结束！\n");

	while (choice != 0)
	{
		printf("\n\t 学生成绩读入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 按学生总分升降序输出");
		printf("\n\t 2. 按某门课程分数升降序输出");
		printf("\n\t 3. 按所有课程平均分升降序输出");
		printf("\n\t 4. 添加学生成绩");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			sorttotal();
			displayallstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaskcmpcourseindex();

			break;
		case '3':
			printf("\n\n你选择了 3\n");
			calceachcourseave();
			sortcoursesave();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptaddstudent();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}

	system("pause");
	return 0;
}

