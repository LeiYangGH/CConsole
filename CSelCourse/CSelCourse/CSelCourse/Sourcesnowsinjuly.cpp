#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define COU_CNT 7
#define MAX_STRLEN 20
#define MAX_COUNT 50
#define FORMAT_COU "%d\t%s\r\n"
#define MEMBERS_COU cou.no, cou.name
#define FORMAT_STU "%s\t%s\r\n"
#define MEMBERS_STU stu.no, stu.name
#define LINE  "\n------------------------\n"

//#define N 2

typedef struct course
{
	int no;
	//char no[MAX_STRLEN];
	char name[MAX_STRLEN];
}course;
course allcourses[MAX_COUNT];
int allcoursescount = 0;

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	int scores[COU_CNT];
	int selcourses[COU_CNT];
	int selcouscnt;
}student;
student allstudents[MAX_COUNT];
int allstudentscount = 0;

char curstuname[MAX_STRLEN] = "";
student  *curstu;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaycourse(course cou)
{
	printf(FORMAT_COU, MEMBERS_COU);
	printf("\r\n");
}
void displayallcourses()
{
	int i;
	printf("所有课程情况如下\r\n");
	printf("编号\t名称\r\n");
	printf(LINE);
	for (i = 0; i < allcoursescount; i++)
	{
		displaycourse(allcourses[i]);
	}
	printf(LINE);
}
void findcoursebyno(int no, course **cou)
{
	int i;
	int found = 0;
	for (i = 0; i < allcoursescount; i++)
	{
		if (allcourses[i].no == no)
		{
			*cou = &allcourses[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到编号名为%d的课程\r\n", no);
		*cou = NULL;
	}
}

void displayonestuselcourses(student *stu)
{
	int i;
	course *cou;
	printf("学生%s选课%d门如下\r\n", stu->name, stu->selcouscnt);
	for (i = 0; i < stu->selcouscnt; i++)
	{
		findcoursebyno(stu->selcourses[i], &cou);
		printf("%s\t", cou->name);
	}
	printf("\r\n");
}
void displayallstuselcourses()
{
	int i;
	printf("所有学生选课结果如下\r\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displayonestuselcourses(&allstudents[i]);
	}
	printf(LINE);
}

//void inputonestuscores(student *stu)
//{
//	int i;
//	int score;
//	char sup[MAX_STRLEN] = "";
//	course *cou;
//	printf("下面请输入学生%s的课程分数\r\n", stu->name);
//	for (i = 0; i < stu->selcouscnt; i++)
//	{
//		findcoursebyno(stu->selcourses[i], &cou);
//		printf("%s的分数：", cou->name);
//		scanf("%d", &score);
//		stu->scores[i] = score;
//		if (score < 60)
//		{
//			printf("请输入补考信息：");
//			scanf("%s", &sup);
//			strcpy(&stu->supplement[i], sup);
//		}
//	}
//	printf("\r\n");
//}
//void inputallstuscores()
//{
//	student *p = stuhead->next;
//	printf("请输入所有学生的课程分数\r\n");
//	printf(LINE);
//	while (p != NULL)
//	{
//		inputonestuscores(p);
//		p = p->next;
//	}
//	printf("所有学生的课程输入完毕。\r\n");
//}



void addscourse(int no, char *name)
{
	course cou;
	cou.no = no;
	strcpy(cou.name, name);
	allcourses[allcoursescount++] = cou;
}


void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()
{
	int i;
	printf("所有学生如下\r\n");
	printf("学号\t姓名\r\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf(LINE);
}
/////////////
void addcourse(int no, char *name)
{
	course cou;
	cou.no = no;
	strcpy(cou.name, name);
	allcourses[allcoursescount++] = cou;
}

void inputcourses()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入课程编号(整数，0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入课程名称:");
		scanf("%s", name);
		addcourse(no, name);
		printf("\n课程%s信息添加成功!\n", name);
	}
}

/////////////

void addstudent(char *no, char *name)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.selcouscnt = 0;
	allstudents[allstudentscount++] = stu;
}

void inputstudents()
{
	int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入学生学号(q结束):");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入学生姓名:");
		scanf("%s", name);
		addstudent(no, name);
		printf("\n学生%s信息添加成功!\n", name);
	}
}


void findstudentbyname(char *name, student **stu)
{
	int i;
	int found = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, name))
		{
			*stu = &allstudents[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到姓名为%s的学生\r\n", name);
		*stu = NULL;
	}
}

void selectonecourse(student *stu, int couno)
{
	course *cou;
	findcoursebyno(couno, &cou);
	if (cou != NULL)
	{
		stu->selcourses[stu->selcouscnt] = couno;
		stu->selcouscnt++;
		printf("选课成功！\r\n");
	}
}

void selectcourses(student *stu)
{
	int no;
	if (stu == NULL)
	{
		printf("请先输入姓名再选课！\n");
		return;
	}
	do
	{
		printf("请输入要选择的课程号，0结束选择：");
		scanf("%d", &no);
		fseek(stdin, 0, SEEK_END);
		if (no == 0)
		{
			printf("你已退出了课程选择。\n");
			break;
		}
		selectonecourse(stu, no);
	} while (1);
	printf("选课结束。\n");
}

int main()
{
	int choice = -1;
	addstudent("001", "n1");
	addstudent("002", "ly");
	addstudent("003", "n3");
	displayallstudents();
	strcpy(curstuname, "ly");
	findstudentbyname(curstuname, &curstu);


	addscourse(1, "c1");
	addscourse(2, "c2");
	displayallcourses();
	//inputstudents();
	selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	//findstudentbyname("sm", &stu);
	/*selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);*/
	displayallstuselcourses();
#if DEV



#else
	while (choice != 0)
	{
		printf("\n\t 学生选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入学生信息");
		printf("\n\t 2. 查看所有课程");
		printf("\n\t 3. 查看所有学生");
		printf("\n\t 4. 更改当前学生姓名");
		printf("\n\t 5. 当前学生选课");
		printf("\n\t 6. 查看所有学生选课");
		printf("\n\t 7. 录入课程信息");
		printf("\n\n  请选择: ");
		choice = getche();
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
			inputstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallcourses();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			displayallstudents();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			printf("请输入您的姓名，回车结束:");
			scanf("%s", curstuname);
			findstudentbyname(curstuname, &curstu);
			printf("当前学生姓名：%s\n", curstuname);
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			selectcourses(curstu);
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			displayallstuselcourses();
			break;
		case '7':
			printf("\n\n你选择了 6\n");
			inputcourses();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}