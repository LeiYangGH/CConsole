#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20

#define TEST 0
typedef struct student
{
	char name[MAX_STRLEN];
	int a;
	int b;
	int c;
	float f;
}student;
student allstudents[100];
int allstudentscount = 0;

int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

float tofloat(char *s)
{
	double temp = strtod(s, NULL);
	return atof(s);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%16s\t%d\t%d\t%d\t%.2f\n", stu.name, stu.a, stu.b, stu.c, stu.f);
}

void displayallstudents()
{
	int i;
	printf("所有%d位球星分数如下\r\n", allstudentscount);
	printf("%16s\t场次1\t进球\t助攻\t效率4\n", "姓名");
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
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.name, part);
			break;
		case 2:
			stu.a = toint(part);
			break;
		case 3:
			stu.b = toint(part);
			break;
		case 4:
			stu.c = toint(part);
			break;
		case 5:
			stu.f = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return stu;
}

int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->b - ((student*)b)->b);
}
void sortbyi2()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);

}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败(按回车键开始输入数据)!", FILE_INPUT);
		getchar();
	}
	else
	{
		allstudentscount = 0;
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allstudentscount;
			allstudents[allstudentscount - 1] = getstudentfromline(line);
		}
		sortbyi2();
	}
}


void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_INPUT, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%.2f\n", stu.name, stu.a, stu.b, stu.c, stu.f);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void addstudent(char name[], int i1, int i2, int i3, float f)
{
	student stu;
	strcpy(stu.name, name);
	stu.a = i1;
	stu.b = i2;
	stu.c = i3;
	stu.f = f;
	allstudents[allstudentscount++] = stu;
	sortbyi2();
	writeallstudents();
}

int promptaddstudent()
{
	char name[MAX_STRLEN] = "";
	int   i1, i2, i3;
	float f;
	printf("\n请输入姓名(end结束):");
	scanf("%s", name);
	if (strcmp(name, "end") == 0)
		return 0;
	else
	{
		printf("\n请输入4项数据，空格隔开，回车结束\n");
		scanf("%d%d%d%f", &i1, &i2, &i3, &f);

		addstudent(name, i1, i2, i3, f);
		printf("完成第%d个球星成绩录入!\r\n", allstudentscount);
		return 1;
	}
}


void promptaddstudentsfirsttime()
{
	if (allstudentscount == 0)
		while (promptaddstudent());
}
void searchtotalbyname(char *name)
{
	int i;
	//先按总分排序
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			printf("%s,第%d名, 详细如下\n", name, allstudentscount - i);
			displaystudent(allstudents[i]);
			return;
		}
	printf("没找到对应球星的信息。\r\n");
}

void promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("请输入要查询的球星姓名:");
	scanf("%s", &name);
	searchtotalbyname(name);
}

int main()
{

#if TEST

	readallstudents();
	promptaddstudentsfirsttime();
	//addstudent("s", 1, 2, 3, 4.4);
	//sorttotal();
	//searchtotalbyname("x1");
	displayallstudents();
	//promptsearchtotalbyname();
	//promptaddstudent();
	//displayallstudents();



#else

	int choice = -1;
	printf("\n开始读文件...\n");
	readallstudents();
	promptaddstudentsfirsttime();
	printf("\n读文件结束！\n");

	while (choice != 0)
	{
		printf("\n\t 球星成绩读入统计");
		printf("\n\t 1. 查看进球榜单");
		printf("\n\t 2. 查找");
		printf("\n\t 3. 增加");
		printf("\n\t 4. 退出");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '1':
			printf("\n\n你选择了 1\n");
			displayallstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptsearchtotalbyname();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptaddstudent();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
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
#endif
	system("pause");
	return 0;
}
