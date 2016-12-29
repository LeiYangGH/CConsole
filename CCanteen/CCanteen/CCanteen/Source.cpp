#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //调试时候1， 发布时候0
#define MAX_COUNT 20 //暂定最多20条数据，随便改
#define MAX_STRLEN 20 //字符串最长长度
#define FORMAT_STU "%d\t%s\t%s\n"
#define MEMBERS_STU stu.no, stu.name, stu.sex
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\n"
#define MEMBERS_CU cu.no, cu.name
#define LINE  "\n------------------------\n"

typedef struct student
{
	int no;
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
}student;
typedef struct rentcd
{
	int cdno;
	char cdname[MAX_STRLEN];
	int cuno;
	char cuname[MAX_STRLEN];
	int days;
	int isreturned;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
}customer;
//所有数据都存储在下面这3个结构体数组里面
student allstudents[MAX_COUNT];
int allstudentscount = 0;

rentcd allrentcds[MAX_COUNT];
int allrentcdscount = 0;

customer allcustomers[MAX_COUNT];
int allcustomerscount = 0;

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

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
}
//display all显示全部，调用displaystudent显示单行，下同
void displayallstudents()
{
	int i;
	printf("所有学生情况如下\n");
	printf("编号\t名称\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf(LINE);
}
void displayrentcd(rentcd rcd)
{
	printf(FORMAT_RCD, MEMBERS_RCD);
}

void displayallrentcds()
{
	int i;
	printf("所有学生租借情况如下\n");
	printf("学生\t客户\t天数\n");
	printf(LINE);
	for (i = 0; i < allrentcdscount; i++)
	{
		if (allrentcds[i].isreturned == 0)
			displayrentcd(allrentcds[i]);
	}
}
//添加单个
void addstudent(int no, char *name, char *sex)
{
	student stu;
	stu.no = no;
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
}

//要求用户输入，输入后调用addstudent，下同，分开两个函数是为了测试方便
void inputstudents()
{
	//int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入学生编号(整数，0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入学生名称、性别，逗号分隔，回车结束:");
		scanf("%s%s", name, sex);
		addstudent(no, name, sex);
		printf("\nCD%s信息添加成功!\n", name);
	}
}

void displaycustomer(customer cu)
{
	printf(FORMAT_CU, MEMBERS_CU);
	printf("\n");
}
void displayallcustomers()
{
	int i;
	printf("所有客户如下\n");
	printf("学号\t姓名\n");
	printf(LINE);
	for (i = 0; i < allcustomerscount; i++)
	{
		displaycustomer(allcustomers[i]);
	}
	printf(LINE);
}

void addcustomer(int no, char *name)
{
	int i;
	customer cu;
	cu.no = no;
	strcpy(cu.name, name);
	allcustomers[allcustomerscount++] = cu;
}

void inputcustomers()
{
	int i, no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入客户编号，不重复自然数(0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入客户姓名:");
		scanf("%s", name);
		addcustomer(no, name);
		printf("\n客户%s信息添加成功!\n", name);
	}
}

//通过名称查找stu，传进来的是student的指针，下同
void findstudentbyname(char *cdname, student **stu)
{
	int i;
	int found = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, cdname))
		{
			*stu = &allstudents[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到名称为%s的学生\n", cdname);
		*stu = NULL;
	}
}

void findcustomerbyname(char *cuname, customer **cu)
{
	int i;
	int found = 0;
	for (i = 0; i < allcustomerscount; i++)
	{
		if (streq(allcustomers[i].name, cuname))
		{
			*cu = &allcustomers[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到姓名为%s的客户\n", cuname);
		*cu = NULL;
	}
}

//假设一定能找到
void findcunamebycdname(char *cdname, char *cuname)
{
	int i;
	for (i = 0; i < allrentcdscount; i++)
	{
		if (streq(allrentcds[i].cdname, cdname))
		{
			strcpy(cuname, allrentcds[i].cuname);
			break;
		}
	}
}






int main()
{
	int choice = -1;

	//下面这些是测试时方便测试的，可以删除
	addstudent(1, "cd1", "F");
	addstudent(2, "cd2", "F");
	addstudent(3, "cd3", "M");

	addcustomer(1, "cust1");
	addcustomer(2, "cust2");


	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");

#if DEV
	//下面这些是测试时方便测试的，可以删除
	addstudent(1, "cd1");
	addstudent(2, "cd2");
	addstudent(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	//addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");
#else
	while (choice != 0)
	{
		printf("\n\t 学生选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入学生信息");
		printf("\n\t 2. 查看所有学生");
		printf("\n\t 3. 录入客户信息");
		printf("\n\t 4. 查看所有客户");
		printf("\n\t 5. 出租学生");
		printf("\n\t 6. 查看所有学生出租情况");
		printf("\n\t 7. 查看某位客户学生出租情况");
		printf("\n\t 8. 归还学生");
		printf("\n\n  请选择: ");
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
			inputstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			inputcustomers();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallcustomers();
			break;
			//case '5':
			//	printf("\n\n你选择了 5\n");
			//	inputrent();
			//	break;
			//case '6':
			//	printf("\n\n你选择了 6\n");
			//	displayallrentcds();
			break;
			//case '7':
			//	printf("\n\n你选择了 7\n");
			//	inputanddisplayonecustomerrentcds();
			//	break;
			//case '8':
			//	printf("\n\n你选择了 8\n");
			//	inputreturn();
			//	break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}