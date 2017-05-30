#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct student
{
	char no[50];
	char name[50];
	int chinese;
	int math;
	int english;
	int total;
}student;

student allstudents[100];
int allstudentscount = 0;

float averagechinese, averagemath, averageenglish;

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.chinese, stu.math, stu.english);
}

void displayallstudents()
{
	int i;
	printf("所有%d分数如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//qsort是快速排序，要求如下写法，根据total排序
int cmpfunc(const void * b, const void * a)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sortstudentsbytotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = allstudents[i].chinese + allstudents[i].math + allstudents[i].english;
	}
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortstudentsbytotalanddisplay()
{
	int i;
	sortstudentsbytotal();
	printf("按每个学生各科平均成绩排序后如下\r\n");
	displayallstudents();
}

void addstudent(char no[50], char name[], int chinese, int math, int english)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.chinese = chinese;
	stu.math = math;
	stu.english = english;
	allstudents[allstudentscount++] = stu;
}

void promptaddstudent()
{
	char no[50]; char name[50] = "";
	int math; int english; int chinese;
	printf("\n请输入学号和姓名，空格隔开\n");
	scanf("%s%s", no, name);
	printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, chinese, math, english);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
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
//查找学号
void searchbyno(char no[20])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (streq(allstudents[i].no, no))
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("没找到对应学生的信息。\r\n");
}
//用户输入并查找学号
void promptsearchbyno()
{
	char no[20];
	printf("请输入要查询的学号:");
	scanf("%s", no);
	searchbyno(no);
}


int main()
{
	char choice = -1;
#if 0//测试用，if块可删除
	//readallstudents();

	addstudent("04", "n4", 41, 92, 93);
	addstudent("01", "n1", 11, 12, 3);
	addstudent("02", "n2", 21, 22, 99);
	addstudent("05", "n5", 51, 52, 93);
	addstudent("06", "n6", 61, 62, 93);
	addstudent("03", "n3", 31, 32, 93);
	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	//calcanddisplaycoursehighest();
	calccoursesaveragesanddisplay();
	calccoursesaveragesbelowcountanddisplay();
	system("pause");

#endif
	while (choice != 0)
	{
		printf("\n\t 学生信息管理系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 添加学生信息");
		printf("\n\t 2. 按总分降序查看所有学生信息");
		printf("\n\t 3. 按学号查询");
		printf("\n\t 4. 按姓名查询");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);//清楚输入缓冲区，以免意外非法输入造成死循环
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
			promptaddstudent();

			break;
		case '2':
			printf("\n\n你选择了 2\n");
			sortstudentsbytotalanddisplay();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptsearchbyno();
			break;
		case '4':
			printf("\n\n你选择了 3\n");
			promptsearchbyname();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	printf("\n\n按任意键退出\n");
	system("pause");

	return 0;
}

