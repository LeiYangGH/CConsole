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
#define FILE_per "s.txt"
#define MAX_STRLEN 20
//编号，姓名、基本工资、奖金、保险、实发工资
typedef struct salary
{
	char no[20];
	char name[20];
	int basic;
	int bonus;
	int insurance;
	int real;
}salary;

salary allsalarys[100];
int allsalaryscount = 0;

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


void displaysalary(salary per)
{
	printf("%s\t%s\t%d\t%d\t%d\t%d\n", s.no, s.name, s.basic, s.bonus, s.insurance, s.real);
}
void displayallsalarys()
{
	int i;
	printf("所有%d位员工工资信息如下\r\n", allsalaryscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsalaryscount; i++)
	{
		displaysalary(allsalarys[i]);
	}
	printf("--------------------------------------------\r\n");
}

void setreal(salary *s)
{
	s->real = s->basic + s->bonus - s->insurance;
}

//从一行文本读入并根据\t符号拆分，组合成一个salary
salary getsalaryfromline(char *line)
{
	char *part;
	int index = 0;
	salary per;
	s.real = 0;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(s.no, part);
			break;
		case 2:
			strcpy(s.name, part);
			break;
		case 3:
			s.basic = toint(part);
			break;
		case 4:
			s.bonus = toint(part);

			break;
		case 5:
			s.insurance = toint(part);
			break;
		case 6:
			s.real = toint(part);
			break;
		case 7:
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	if (s.real == 0)
		setreal(&per);
	return per;
}

void readallsalarys()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
	}
	else
	{
		allsalaryscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allsalarys[allsalaryscount++] = getsalaryfromline(line);
		}
		printf("\n已读入文件!", FILE_per);
	}
}

//qsort是快速排序，要求如下写法，根据age排序
int cmpfunc(const void * b, const void * a)
{
	return ((salary*)a)->basic - ((salary*)b)->basic;
}

void sortsalarysbyageanddisplay()
{
	int i;
	qsort(allsalarys, allsalaryscount, sizeof(salary), cmpfunc);
	printf("按每个员工基本工资排序后如下\r\n");
	displayallsalarys();
}

//根据编号查数组里的序号
int getsalaryidexbyname(char name[50])
{
	int i;
	for (i = 0; i < allsalaryscount; i++)
	{
		if (streq(allsalarys[i].name, name))
			return i;
	}
	return -1;//没找到
}

void writeallsalarys()
{
	int i;
	salary per;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allsalaryscount; i++)
	{
		per = allsalarys[i];
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", s.no, s.name, s.basic, s.bonus, s.insurance, s.real);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void editsalary(char id[50])
{
	int i;
	i = getsalaryidexbyname(id);
	if (i >= 0)
	{
		printf("\n请输入新的基本工资、奖金、保险（都是正整数），空格隔开\n");
		scanf("%d%d%d", &allsalarys[i].basic, &allsalarys[i].bonus, &allsalarys[i].insurance);
		setreal(&allsalarys[i]);
		writeallsalarys();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应姓名的员工。\r\n");
	}
}

void prompteditsalary()
{
	char name[50];
	printf("请输入要修改工资的员工姓名:");
	scanf("%s", &name);
	editsalary(name);
}



int main()
{
	char choice = -1;
#if 0//测试用，if块可删除
	readallsalarys();
	//addsalary("05", "n5", "20170605", 41, 92, 93);
	//addsalary("06", "n6", "20170606", 46, 96, 96);

	//editsalary("01");
	////printf("\n%d\n", allsalaryscount);
	displayallsalarys();
	promptaddsalary();
	displayallsalarys();
	//promptsearchbetweenage();
	//prompteditsalary();
	//writeallsalarys();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//promptremovesalary();
	//sortsalarysbytotalanddisplay();
	//displayallsalarys();
	//sortsalarysbytotal();
	//prompteditsalary();
	//displayallsalarys();


	system("pause");

#endif
	readallsalarys();
	while (choice != 0)
	{
		printf("\n\t 员工工资信息管理系统");
		printf("\n\t 0---退出");
		printf("\n\t 1---户籍信息录入");
		printf("\n\t 2---户籍信息浏览");
		printf("\n\t 3---按年龄排序");
		printf("\n\t 4---按年龄区间查询");
		printf("\n\t 5---户籍信息删除");
		printf("\n\t 6---户籍信息修改");
		printf("\n请选择:");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0); break;
		case '1':
			printf("\n\n你选择了 1\n");
			promptaddsalary();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallsalarys();
			break;
		case '3':
			printf("\n\n你选择了 c\n");
			sortsalarysbyageanddisplay();
			break;
		case '4':
			printf("\n\n你选择了 d\n");
			promptsearchbetweenage();
			break;
		case '5':
			printf("\n\n你选择了 e\n");
			promptremovesalary();
			break;
		case '6':
			printf("\n\n你选择了 f\n");
			prompteditsalary();
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

