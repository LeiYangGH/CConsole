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
	float average;
}student;
//char *coursenames[3] = { "语文","数学", "英语" };
student allstudents[100];
int allstudentscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "stu.txt";
student *head;

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
			/*case 6:
				stu.c = toint(part);
				break;
			case 7:
				stu.total = toint(part);
				break;
			case 8:
				stu.average = tofloat(part);
				break;*/
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
void sorttotal()
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
	sorttotal();
	printf("排序后如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}




void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入姓名:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}


//输入成绩信息
void inputname(char str[])
{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	scanf("%s", str);
	printf("您输入的姓名为为 %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("请输入分数1～100:");
		scanf("%d", &n);
	}
	return n;
}



int getstudentidexbyid(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (streq(b.no, no))
			return i;
	}
	return -1;
}

void editstudent(char no[50])
{
	int i;
	i = getstudentidexbyid(no);
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
	scanf("%d", &no);
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


void addstudent(char no[50], char name[], int math, int english, int chinese)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.math = math;
	stu.english = english;
	stu.chinese = chinese;
	allstudents[allstudentscount++] = stu;
}




void promptaddstudent()
{
	char no[50]; char name[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n请输入学号\n");
	scanf("%d", &no);
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入语文、数学、英语成绩（整数），空格隔开\n");
	scanf("%d%d%d%d", &chinese, &math, &english);
	addstudent(no, name, math, english, chinese);
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


int main()
{
	int choice = -1;

#if 1
	//readallstudents();

	addstudent("04", "n4", 41, 92, 43);
	addstudent("01", "n1", 11, 12, 13);
	addstudent("02", "n2", 21, 22, 93);
	addstudent("05", "n5", 51, 52, 53);
	addstudent("06", "n6", 61, 62, 63);
	addstudent("03", "n3", 31, 32, 33);
	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	calcanddisplaycoursehighest();
	system("pause");

#endif
	while (choice != 0)
	{
		char *menu = "**********************菜单****************************\n"
			"按1键：读入学生档案               按6键：学科及格概率\n"
			"按2键：按照姓名查询               按7键：学生档案排序\n"
			"按3键：按照学号查询               按8键：保存学生档案\n"
			"按4键：添加学生档案               按9键 : 查看学生档案\n"
			"按5键：修改学生档案               按10键：求各科平均分\n"
			"按0键：退出管理系统";
		printf("请输入选择数字，并回车\n", menu);
		printf("%s\n", menu);
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			system("pause");
			exit(0);
			break;
		case 1:
			readallstudents();
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			promptaddstudent();
			break;
		case 5:
			prompteditstudent();
			break;
		case 6:

			break;
		case 7:
			sortanddisplay();
			break;
		case 8:
			writeallstudents();
			break;
		case 9:
			sortanddisplay();
			break;
		case 10:


			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	printf("\n\n按任意键退出\n");
	system("pause");
	return 0;
}

