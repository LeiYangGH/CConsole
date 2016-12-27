#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 1
#define COU_CNT 7
#define MAX_STRLEN 20
#define N 5
//下面两个格式，为了方便，利用了N=5，写死了
#define FORMAT_COU "%d\t%s\t%d\t%d\r\n"
#define MEMBERS_COU cou.no, cou.name, cou.points, cou.stucnt

#define FORMAT_STU "%s\t%s\t%s\t%d\r\n"
//#define FORMAT_STU "%s\t%s\t%s\t%d\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.2f\r\n"
#define MEMBERS_STU stu.no, stu.name, stu.sex, stu.totalpoints, stu.supplement
#define LINE  "\n------------------------\n"

//#define N 2

typedef struct course
{
	int no;
	char name[10];
	int points;
	//int maxstucnt;
	int stucnt;
	struct course  *next;
}course;
char *coursefile = "courses.txt";
course *couhead;

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
	float scores[COU_CNT];
	int selcourses[COU_CNT];
	int selcouscnt;
	int totalpoints;
	char supplement[MAX_STRLEN];
	struct student  *next;
}student;
student *stuhead;

char curstuname[MAX_STRLEN];
student * curstu;

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
	course *p = couhead->next;
	printf("所有课程情况如下\r\n");
	printf(LINE);
	while (p != NULL)
	{
		displaycourse(*p);
		p = p->next;
	}
}
void findcoursebyno(int  no, course **cou)  //根据名字查找学生
{
	int found = 0;
	course *p = couhead;

	while (p != NULL)
	{
		if (p->no == no)
		{
			*cou = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("没找到编号名为%d的课程\r\n", no);
		*cou = NULL;
	}
}
/////////////
void displayonestuselcourses(student *stu)
{
	int i;
	printf("学生%s选课%d门如下\r\n", stu->name, stu->selcouscnt);
	for (i = 0; i < stu->selcouscnt; i++)
	{
		course *cou;
		findcoursebyno(stu->selcourses[i], &cou);
		printf("%s\t", cou->name);
	}
	//printf(FORMAT_COU, MEMBERS_COU);
	printf("\r\n");
}
void displayallstuselcourses()
{
	student *p = stuhead->next;
	printf("所有学生选课结果如下\r\n");
	printf(LINE);
	while (p != NULL)
	{
		displayonestuselcourses(p);
		p = p->next;
	}
}




/////////
void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()  //输出所有学生信息
{
	student *p = stuhead->next;
	printf("所有学生成绩如下\r\n");
	printf("学号\t姓名\t性别\t总学分\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}
//从一行文本拆分出成绩
void getcoursefromline(char *line, course *cou)
{
	char * part;
	int index = 0, courseno;
	part = strtok(line, ",");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			courseno = toint(part);
			break;
		case 2:
			strcpy(cou->name, part);
			break;
		case 3:
			cou->points = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, ",");
	}
	cou->no = courseno;
	cou->stucnt = 0;
}

//读取所有成绩到链表
void readallcourses()
{
	char line[200];
	course *p1, *p2;
	FILE *fp = fopen(coursefile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		fp = fopen(coursefile, "a+");
		getchar();
	}

	p1 = p2 = (course *)malloc(sizeof(course));
	couhead = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//读进来的行去掉末尾换行符，重要
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
		strtok(line, "\n");
		getcoursefromline(line, p1);
		if (couhead == NULL)
			couhead = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (course*)malloc(sizeof(course));
	}
	p2->next = NULL;
}

void addstudents(student **p1, student **p2, char *no, char *name, char *sex)
{
	strcpy((*p1)->no, no);
	strcpy((*p1)->name, name);
	strcpy((*p1)->sex, sex);
	strcpy((*p1)->supplement, "");
	(*p1)->totalpoints = 0;
	(*p1)->selcouscnt = 0;
	(*p2)->next = (*p1);
	(*p2) = (*p1);
	(*p1) = (student*)malloc(sizeof(student));

}

