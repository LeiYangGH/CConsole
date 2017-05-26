// CProj.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20
#define STUDENTS_COUNT 6
#define COURSES_COUNT 5

typedef struct student
{
	char name[MAX_STRLEN];//姓名
	int score[COURSES_COUNT];//分数
	int total;//总分
	float average;//平均
}student;
student allstudents[6];//所有学生
int allstudentscount = 0;//学生数量

typedef struct calcstudent
{
	int highest;//总分
	int lowest;//总分
	int total;
	float average;//平均
}calcstudent;
calcstudent allcalcstudents[6];//所有学生


typedef struct course//课程
{
	int highest;//总分
	int lowest;//总分
	int total;
	float average;//平均
}course;
course allcourses[COURSES_COUNT];//5门课程



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
	printf("\r\n--------------------------------------------\r\n");
}

//科目平均分排序
int cmpstubyonecourse(const void * a, const void * b)
{
	return (int)(((student*)a)->score[0] - ((student*)b)->score[0]);
}
//1
void displaystudentonecourse(student stu, int courseid)
{
	printf("%s\t%d\n", stu.name, stu.score[courseid]);
}

//显示所有学生成绩
void displayonecoursesort()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	qsort(allstudents, STUDENTS_COUNT, sizeof(student), cmpstubyonecourse);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudentonecourse(allstudents[i], 0);
	}
	printf("\r\n--------------------------------------------\r\n");
}
//2
//显示一个学生成绩
void displaycalcstudent(calcstudent stu)
{
	printf("%d\t%d\t%.1f\n",
		stu.highest, stu.lowest, stu.average);
}

//显示所有学生成绩
void displayallcalcstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", STUDENTS_COUNT);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		displaycalcstudent(allcalcstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void calchighlowaveanddisplay()
{
	int i, t, j, h, l, sum;
	float ave;
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		h = 0, l = 100, sum = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)COURSES_COUNT;
		allcalcstudents[i].highest = h;
		allcalcstudents[i].lowest = l;
		allcalcstudents[i].total = sum;
		allcalcstudents[i].average = ave;
	}
	displayallcalcstudents();
}





//显示所有科目平均分排序
void displayallcourses()
{
	int i;
	printf("所有科目平均分排序如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{

		course cou = allcourses[i];
		printf("%d\t%d\t%.1f\n",
			cou.highest, cou.lowest, cou.average);
	}
	printf("\r\n--------------------------------------------\r\n");
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




//计算每个科目的平均分
void calccoursesanddisplay()
{
	int i, t, j, h, l, sum;
	float ave;
	for (j = 0; j < COURSES_COUNT; j++)
	{
		h = 0, l = 100, sum = 0;

		for (i = 0; i < STUDENTS_COUNT; i++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)STUDENTS_COUNT;
		allcourses[j].highest = h;
		allcourses[j].lowest = l;
		allcourses[j].total = sum;
		allcourses[j].average = ave;
	}
	displayallcourses();
}





////提示输入要排序的科目
//void promptaskcmpcourseindex()
//{
//	int courseid;
//	printf("\n请输入要排序的课程序号(1~5)，以回车结束：");
//	scanf("%d", &courseid);
// 
//}


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

//查找姓名
void searcbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("没找到对应学生的信息。\r\n");
}
//用户输入并查找姓名
void promptsearchbyname()
{
	char name[20];
	printf("请输入姓名:");
	scanf("%s", name);
	searcbyname(name);
}

int main()
{
#if 1
	addstudent("04", "n4", 41, 42, 43, 44, 45);
	addstudent("01", "n1", 11, 12, 13, 14, 15);
	addstudent("02", "n2", 21, 22, 23, 24, 25);
	addstudent("06", "n6", 61, 62, 63, 64, 65);
	addstudent("03", "n3", 31, 32, 33, 34, 35);
	addstudent("05", "n5", 51, 52, 53, 54, 55);
	displayallstudents();
	//calchighlowaveanddisplay();
	//calccoursesanddisplay();
	//searcbyname("n1");
	displayonecoursesort();
	system("pause");
#endif
	int choice = -1;


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

			break;
		case '2':
			printf("\n\n你选择了 2\n");

			break;
		case '3':
			printf("\n\n你选择了 3\n");

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

