#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
#define MAX_STRLEN 20
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
			stu.math = toint(part);
			break;
		case 4:
			stu.english = toint(part);
			break;
		case 5:
			stu.chinese = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
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

int cmpfunc(const void * a, const void * b)
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

void sortanddisplay()
{
	int i;
	sortstudentsbytotal();
	printf("按每个学生各科平均成绩排序后如下\r\n");
	displayallstudents();
}

int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].no, no))
			return i;
	}
	return -1;
}

void editstudent(char no[50])
{
	int i;
	i = getstudentidexbyno(no);
	if (i >= 0)
	{
		printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
		scanf("%d%d%d", &allstudents[i].chinese, &allstudents[i].math, &allstudents[i].english);
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
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.math, stu.english, stu.chinese);
	}
	fclose(fp);
	printf("已保存记录到文件。");
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
	char no[50]; char name[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n请输入学号和姓名，空格隔开\n");
	scanf("%s%s", no, name);
	printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, chinese, math, english);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
}

void calcanddisplaycoursehighest()
{
	int i, t, index, h;

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].chinese;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("语文最高分:%d\t学生:%s\n", h, allstudents[index].name);

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].math;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("数学最高分:%d\t学生:%s\n", h, allstudents[index].name);

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].english;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("英语最高分:%d\t学生:%s\n", h, allstudents[index].name);
}

void calccoursesaverages()
{
	int i, sum;
	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].chinese;
	}
	averagechinese = sum / (float)allstudentscount;

	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].math;
	}
	averagemath = sum / (float)allstudentscount;

	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].english;
	}
	averageenglish = sum / (float)allstudentscount;
}

void calccoursesaveragesanddisplay()
{
	calccoursesaverages();
	printf("语文平均分:%.1f\n", averagechinese);
	printf("数学平均分:%.1f\n", averagemath);
	printf("英语平均分:%.1f\n", averageenglish);
}

void calccoursesaveragesbelowcountanddisplay()
{
	int i, c;
	calccoursesaverages();
	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].chinese > averagechinese)
			c++;
	}
	printf("超过语文平均成绩的学生人数:%d\n", c);

	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].math > averagemath)
			c++;
	}
	printf("超过数学平均成绩的学生人数:%d\n", c);

	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].english > averageenglish)
			c++;
	}
	printf("超过英语平均成绩的学生人数:%d\n", c);
}


void menuf()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t    1）显示每门课程成绩最高的学生基本信息");
		printf("\n\t    2）显示每门课程的平均成绩");
		printf("\n\t    3）显示超过某门课程平均成绩的学生人数");
		printf("\n\t  按0返回上级\n");
		fseek(stdin, 0, SEEK_END);//清楚输入缓冲区，以免意外非法输入造成死循环
		choice = getchar();
		switch (choice)
		{
		case '1':
			calcanddisplaycoursehighest();
			break;
		case '2':
			calccoursesaveragesanddisplay();
			break;
		case '3':
			calccoursesaveragesbelowcountanddisplay();
			break;
		default:
			printf("\n\n输入有误!");
			break;
		}
	}
}

int main()
{
	char choice = -1;


#if 0
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
			sortanddisplay();
			break;
		case 'e':
			printf("\n\n你选择了 e\n");
			prompteditstudent();
			break;
		case 'f':
			printf("\n\n你选择了 f\n");
			menuf();
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

