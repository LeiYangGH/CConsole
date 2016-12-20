#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
//#define FILE_STU "sample.txt"
//#define FILE_BEST "best.txt"
//#define FILE_SCORES "scores.txt"
//#define FILE_ANALYSIS "analysis.txt"
#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c, stu.total, stu.average
#define STU_MEMBERS_NET stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c
typedef struct student
{
	int no;
	char name[50];
	int math;
	int english;
	int chinese;
	int c;
	int total;
	float average;
}student;

student allstudents[100];
student sortstudents[100];
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

int tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf(FORMATNET, STU_MEMBERS_NET);
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
			stu.no = toint(part);
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
		case 6:
			stu.c = toint(part);
			break;
		case 7:
			stu.total = toint(part);
			break;
		case 8:
			stu.average = tofloat(part);
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
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
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
		sortstudents[i] = allstudents[i];
	}
	qsort(sortstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("排序后如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(sortstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

int below60()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total < 60)
			c++;
	}
	return c;
}

int below60_80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 60 && allstudents[i].total < 80)
			c++;
	}
	return c;
}

int above80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 80)
			c++;
	}
	return c;
}

float ave()
{
	int i;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
		sum += allstudents[i].total;
	return sum / (float)allstudentscount;
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入姓名,输入q退出查询:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

int searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
			return allstudents[i].average;
	printf("没找到对应学生的信息。\r\n");
	return 0;
}

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	printf("学生%s的成绩为%d：", name, searchtotalbyname(name));
	return strcmp(name, "q");
}



int searchtotalbyno(int no)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (allstudents[i].no == no)
			return allstudents[i].average;
	printf("没找到对应学生的信息。\r\n");
	return 0;
}

void promptsearchtotalbyno()
{
	int no;
	printf("请输入要查询的学号:");
	scanf("%d", &no);
	printf("学号%d的成绩为%d：", no, searchtotalbyno(no));
}

//输入成绩信息
void inputname(char str[])
{
	//int len = -1;
	//while (len < 2 || len > 49)
	//{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	//	scanf("%s", str);
	//	len = strlen(str);
	//}
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
	fprintf(fp, FORMATNET, 33, "Smile", 13, 23, 33, 43);
	fprintf(fp, FORMATNET, 44, "Lukas", 14, 24, 34, 44);
	fprintf(fp, FORMATNET, 55, "Shawn", 15, 25, 35, 45);
	fprintf(fp, FORMATNET, 22, "Tony", 12, 22, 32, 42);
	fprintf(fp, FORMATNET, 11, "Flex", 11, 21, 31, 41);
	fclose(fp);
	printf("5条示例成绩数据已保存到student.txt。\n");
}



int getstudentidexbyid(int no)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (b.no == no)
			return i;
	}
}

void removestudent(int no)
{
	int i;
	int index;
	index = getstudentidexbyid(no);
	for (i = index; i < allstudentscount - 1; i++)
		allstudents[i] = allstudents[i + 1];
	allstudentscount--;
	printf("删除完毕，剩下%d个。\r\n", allstudentscount);

}

void promptremovestudent()
{
	int no = 99;
	removestudent(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入密码\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
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
		fprintf(fp, FORMATNET, STU_MEMBERS_NET);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}

void addstudent(int no, char name[], int math, int english, int chinese, int c)
{
	student stu;
	stu.no = no;
	strcpy(stu.name, name);
	stu.math = math;
	stu.english = english;
	stu.chinese = chinese;
	stu.c = c;
	allstudents[allstudentscount++] = stu;
}

void calcanddisplaytotalandaverage()
{
	int i;
	student stu;
	printf("所有%d分数如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		allstudents[i].total = stu.total = calctotal(stu.math, stu.english, stu.chinese, stu.c);
		allstudents[i].average = stu.average = calcave(stu.total);
		printf("%d\t%s\t%d\t%.1f\r\n", stu.no, stu.name, stu.total, stu.average);
	}
	printf("--------------------------------------------\r\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("科目:%s 平均分%.1f、及格率百分之%.1f、不及格率百分之%.1f\r\n", subuject,
		(sum / (float)allstudentscount),
		(1 - below60 / (float)allstudentscount)*100.0f,
		(below60 / (float)allstudentscount)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	int i, sum = 0, below60 = 0;
	int scores[100];
	student stu;
	printf("所有科目成绩统计如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].math;
	}
	calcanddisplaysubject("数学", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].english;
	}
	calcanddisplaysubject("英语", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].chinese;
	}
	calcanddisplaysubject("语文", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].c;
	}
	calcanddisplaysubject("C语言", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddstudent()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n请输入学号\n");
	scanf("%d", &no);
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入数学、英语、语文、c语言成绩（整数），空格隔开\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addstudent(no, name, math, english, chinese, c);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;

	/*if (login())
	{
		printf("login ok\n");
	}
	else
		printf("login fail\n");*/

	createsamplestudents();

	readallstudents();
	//printf("\n%d\n", allstudentscount);
	/*promptaddstudent();
	writeallstudents();*/
	/*promptremovestudent();
	writeallstudents();*/
	//promptsearchtotalbyname();
	//promptsearchtotalbyno();

	//displayallstudents();
	calcanddisplaytotalandaverage();
	sortanddisplay();
	calcanddisplayallsubjects();
	//addstudent();
	//writeallstudents();

	//char name[20] = "Miller";
	//deletestudent(delname);

	//viewstudent(name);
	//sortandviewall();

	/*char name[20] = "insert";
	int sc = 55;
	if (insert(head, 3, name, sc))
	printf("\nisnerted\n");*/
	//viewallstudents();
	//while (choice != 0)
	//{
	//	printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
	//	printf("\n\t------------------------------");
	//	printf("\n\n\t 0. 退出 0");
	//	printf("\n\n\t 1. 添加 1");
	//	printf("\n\t 2. 删除 2");
	//	printf("\n\t 3. 查看所有 3");
	//	printf("\n\t 4. 根据姓名查找单个 4");
	//	printf("\n\t 5. 按成绩递增排序 5");
	//	printf("\n\t 6. 插入 6");
	//	printf("\n\t 7. 保存 7");
	//	printf("\n\n 请选择: ");
	//	scanf("%1[01234567]d%*c", &choice);
	//	choice = getche();
	//	switch (choice)
	//	{
	//	case '0':
	//		printf("\n\n 你选择了退出: ");
	//		fseek(stdin, 0, SEEK_END);
	//		system("pause");
	//		exit(0);
	//		break;
	//	case '1':
	//		printf("\n\n你选择了 1\n");
	//		addstudent();
	//		break;
	//	case '2':
	//		printf("\n\n你选择了 2\n");
	//		promptdeletebyname();
	//		break;
	//	case '3':
	//		printf("\n\n你选择了 3\n");
	//		viewallstudents();
	//		break;
	//	case '4':
	//		printf("\n\n你选择了 4\n");
	//		promptsearchtotalbyname();
	//		break;
	//	case '5':
	//		printf("\n\n你选择了 5\n");
	//		sortandviewall();
	//		break;
	//	case '6':
	//		printf("\n\n你选择了 6\n");
	//		promptinsertbeforeno();
	//		break;
	//	case '7':
	//		printf("\n\n你选择了 7\n");
	//		writeallstudents();
	//		break;
	//	default:
	//		printf("\n\n输入有误，请重选\n");
	//		break;
	//	}
	//	getch();
	//}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