void inputstudents()
{
	int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	student *p1, *p2;
	stuhead = (student *)malloc(sizeof(student));
	p1 = p2 = (student *)malloc(sizeof(student));
	stuhead->next = p1;
#if DEV
#else
	while (1)
#endif
	{
		//printf("\n\n请输入学生学号(q结束):");
		//scanf("%s", &no);
		//if (streq(no, "q"))
		//{
		//	printf("\n您已结束输入！");
		//	break;
		//}
		//printf("\n请输入学生姓名:");
		//scanf("%s", name);
		//strcpy(p1->no, no);
		//strcpy(p1->name, name);
		//for (i = 0; i < N; i++)
		//{
		//	printf("\n请输入第%d门课程成绩:", i + 1);
		//	scanf("%d", &score);
		//	p1->score[i] = score;
		//}
		//p1->score[N] = 0;
		//p2->next = p1;
		//p2 = p1;
#if DEV
		addstudents(&p1, &p2, "01", "name", "sex");
		addstudents(&p1, &p2, "02", "ly", "b");
		addstudents(&p1, &p2, "03", "sm", "g");
#else
#endif
		printf("\n学生%s信息添加成功!\n", name);
	}
	p2->next = NULL;
}

int deletestudentbyno(student *L, char * no)
{
	student *p1 = L, *p2;
	if (L == NULL)
	{
		printf("\n学生链表为空!\n");
		return 0;
	}
	while (!streq(p1->no, no) && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (streq(p1->no, no))
	{
		if (p1 == L)
			L = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("已删除学号为%s的学生的成绩。\r\n", no);
			return 1;
		}
	}
	else
	{
		printf("没找到学号为%s的学生!\r\n", no);
		return 0;
	}
}

//新增成绩
void calcaverage(student *L)
{
	/*int i;
	float sum;
	student *n;
	n = L;
	while (n != NULL)
	{
		sum = 0;
		for (i = 0; i < N; i++)
		{
			sum += n->score[i];
		}
		n->score[N] = sum / N;
		n = n->next;
	}
	printf("平均成绩计算完毕\r\n");*/
}






void findstudentbyname(char *name, student **stu)  //根据名字查找学生
{
	int found = 0;
	student *p = stuhead;

	while (p != NULL)
	{
		if (streq(p->name, name))
		{
			*stu = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("没找到姓名为%s的学生\r\n", name);
		*stu = NULL;
	}
}

int selectonecourse(student *stu, int couno)
{
	course *cou;

	if (stu->selcouscnt >= 5)
	{
		printf("选课不能超过5门\r\n");
		return 0;
	}
	findcoursebyno(couno, &cou);
	if (cou != NULL)
	{
		if (cou->stucnt < cou->no)
		{
			stu->selcourses[stu->selcouscnt++] = couno;
			cou->stucnt++;
			printf("选课成功！\r\n");
			return 1;
		}
		else
		{
			printf("课程%s已经选满！\r\n", cou->name);
			return 0;
		}
	}
}

void selectcourses(student *stu)
{
	student *p = stuhead->next;
	printf("所有学生成绩如下\r\n");
	printf("学号\t姓名\t性别\t总学分\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}


int main()
{
	int choice = -1;
	student *stu;
#if DEV
	strcpy(curstuname, "ly");
	readallcourses();
	displayallcourses();
	inputstudents();
	displayallstudents();
	findstudentbyname(curstuname, &curstu);
	selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	selectonecourse(curstu, 3);
	selectonecourse(curstu, 4);
	selectonecourse(curstu, 5);
	selectonecourse(curstu, 6);
	findstudentbyname("sm", &stu);
	selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);
	displayallstuselcourses();
#else
	char no[MAX_STRLEN] = "";
	student *L;
	while (choice != 0)
	{
		printf("\n\t 学生成绩录入删除计算");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入学生成绩");
		printf("\n\t 2. 计算平均");
		printf("\n\t 3. 根据学号删除");
		printf("\n\t 4. 查看所有成绩");
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
			L = inputstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			calcaverage(L);
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			printf("\n\n请输入学生学号:");
			scanf("%s", &no);
			deletestudentbyno(L, no);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallstudents(L);
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