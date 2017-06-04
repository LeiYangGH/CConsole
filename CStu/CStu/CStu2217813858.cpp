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

int main()
{
	char choice = -1;
#if 1//测试用，if块可删除
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

	displayallstudents();
	//sortstudentsbytotal();
	//prompteditstudent();
	promptremovestudent();
	displayallstudents();


	system("pause");

#endif
	readallstudents();
	while (choice != 'g')
	{
		printf("\n\t 请选择系统功能项");
		printf("\n\t a、成绩录入");
		printf("\n\t b、成绩显示");
		printf("\n\t c、成绩保存");
		printf("\n\t d、成绩排序");
		printf("\n\t e、成绩修改");
		printf("\n\t f、成绩统计");
		printf("\n\t    1）显示每门课程成绩最高的学生基本信息");
		printf("\n\t    2）显示每门课程的平均成绩");
		printf("\n\t    3）显示超过某门课程平均成绩的学生人数");
		printf("\n\t g、退出系统\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case 'a':
			printf("\n\n你选择了 a\n");
			promptaddstudent();
			break;
		case 'b':
			printf("\n\n你选择了 b\n");
			displayallstudents();
			break;
		case 'c':
			printf("\n\n你选择了 c\n");
			writeallstudents();
			break;
		case 'd':
			printf("\n\n你选择了 d\n");
			sortstudentsbytotalanddisplay();
			break;
		case 'e':
			printf("\n\n你选择了 e\n");
			prompteditstudent();
			break;
		case 'f':
			printf("\n\n你选择了 f\n");
			break;
		case 'g':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
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

