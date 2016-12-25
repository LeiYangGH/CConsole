//#include <time.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include <conio.h>
//#define FILE_STU "stu.txt"
////#define FILE_STU "sample.txt"
////#define FILE_BEST "best.txt"
////#define FILE_SCORES "scores.txt"
////#define FILE_ANALYSIS "analysis.txt"
//#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
//#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
//#define MAX_STRLEN 20
//#define QUESTIONS_COUNT 35
//#define STU_MEMBERS_FULL stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c, stu.total, stu.average
//#define STU_MEMBERS_NET stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c
//typedef struct student
//{
//	int no;
//	char name[50];
//	int math;
//	int english;
//	int chinese;
//	int c;
//	int total;
//	float average;
//}student;
//
//student allstudents[100];
//student sortstudents[100];
//int allstudentscount = 0;
//
//int streq(char *s1, char *s2)
//{
//	return strcmp(s1, s2) == 0;
//}
//
////char *FILE_STU = "stu.txt";
//student *head;
//
////字符串转整数
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}
//
//int tofloat(char *s)
//{
//	char *end;
//	return (float)strtol(s, &end, 10);
//}
//
//void displaystudent(student stu)
//{
//	printf("\r\n");
//	printf(FORMATNET, STU_MEMBERS_NET);
//}
//
//void displayallstudents()
//{
//	int i;
//	printf("所有%d分数如下\r\n", allstudentscount);
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		displaystudent(allstudents[i]);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
//student getstudentfromline(char *line)
//{
//	char *part;
//	int index = 0;
//	student stu;
//	part = strtok(line, "\t");
//	while (part != NULL)
//	{
//		switch (++index)
//		{
//		case 1:
//			stu.no = toint(part);
//			break;
//		case 2:
//			strcpy(stu.name, part);
//			break;
//		case 3:
//			stu.math = toint(part);
//			break;
//		case 4:
//			stu.english = toint(part);
//			break;
//		case 5:
//			stu.chinese = toint(part);
//			break;
//		case 6:
//			stu.c = toint(part);
//			break;
//		case 7:
//			stu.total = toint(part);
//			break;
//		case 8:
//			stu.average = tofloat(part);
//			break;
//		default:
//			break;
//		}
//		part = strtok(NULL, "\t");
//	}
//	return stu;
//}
//
//void readallstudents()
//{
//	char line[200];
//	FILE *fp = fopen(FILE_STU, "r");
//	if (fp == NULL)
//	{
//		printf("\n打开文件%s失败!", FILE_STU);
//		getchar();
//		exit(1);
//	}
//	allstudentscount = 0;
//
//	while (fgets(line, 1024, fp) != NULL)
//	{
//		if (strlen(line) < 5)
//			continue;
//		allstudents[allstudentscount++] = getstudentfromline(line);
//	}
//	printf("\n已读入文件!", FILE_STU);
//
//}
//
//int cmpfunc(const void * a, const void * b)
//{
//	return ((student*)a)->total - ((student*)b)->total;
//}
//void sorttotal()
//{
//	int i;
//	for (i = 0; i < allstudentscount; i++)
//	{
//		sortstudents[i] = allstudents[i];
//	}
//	qsort(sortstudents, allstudentscount, sizeof(student), cmpfunc);
//}
//
//void sortanddisplay()
//{
//	int i;
//	sorttotal();
//	printf("排序后如下\r\n");
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		displaystudent(sortstudents[i]);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
//
//
//void countbygrades()
//{
//	int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt60 = 0;
//	student stu;
//	printf("总分分数段人数统计%d分数如下\r\n", allstudentscount);
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		t = allstudents[i].average;
//		if (t >= 90)
//			cnt90++;
//		else if (t >= 75 && t <= 89)
//			cnt7589++;
//		else if (t >= 60 && t <= 74)
//			cnt6074++;
//		else if (t < 60)
//			cnt60++;
//	}
//	printf("90分以上:%d人, 75~89:%d人, 60~74:%d人, 60分以下:%d人\r\n",
//		cnt90, cnt7589, cnt6074, cnt60);
//	printf("--------------------------------------------\r\n");
//}
//
//
//
//float ave()
//{
//	int i;
//	float sum = 0;
//	for (i = 0; i < allstudentscount; i++)
//		sum += allstudents[i].total;
//	return sum / (float)allstudentscount;
//}
//
//void inputstring(char str[])
//{
//	int len = -1;
//	char input[50] = "";
//	while (len < 1 || len > MAX_STRLEN)
//	{
//		printf("请输入姓名:");
//		fseek(stdin, 0, SEEK_END);
//		scanf("%s", input);
//		len = strlen(input);
//	}
//	strcpy(str, input);
//}
//
//void searchtotalbyname(char *name)
//{
//	int i;
//	for (i = 0; i < allstudentscount; i++)
//		if (strcmp(name, allstudents[i].name) == 0)
//		{
//			displaystudent(allstudents[i]);
//			return;
//		}
//	printf("没找到对应学生的信息。\r\n");
//}
//
//int promptsearchtotalbyname()
//{
//	char name[MAX_STRLEN] = "";
//	inputstring(name);
//	searchtotalbyname(name);
//	return strcmp(name, "q");
//}
//
//
//
//void searchtotalbyno(int no)
//{
//	int i;
//	for (i = 0; i < allstudentscount; i++)
//		if (allstudents[i].no == no)
//		{
//			displaystudent(allstudents[i]);
//			return;
//		}
//	printf("没找到对应学生的信息。\r\n");
//}
//
//void promptsearchtotalbyno()
//{
//	int no;
//	printf("请输入要查询的学号:");
//	scanf("%d", &no);
//	searchtotalbyno(no);
//}
//
////输入成绩信息
//void inputname(char str[])
//{
//	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
//	scanf("%s", str);
//	printf("您输入的姓名为为 %s \r\n", str);
//}
//
//int inputscore()
//{
//	int n = -1;
//	while (n < 1 || n > 100)
//	{
//		printf("请输入分数1～100:");
//		scanf("%d", &n);
//	}
//	return n;
//}
//
//void createsamplestudents()
//{
//	FILE *fp = fopen(FILE_STU, "wb");
//	printf("创建示例成绩数据...");
//	if (fp == NULL)
//	{
//		printf("\nerror on open file!");
//		getchar();
//		exit(1);
//	}
//	fprintf(fp, FORMATNET, 33, "Smile", 13, 83, 63, 93);
//	fprintf(fp, FORMATNET, 44, "Lukas", 14, 84, 64, 94);
//	fprintf(fp, FORMATNET, 55, "Shawn", 15, 85, 65, 95);
//	fprintf(fp, FORMATNET, 22, "Tony", 12, 82, 62, 92);
//	fprintf(fp, FORMATNET, 11, "Flex", 11, 81, 61, 91);
//	fclose(fp);
//	printf("5条示例成绩数据已保存到student.txt。\n");
//}
//
//int getstudentidexbyid(int no)
//{
//	int i;
//	for (i = 0; i < allstudentscount; i++)
//	{
//		student b = allstudents[i];
//		if (b.no == no)
//			return i;
//	}
//}
//
//void removestudent(int no)
//{
//	int i;
//	int index;
//	index = getstudentidexbyid(no);
//	for (i = index; i < allstudentscount - 1; i++)
//		allstudents[i] = allstudents[i + 1];
//	allstudentscount--;
//	printf("删除完毕，剩下%d个。\r\n", allstudentscount);
//
//}
//
//void promptremovestudent()
//{
//	int no;
//	printf("请输入要删除的学号:");
//	scanf("%d", &no);
//	removestudent(no);
//}
//
//
//int login()
//{
//	char name[50] = "";
//	char pwd[50] = "";
//	printf("\n请输入用户名\n");
//	scanf("%s", name);
//	printf("\n请输入密码\n");
//	scanf("%s", pwd);
//	return streq(name, "username")
//		&& streq(pwd, "password");
//}
//
//void writeallstudents()
//{
//	int i;
//	student stu;
//	FILE *fp = fopen(FILE_STU, "w+");
//	if (fp == NULL)
//	{
//		printf("\n打开文件%s失败!", FILE_STU);
//		getchar();
//		exit(1);
//	}
//
//
//	for (i = 0; i < allstudentscount; i++)
//	{
//		stu = allstudents[i];
//		fprintf(fp, FORMATNET, STU_MEMBERS_NET);
//	}
//	fclose(fp);
//	printf("已保存记录到文件。");
//}
//
//int calctotal(int math, int english, int chinese, int c)
//{
//	return math + english + chinese + c;
//}
//
//float calcave(int total)
//{
//	return total / 4.0f;
//}
//
//void addstudent(int no, char name[], int math, int english, int chinese, int c)
//{
//	student stu;
//	stu.no = no;
//	strcpy(stu.name, name);
//	stu.math = math;
//	stu.english = english;
//	stu.chinese = chinese;
//	stu.c = c;
//	allstudents[allstudentscount++] = stu;
//}
//
//void calcanddisplaytotalandaverage()
//{
//	int i;
//	student stu;
//	printf("所有各科总分、平均分如下\r\n");
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		stu = allstudents[i];
//		allstudents[i].total = stu.total = calctotal(stu.math, stu.english, stu.chinese, stu.c);
//		allstudents[i].average = stu.average = calcave(stu.total);
//		printf("%d\t%s\t%d\t%.1f\r\n", stu.no, stu.name, stu.total, stu.average);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
//void calcanddisplaysubject(char *subuject, int scores[])
//{
//	int i, sum = 0, below60 = 0;
//	for (i = 0; i < allstudentscount; i++)
//	{
//		sum += scores[i];
//		if (scores[i] < 60)
//			below60++;
//	}
//	printf("科目:%s 平均分%.1f、及格率百分之%.1f、不及格率百分之%.1f\r\n", subuject,
//		(sum / (float)allstudentscount),
//		(1 - below60 / (float)allstudentscount)*100.0f,
//		(below60 / (float)allstudentscount)*100.0f
//	);
//}
//
//
//void calcanddisplayallsubjects()
//{
//	int i, sum = 0, below60 = 0;
//	int scores[100];
//	student stu;
//	printf("所有科目成绩统计如下\r\n");
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		scores[i] = allstudents[i].math;
//	}
//	calcanddisplaysubject("数学", scores);
//
//	for (i = 0; i < allstudentscount; i++)
//	{
//		scores[i] = allstudents[i].english;
//	}
//	calcanddisplaysubject("英语", scores);
//
//	for (i = 0; i < allstudentscount; i++)
//	{
//		scores[i] = allstudents[i].chinese;
//	}
//	calcanddisplaysubject("语文", scores);
//
//	for (i = 0; i < allstudentscount; i++)
//	{
//		scores[i] = allstudents[i].c;
//	}
//	calcanddisplaysubject("C语言", scores);
//	printf("--------------------------------------------\r\n");
//}
//
//void promptaddstudent()
//{
//	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
//	printf("\n请输入学号\n");
//	scanf("%d", &no);
//	printf("\n请输入用户名\n");
//	scanf("%s", name);
//	printf("\n请输入数学、英语、语文、c语言成绩（整数），空格隔开\n");
//	scanf("%d%d%d%d", &math, &english, &chinese, &c);
//	addstudent(no, name, math, english, chinese, c);
//	printf("完成第%d个入库录入!\r\n", allstudentscount);
//}
//
//
//int main0()
//{
//	int choice = -1;
//
//	/*if (login())
//	{
//		printf("login ok\n");
//	}
//	else
//		printf("login fail\n");*/
//
//	createsamplestudents();
//
//	readallstudents();
//	////printf("\n%d\n", allstudentscount);
//	///*promptaddstudent();
//	//writeallstudents();*/
//	///*promptremovestudent();
//	//writeallstudents();*/
//	////promptsearchtotalbyname();
//	////promptsearchtotalbyno();
//
//	////displayallstudents();
//	//calcanddisplaytotalandaverage();
//	//sortanddisplay();
//	//calcanddisplayallsubjects();
//
//	//countbygrades();
//
//	while (choice != 0)
//	{
//		char *menu = "**********************菜单****************************\n"
//			"按1键：读入学生档案               按6键：学科及格概率\n"
//			"按2键：按照姓名查询               按7键：学生档案排序\n"
//			"按3键：按照学号查询               按8键：保存学生档案\n"
//			"按4键：添加学生档案               按9键 : 查看学生档案\n"
//			"按5键：删除学生档案               按10键：求各科平均分\n"
//			"按0键：退出管理系统";
//		printf("请输入选择数字，并回车\n", menu);
//		printf("%s\n", menu);
//		scanf("%d", &choice);
//		switch (choice)
//		{
//		case 0:
//			system("pause");
//			exit(0);
//			break;
//		case 1:
//			readallstudents();
//			break;
//		case 2:
//			promptsearchtotalbyname();
//			break;
//		case 3:
//			promptsearchtotalbyno();
//			break;
//		case 4:
//			promptaddstudent();
//			break;
//		case 5:
//			promptremovestudent();
//			break;
//		case 6:
//			countbygrades();
//			break;
//		case 7:
//			sortanddisplay();
//			break;
//		case 8:
//			writeallstudents();
//			break;
//		case 9:
//			sortanddisplay();
//			break;
//		case 10:
//			calcanddisplaytotalandaverage();
//			calcanddisplayallsubjects();
//
//			break;
//		default:
//			printf("\n\n输入有误，请重选\n");
//			break;
//		}
//		getch();
//	}
//	fseek(stdin, 0, SEEK_END);
//	printf("\n\n按任意键退出\n");
//	system("pause");
//	return 0;
//}
//
