#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_INPUT "input.txt"
//#define FILE_INPUT "sample.txt"
#define FILE_BEST "best.txt"
#define FILE_SCORES "scores.txt"
#define FILE_ANALYSIS "analysis.txt"
#define FORMAT3DSD "%d\t%s\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
typedef struct student
{
	int no;
	char name[50];
	char choice[QUESTIONS_COUNT];
	int score;
	int total;
}student;

student allstudents[100];
int allstudentscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

char *studentfile = "stu.txt";
student *head;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//从一行文本拆分出成绩 
void getstudentfromline(char *line, student *adg)
{
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			adg->no = toint(part);
			break;
		case 2:
			strcpy(adg->name, part);
			break;
		case 3:
			adg->score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}


//显示一个成绩 
void displaystudent(student stu)
{
	printf(FORMAT3DSD, stu.no, stu.name, stu.score);
	printf("\r\n");
}


void readallstudents()
{
	//char line[200];
	//FILE *fp = fopen(FILE_INPUT, "r");
	//if (fp == NULL)
	//{
	//	printf("\n打开文件%s失败!", FILE_INPUT);
	//	getchar();
	//	exit(1);
	//}
	//allstudentscount = 0;

	//while (fgets(line, 1024, fp) != NULL)
	//{
	//	if (strlen(line) < 5)
	//		continue;
	//	++allstudentscount;
	//	allstudents[allstudentscount - 1] = getstudentfromline(line);
	//}
}



int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sorttotal()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

void writetotal()
{
	int i;
	FILE *fp;
	fp = fopen(FILE_SCORES, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SCORES);
		getchar();
		exit(1);
	}
	sorttotal();
	for (i = 0; i < allstudentscount; i++)
	{
		printf("%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
		fprintf(fp, "%s\t%d\r\n", allstudents[i].name, allstudents[i].total);
	}
	fclose(fp);
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

void writeanalysis()
{
	int i;
	FILE *fp;
	fp = fopen(FILE_ANALYSIS, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ANALYSIS);
		getchar();
		exit(1);
	}
	printf("%s\t%d\r\n", "<60", below60());
	printf("%s\t%d\r\n", "60~80", below60_80());
	printf("%s\t%d\r\n", ">80", above80());
	printf("%s\t%d\r\n", "最高", allstudents[allstudentscount - 1].total);
	printf("%s\t%d\r\n", "最低", allstudents[0].total);
	printf("%s\t%f\r\n", "平均", ave());
	printf("%s\t百分之%d\r\n", "及格率", (int)(100 * (float)(below60_80() + above80()) / (float)allstudentscount));

	fprintf(fp, "%s\t%d\r\n", "<60", below60());
	fprintf(fp, "%s\t%d\r\n", "60~80", below60_80());
	fprintf(fp, "%s\t%d\r\n", ">80", above80());
	fprintf(fp, "%s\t%d\r\n", "最高", allstudents[allstudentscount - 1].total);
	fprintf(fp, "%s\t%d\r\n", "最低", allstudents[0].total);
	fprintf(fp, "%s\t%f\r\n", "平均", ave());
	fprintf(fp, "%s\t百分之%d\r\n", "及格率", (int)(100 * (float)(below60_80() + above80()) / (float)allstudentscount));
	fclose(fp);
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
			return allstudents[i].total;
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
	FILE *fp = fopen(studentfile, "wb");
	printf("创建示例成绩数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMAT3DSD, 11, "Flex", 75);
	fprintf(fp, FORMAT3DSD, 22, "Tony", 80);
	fprintf(fp, FORMAT3DSD, 33, "测试中文姓名", 90);
	fprintf(fp, FORMAT3DSD, 44, "Lukas", 88);
	fprintf(fp, FORMAT3DSD, 55, "Shawn", 100);

	fclose(fp);
	printf("5条示例成绩数据已保存到student.txt。\n");
}





void promptdeletebyname()
{
	char name[50] = "";
	inputname(name);
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

	//readallstudents();
	//viewallstudents();
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

