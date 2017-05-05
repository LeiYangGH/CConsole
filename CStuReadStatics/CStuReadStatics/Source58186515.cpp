#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5
#define GRADES_COUNT 5

typedef struct student
{
	char name[MAX_STRLEN];
	int score[COURSES_COUNT];
	float average;
	int order;
}student;
student allstudents[100];
int allstudentscount = 0;

typedef struct course
{
	int oldindex;
	float average;
	int countingrade[GRADES_COUNT];
}course;
course allcourses[COURSES_COUNT];


#define TEST 0
int cmpcourseindex;
//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%d\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average, stu.order);
}

void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("姓名\t科目1\t科目2\t科目3\t科目4\t科目5\t平均\t排名\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void displayonecourseorder()
{
	int i;
	printf("第%d科目分数如下\r\n", cmpcourseindex + 1);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		printf("\r\n");
		student stu = allstudents[i];
		printf("%s\t\%d\n", stu.name,
			stu.score[cmpcourseindex]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void displayallcoursesaveorder()
{
	int i;
	printf("所有科目平均分排序如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{
		printf("\r\n");
		course cou = allcourses[i];
		printf("第%d科\t\%.1f\n", cou.oldindex + 1,
			cou.average);
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
		sum = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			sum += allstudents[i].score[j];
		}
		allstudents[i].average = sum / (float)COURSES_COUNT;
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



int cmpstuavefunc(const void * a, const void * b)
{
	return (((student*)a)->average - ((student*)b)->average);
}
void sortstuave()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
	allstudents[0].order = 1;
	for (i = 1; i < allstudentscount; i++)
	{
		if (allstudents[i].average == allstudents[i - 1].average)
			allstudents[i].order = allstudents[i - 1].order;
		else
			allstudents[i].order = allstudents[i - 1].order + 1;
	}
}


int cmponecoursefunc(const void * a, const void * b)
{
	return (((student*)a)->score[cmpcourseindex] - ((student*)b)->score[cmpcourseindex]);
}
void sortonecourse()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmponecoursefunc);
}

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

int cmpcoursesavefunc(const void * a, const void * b)
{
	return (((course*)a)->average - ((course*)b)->average);
}
void sortcoursesave()
{
	qsort(allcourses, COURSES_COUNT, sizeof(course), cmpcoursesavefunc);
}

void promptaskcmpcourseindex()
{
	int courseid;
	printf("\n请输入要排序的课程序号(1~5)，以回车结束：");
	scanf("%d", &courseid);
	cmpcourseindex = courseid - 1;
}


int main()
{
#if TEST
	readallstudents();
	//sorttotal();
	//displayallstudents();
	ascending = -1;
	cmpcourseindex = 4;
	sortonecourse();
	displayonecourseorder();
#else

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
			sortstuave();
			displayallstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaskcmpcourseindex();
			sortonecourse();
			displayonecourseorder();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			calceachcourseave();
			sortcoursesave();
			displayallcoursesaveorder();
			break;

		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
#endif
	system("pause");
	return 0;
}
