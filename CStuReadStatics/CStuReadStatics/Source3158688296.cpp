#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"

typedef struct student
{
	char  no[11];           //学号
	char  name[20];    //姓名
	int  score;              //成绩
}student;
student allstudents[100];
int allstudentscount = 0;


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
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score);
}

void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("学号\t姓名\t分数\n");
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
		part = strtok(NULL, "\t");
	}
	return stu;
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
}

int cmpstuscorefunc(const void * a, const void * b)
{
	return ((student*)a)->score - ((student*)b)->score;
}
void sortstudentsbyscore()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuscorefunc);
}

int cmpstunamefunc(const void * a, const void * b)
{
	return strcmp(((student*)a)->name, ((student*)b)->name);
}
void sortstudentsbyname()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstunamefunc);
}

void displayhighest()
{
	sortstudentsbyscore();
	printf("\n最高分学生为\n");
	displaystudent(allstudents[allstudentscount - 1]);
}

int login()
{
	int trytimes = 3;
	char username[20] = "";
	char password[20] = "";
	while (trytimes > 0)
	{
		printf("\n还有%d次机会\n", trytimes--);
		printf("\n请输入用户名:");
		scanf("%s", &username);
		printf("\n请输入密码:");
		scanf("%s", &password);
		if (strcmp(username, "admin") == 0
			&& strcmp(password, "123456") == 0)
			return 1;
	}
	return 0;
}

int main()
{
#if TEST
	readallstudents();
	//sortstudentsbyscore();
	//sortstudentsbyname();
	displayallstudents();
	displayhighest();
#else
	if (!login())
		return 0;
	int choice = -1;
	printf("\n开始读文件...\n");
	readallstudents();
	printf("\n读文件结束！\n");

	while (choice != 0)
	{
		printf("\n\t 学生成绩读入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 成绩排序");
		printf("\n\t 2. 姓名排序");
		printf("\n\t 3. 成绩最高分");
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
			sortstudentsbyscore();
			displayallstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			sortstudentsbyname();
			displayallstudents();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			displayhighest();
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
