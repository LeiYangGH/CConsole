//C语言课程设计，用c语言设计一户籍管理系统，求所写代码要求:
//户籍信息包括身份证号、姓名、性别、年龄、学历、住址、电话等（身份证号不重复）。
//试设计一户籍管理系统，该系统具有如下功能：
//1. 户籍信息录入功能(户籍信息用文件保存，并可在电脑中直接查找并打开该文件）
//	2．户籍信息浏览功能
//	3．按年龄排序
//	4．按年龄区间查询
//	5．户籍信息删除
//	6．户籍信息修改

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_STU "stu.txt"
#define MAX_STRLEN 20
typedef struct student
{
	char snum[20];
	char name[20];
	char birthday[20];
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


//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}


void displaystudent(student stu)
{
	printf("%s\t%s\t%s\t%d\t%d\t%d\n", stu.snum, stu.name, stu.birthday, stu.chinese, stu.math, stu.english);
}

void displayallstudents()
{
	int i;
	printf("所有%d位同学信息如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行文本读入并根据\t符号拆分，组合成一个student
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.snum, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			strcpy(stu.birthday, part);
			break;
		case 4:
			stu.math = toint(part);
			break;
		case 5:
			stu.english = toint(part);
			break;
		case 6:
			stu.chinese = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return stu;
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_STU);
	}
	else
	{
		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n已读入文件!", FILE_STU);
	}
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

//根据编号查数组里的序号
int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].snum, no))
			return i;
	}
	return -1;//没找到
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
		fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%d\n", stu.snum, stu.name, stu.birthday, stu.math, stu.english, stu.chinese);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void editstudent(char no[50])
{
	int i;
	char pwd[20] = "";
	i = getstudentidexbyno(no);
	if (i >= 0)
	{
		printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
		scanf("%d%d%d", &allstudents[i].chinese, &allstudents[i].math, &allstudents[i].english);
		writeallstudents();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应学号的学生。\r\n");
	}
}

void prompteditstudent()
{
	char no[50];
	printf("请输入要修改的学号:");
	scanf("%s", &no);
	editstudent(no);
}

void addstudent(char no[50], char name[], char birthday[], int chinese, int math, int english)
{
	student stu;
	strcpy(stu.snum, no);
	strcpy(stu.name, name);
	strcpy(stu.birthday, birthday);
	stu.chinese = chinese;
	stu.math = math;
	stu.english = english;
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

void promptaddstudent()
{
	char no[50];
	char name[MAX_STRLEN] = "";
	char birthday[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n请输入学号、姓名、和生日（都是不带空格的字符串），空格隔开\n");
	scanf("%s%s%s", no, name, birthday);
	printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, birthday, chinese, math, english);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
}

void promptaddallstudent()
{
	int i, count;
	char no[50];
	char name[MAX_STRLEN] = "";
	char birthday[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n请输入要输入多少位学生信息(1-10):");
	scanf("%d", &count);
	allstudentscount = 0;
	for (i = 0; i < count; i++)
	{
		promptaddstudent();
	}
}

void promptaddallorreadstudent()
{
	char choice = -1;
	fseek(stdin, 0, SEEK_END);
	printf("请选择手动输入(h)、读文件(r)、还是放弃(q)：");
	choice = getchar();
	if (choice == 'q')
		return;
	if (allstudentscount > 0)
	{
		printf("\n注意：目前已经有%d位学生信息，重新读入或创建会覆盖原来的记录！");
	}
	if (choice == 'h')
		promptaddallstudent();
	else if (choice == 'r')
		readallstudents();
}

void removestudent(char no[20])
{
	int i;
	int index;
	index = getstudentidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allstudentscount - 1; i++)
			allstudents[i] = allstudents[i + 1];
		allstudentscount--;
		writeallstudents();
		printf("删除完毕，剩下%d个。\r\n", allstudentscount);
	}
	else
	{
		printf("没找到对应学号的学生。\r\n");
	}

}

void promptremovestudent()
{
	char no[20];
	printf("请输入要删除的学号:");
	scanf("%s", no);
	removestudent(no);
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
	char choice = -1;
#if 0//测试用，if块可删除
	readallstudents();
	//addstudent("05", "n5", "20170605", 41, 92, 93);
	//addstudent("06", "n6", "20170606", 46, 96, 96);

	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	promptaddallstudent();
	displayallstudents();
	//promptsearchbyname();
	//sortstudentsbytotal();
	//prompteditstudent();
	//promptremovestudent();
	//displayallstudents();


	system("pause");

#endif
	readallstudents();
	while (choice != 'g')
	{
		printf("\n\t 学生信息管理系统");
		printf("\n\t 0---学生信息的创建");
		printf("\n\t 1---学生信息的排序");
		printf("\n\t 2---学生信息的增加");
		printf("\n\t 3---学生信息的删除");
		printf("\n\t 4---学生信息的修改");
		printf("\n\t 5---学生信息的查找");
		printf("\n\t 6---学生信息的浏览");
		printf("\n\t 7---退出\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n你选择了 0\n");
			promptaddallorreadstudent();
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			sortstudentsbytotalanddisplay();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaddstudent();
			break;
		case '3':
			printf("\n\n你选择了 c\n");
			promptremovestudent();
			break;
		case '4':
			printf("\n\n你选择了 d\n");
			prompteditstudent();
			break;
		case '5':
			printf("\n\n你选择了 e\n");
			promptsearchbyname();
			break;
		case '6':
			printf("\n\n你选择了 f\n");
			displayallstudents();
			break;
		case '7':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
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

