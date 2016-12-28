#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 1
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
student  curstu;

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
	printf("所有课程情况如下\r\n");
	printf(LINE);
	printf("编号\t名称\t学分\t人数\r\n");
}
//void findcoursebyno(int  no, course **cou)  //根据名字查找学生
//{
//	int found = 0;
//	course *p = couhead;
//
//	while (p != NULL)
//	{
//		if (p->no == no)
//		{
//			*cou = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("没找到编号名为%d的课程\r\n", no);
//		*cou = NULL;
//	}
//}

//void displayonestuselcourses(student *stu)
//{
//	int i;
//	course *cou;
//	printf("学生%s选课%d门如下\r\n", stu->name, stu->selcouscnt);
//	for (i = 0; i < stu->selcouscnt; i++)
//	{
//		findcoursebyno(stu->selcourses[i], &cou);
//		printf("%s\t", cou->name);
//	}
//	printf("\r\n");
//}
//void displayallstuselcourses()
//{
//	student *p = stuhead->next;
//	printf("所有学生选课结果如下\r\n");
//	printf(LINE);
//	while (p != NULL)
//	{
//		displayonestuselcourses(p);
//		p = p->next;
//	}
//}

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






void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()
{
	int i;
	printf("所有学生成绩如下\r\n");
	printf("学号\t姓名\t性别\t总学分\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}


void addstudent(char *no, char *name)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.selcouscnt = 0;
	allstudents[allstudentscount++] = stu;
}

//void inputstudents()
//{
//	int i, score;
//	char no[MAX_STRLEN] = "";
//	char name[MAX_STRLEN] = "";
//	char sex[MAX_STRLEN] = "";
//	student *p1, *p2;
//	stuhead = (student *)malloc(sizeof(student));
//	p1 = p2 = (student *)malloc(sizeof(student));
//	stuhead->next = p1;
//#if DEV
//#else
//	while (1)
//#endif
//	{
//
//#if DEV
//		addstudents(&p1, &p2, "01", "name", "sex");
//		addstudents(&p1, &p2, "02", "ly", "b");
//		addstudents(&p1, &p2, "03", "sm", "g");
//#else
//		printf("\n\n请输入学生学号(q结束):");
//		scanf("%s", &no);
//		if (streq(no, "q"))
//		{
//			printf("\n您已结束输入！");
//			break;
//	}
//		printf("\n请输入学生姓名:");
//		scanf("%s", name);
//		printf("\n请输入学生性别:");
//		scanf("%s", sex);
//		addstudents(&p1, &p2, no, name, sex);
//#endif
//		printf("\n学生%s信息添加成功!\n", name);
//}
//	p2->next = NULL;
//}


//void findstudentbyname(char *name, student **stu)
//{
//	int found = 0;
//	student *p = stuhead;
//
//	while (p != NULL)
//	{
//		if (streq(p->name, name))
//		{
//			*stu = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("没找到姓名为%s的学生\r\n", name);
//		*stu = NULL;
//	}
//}

//int selectonecourse(student *stu, int couno)
//{
//	course *cou;
//
//	if (stu->selcouscnt >= 5)
//	{
//		printf("选课不能超过5门\r\n");
//		return 0;
//	}
//	findcoursebyno(couno, &cou);
//	if (cou != NULL)
//	{
//		if (cou->stucnt < cou->no)
//		{
//			stu->selcourses[stu->selcouscnt] = couno;
//			stu->totalpoints += cou->points;
//			stu->selcouscnt++;
//			cou->stucnt++;
//			printf("选课成功！\r\n");
//			return 1;
//		}
//		else
//		{
//			printf("课程%s已经选满！\r\n", cou->name);
//			return 0;
//		}
//	}
//}
//
//void selectcourses(student *stu)
//{
//	int no;
//	if (stu == NULL)
//	{
//		printf("请先输入姓名再选课！\n");
//		return;
//	}
//	do
//	{
//		printf("请输入要选择的课程号（1～7），0结束选择：");
//		scanf("%d", &no);
//		fseek(stdin, 0, SEEK_END);
//		if (no == 0)
//		{
//			if (stu->selcouscnt >= 3)
//			{
//				printf("你已退出了课程选择。\n");
//				break;
//			}
//			else
//			{
//				printf("必须选满至少3门课程！\n");
//			}
//		}
//		selectonecourse(stu, no);
//	} while (stu->selcouscnt <= 5);
//	printf("选课结束。\n");
//}
//



int main()
{
	int choice = -1;
#if DEV
	addstudent("001", "n1");
	addstudent("002", "ly");
	addstudent("003", "n3");
	strcpy(curstuname, "ly");
	//displayallcourses();
	//inputstudents();
	displayallstudents();
	//findstudentbyname(curstuname, &curstu);
	/*selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	selectonecourse(curstu, 3);
	selectonecourse(curstu, 4);
	selectonecourse(curstu, 5);
	selectonecourse(curstu, 6);*/
	//findstudentbyname("sm", &stu);
	/*selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);*/
	//displayallstuselcourses();
	//sortanddisplayallstudents();
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
		printf("\n\t 7. 学生按学分总积分排列输出");
		printf("\n\t 8. 输入所有学生成绩");
		printf("\n\t 9. 一门和三门功课不及格的学生");
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
			printf("\n\n你选择了 7\n");
			sortanddisplayallstudents();
			break;
		case '8':
			printf("\n\n你选择了 8\n");
			inputallstuscores();
			break;
		case '9':
			printf("\n\n你选择了 9\n");
			listallnamesbelow60forcou(1);
			listallnamesbelow60forcou(3);
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