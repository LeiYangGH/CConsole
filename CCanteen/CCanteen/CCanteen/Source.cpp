#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //调试时候1， 发布时候0
#define MAX_COUNT 20 //暂定最多20条数据，随便改
#define MAX_STRLEN 20 //字符串最长长度
#define FORMAT_STU "%s\t%s\t%s\r\n" //\r is for write
#define MEMBERS_STU stu.no, stu.name, stu.sex
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\n"
#define MEMBERS_CU cu.no, cu.name
#define LINE  "\n------------------------\n"
#define FILE_STU "stu.txt"
typedef struct student
{
	char no[MAX_STRLEN];
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
void addstudent(char * no, char *name, char *sex)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
}

//要求用户输入，输入后调用addstudent，下同，分开两个函数是为了测试方便
void inputstudents()
{
	//int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入学生编号(整数，q结束):");
		scanf("%s", no);
		if (streq(no, "q"))
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
			strcpy(stu.sex, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void createsamplestudents()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("创建示例成绩数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMAT_STU, "01", "smile", "F");
	fprintf(fp, FORMAT_STU, "02", "lukas", "M");
	fprintf(fp, FORMAT_STU, "03", "shawn", "F");
	fprintf(fp, FORMAT_STU, "04", "tony", "M");
	fprintf(fp, FORMAT_STU, "05", "flex", "F");
	fclose(fp);
	printf("5条示例成绩数据已保存到student.txt。\n");
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!\n", FILE_STU);
		createsamplestudents();
		fp = fopen(FILE_STU, "r");
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
	}
	printf("\n已读入文件!", FILE_STU);

}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, FORMAT_STU, MEMBERS_STU);
	}
	fclose(fp);
	printf("已保存记录到文件。");
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
	//createsamplestudents();
	readallstudents();
	displayallstudents();

#if DEV
	//下面这些是测试时方便测试的，可以删除

#else
	while (choice != 0)
	{
		printf("\n\t 学生选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 增加学生信息");
		printf("\n\t 2. 查看所有学生");
		/*printf("\n\t 3. 录入客户信息");
		printf("\n\t 4. 查看所有客户");
		printf("\n\t 5. 出租学生");
		printf("\n\t 6. 查看所有学生出租情况");
		printf("\n\t 7. 查看某位客户学生出租情况");
		printf("\n\t 8. 归还学生");*/
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
			//case '3':
			//	printf("\n\n你选择了 3\n");
			//	inputcustomers();
			//	break;
			//case '4':
			//	printf("\n\n你选择了 4\n");
			//	displayallcustomers();
			//	break;
				//case '5':
				//	printf("\n\n你选择了 5\n");
				//	inputrent();
				//	break;
				//case '6':
				//	printf("\n\n你选择了 6\n");
				//	displayallrentcds();
				//break;
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