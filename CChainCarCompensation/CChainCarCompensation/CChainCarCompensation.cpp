#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define FILE_COM "compensation.txt"
#define LINE  "------------------------\n" 
typedef struct compensation
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	compensation *next;
}compensation;

compensation *head;
#define T 0
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

int getdatestringpart(char* str, int from, int to)
{
	int i;
	char  x[5];
	for (i = from; i <= to; i++)
		x[i - from] = str[i];
	x[to - from + 1] = 0;
	return toint(x);
}

int  validatedate(char* str)
{

	int d, m, y;
	int daysinmonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int legit = 0;
	if (strlen(str) != 8)
		return 0;
	y = getdatestringpart(str, 0, 3);
	m = getdatestringpart(str, 4, 5);
	d = getdatestringpart(str, 6, 7);
	//printf("%d\t%d\t%d\n", y, m, d);
	if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
		daysinmonth[1] = 29;
	if (m < 13)
	{
		if (d <= daysinmonth[m - 1])
			legit = 1;
	}
	return legit == 1;
}



void displaycompensation(compensation com)
{
	printf("%s\t%s\t%s\t%s\t%d\t%s\n",
		com.no, com.station, com.chassis, com.auditor, com.money, com.date);
}


void createhead()
{
	char line[200];
	compensation *p1, *p2;
	p1 = p2 = (compensation *)malloc(sizeof(compensation));
	head = p1;
	p2->next = NULL;
}

void checkandreinputdate(char expected[20], char str[20])
{
	while (!validatedate(str))
	{
		printf("请输入合法日期(8位数字，类似20170614，不足补0):");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", str);
	}
	strcpy(expected, str);
}

void inputstring(char str[], char *description)
{
	printf("请输入%s:", description);
	scanf("%s", str);
	printf("您输入的%s为 %s \n", description, str);
}

void gettail(compensation **tail)
{
	int newno = 0;
	compensation *p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	*tail = p;
}

void writeallcompensations()
{
	int i;
	compensation stu;
	compensation *p = head->next;
	FILE *fp = fopen(FILE_COM, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_COM);
		getchar();
		exit(1);
	}


	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期
	while (p != NULL)
	{
		fprintf(fp, "%s %s %s %s %d %s\n",
			p->no, p->station, p->chassis, p->auditor, p->money, p->date);
		p = p->next;
	}

	fclose(fp);
}

void addcompensation(char no[20], char station[20], char chassis[20], char auditor[20], int money, char date[20])
{
	compensation *p = head;
	compensation *n;

	gettail(&p);
	n = (compensation *)malloc(sizeof(compensation));

	strcpy(n->no, no);
	strcpy(n->auditor, auditor);
	strcpy(n->station, station);
	strcpy(n->chassis, chassis);
	n->money = money;
	strcpy(n->date, date);

	p->next = n;
	n->next = NULL;
	writeallcompensations();
}

void findcompensationbyno(char no[20], compensation **found)
{
	compensation *p = head;
	while (p != NULL)
	{
		if (streq(p->no, no))
		{
			*found = p;
			return;
		}
		p = p->next;
	}
}

int isnoexists(char no[20])
{
	compensation *found = NULL;
	findcompensationbyno(no, &found);
	return !(found == NULL);
}

void getcompensationfromline(char *line, compensation *com)
{
	char *part;
	int index = 0;
	//compensation com;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(com->no, part);
			break;
		case 2:
			strcpy(com->station, part);
			break;
		case 3:
			strcpy(com->chassis, part);
			break;
		case 4:
			strcpy(com->auditor, part);
			break;
		case 5:
			com->money = toint(part);
			break;
		case 6:
			strcpy(com->date, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
}

void readallcompensations()
{
	char line[200];
	FILE *fp = fopen(FILE_COM, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_COM);
	}
	else
	{

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;

			//allcompensations[allcompensationscount++] = getcompensationfromline(line);
			compensation *n = (compensation *)malloc(sizeof(compensation));
			getcompensationfromline(line, n);
			addcompensation(n->no, n->station, n->chassis, n->auditor,
				n->money, n->date);
		}
		printf("\n已读入文件!", FILE_COM);
	}
}


void promptaddcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	char expecteddate[20];
	printf("\n请输入编号:");
	scanf("%s", no);
	if (isnoexists(no))
	{
		printf("编号%s已经存在，不能重复添加商品!", no);
		return;
	}
	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期

	printf("\n请输入服务站名称、底盘号、审核人（都是不带空格的字符串），空格隔开\n");
	scanf("%s%s%s", station, chassis, auditor);
	printf("\n请输入索赔金额（整数）、索赔日期（格式20170614），空格隔开\n");
	scanf("%d%s", &money, date);
	checkandreinputdate(expecteddate, date);
	addcompensation(no, station, chassis, auditor, money, date);
	printf("完成录入!\r\n");
}


void editcompensation(compensation *n, char station[20], char chassis[20], char auditor[20], int money, char date[20])
{
	strcpy(n->auditor, auditor);
	strcpy(n->station, station);
	strcpy(n->chassis, chassis);
	n->money = money;
	strcpy(n->date, date);
	writeallcompensations();
}

void prompteditcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	char expecteddate[20];
	compensation *found = NULL;
	printf("\n请输入编号:");
	scanf("%s", no);
	findcompensationbyno(no, &found);
	if (found == NULL)
	{
		printf("编号%s不存在!", no);
		return;
	}
	printf("\n请输入服务站名称、底盘号、审核人（都是不带空格的字符串），空格隔开\n");
	scanf("%s%s%s", station, chassis, auditor);
	printf("\n请输入索赔金额（整数）、索赔日期（格式20170614），空格隔开\n");
	scanf("%d%s", &money, date);
	checkandreinputdate(expecteddate, date);
	editcompensation(found, station, chassis, auditor, money, date);
}

void deletecompensation(char * no)
{
	compensation *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n索赔信息为空!\n");
		return;
	}
	while (strcmp(p1->no, no) != 0 && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (strcmp(p1->no, no) == 0)
	{
		if (p1 == head)
			head = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			writeallcompensations();
			printf("已删除编号为%s的索赔信息的索赔信息。\r\n", no);
		}
	}
	else
		printf("没找到编号为%s的索赔信息!\r\n", no);
}



void displaycompensation(char * auditor)
{
	int found = 0;
	compensation *p = head;

	while (p != NULL)
	{
		if (strcmp(p->auditor, auditor) == 0)
		{
			found = 1;
			printf("%s的索赔信息如下\r\n", auditor);

			//printf("序号    姓名    索赔信息\n");

			displaycompensation(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的索赔信息\r\n", auditor);
}


void searchbyauditor(char * auditor, compensation **f)
{
	int found = 0;
	compensation *p = head;

	while (p != NULL)
	{
		if (strcmp(p->auditor, auditor) == 0)
		{
			*f = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("没找到名为%s的索赔信息\r\n", auditor);
		*f = NULL;
	}
}

void displayallcompensations()
{
	compensation *p = head->next;

	printf("所有索赔信息索赔信息如下\n");
	printf(LINE);
	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期
	printf("编号%t服务站%t底盘%t审核人%t金额%t日期\n");
	while (p != NULL)
	{
		displaycompensation(*p);
		p = p->next;
	}
	printf(LINE);
}




void promptsearchbyno()
{
	char no[20] = "";
	inputstring(no, "要查找记录的编号");
	displaycompensation(no);
}



void promptdeletebyno()
{
	char no[20] = "";
	inputstring(no, "要删除记录的编号");
	deletecompensation(no);
}

void calcstationtotal(char station[20])
{
	compensation *p = head->next;
	int total = 0, found = 0;
	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期
	while (p != NULL)
	{
		if (streq(p->station, station))
		{
			found = 1;
			total += p->money;
		}
		p = p->next;
	}
	if (found == 1)
		printf("服务站%s总索赔金额为%d元。\n", station, total);
	else
		printf("没找到服务站%s的索赔信息。\n", station);
}

void promptcalcstationtotal()
{
	char station[20] = "";
	inputstring(station, "要查询总索赔金额的服务站名称");
	calcstationtotal(station);
}

void getauditbycount(char auditor[20])
{
	compensation *p = head->next;
	int total = 0, found = 0;
	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期
	while (p != NULL)
	{
		if (streq(p->auditor, auditor))
		{
			found = 1;
			total++;
		}
		p = p->next;
	}
	if (found == 1)
		printf("审核人%s审核的索赔次数为%d。\n", auditor, total);
	else
		printf("没找到审核人%s的索赔信息。\n", auditor);
}

void promptgetauditbycount()
{
	char auditor[20] = "";
	inputstring(auditor, "要查询总审核索赔次数的审核人的姓名");
	getauditbycount(auditor);
}

void displaychassiscompensations(char chassis[20])
{
	compensation *p = head->next;

	printf("地盘编号为%的汽车的索赔历史如下\n", chassis);
	printf(LINE);
	//索赔编号、服务站名称、底盘号、审核人、索赔金额、索赔日期
	printf("编号%t服务站%t底盘%t审核人%t金额%t日期\n");
	while (p != NULL)
	{
		if (streq(p->chassis, chassis))
		{
			displaycompensation(*p);
		}
		p = p->next;
	}
	printf(LINE);
}
void promptdisplaychassiscompensations()
{
	char chassis[20] = "";
	inputstring(chassis, "要查询索赔历史的汽车底盘编号");
	displaychassiscompensations(chassis);
}
int main()
{
	int choice = -1;
	compensation *found;

	createhead();
	readallcompensations();
#if T
	//addcompensation("01", "s1", "c1", "a1", 1, "d1");
	//addcompensation("02", "s2", "c2", "a2", 2, "d2");
	//addcompensation("03", "s3", "c3", "a3", 3, "d3");
	displayallcompensations();
	//calcstationtotal("s3");
	getauditbycount("a1");
	//int i = validatedate("2017x106");
	//printf("i=%d\n", i);

	//promptdeletebyno();
	//promptaddcompensation();
	//displayallcompensations();

	//findcompensationbyno("03", &found);
	//editcompensation(found, "s-", "c-", "a-", 99, "d-");
	//prompteditcompensation();
	//displayallcompensations();
	//writeallcompensations();

#else
	while (choice != 0)
	{
		printf("\n\t 索赔录管理");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 查看所有索赔信息");
		printf("\n\t 2. 添加索赔信息");
		printf("\n\t 3. 修改索赔信息");
		printf("\n\t 4. 删除索赔信息");
		printf("\n\t 5. 根据汽车底盘编号查询索赔历史");
		printf("\n\t 6. 查询服务站总索赔金额");
		printf("\n\t 7. 查询审核人总审核索赔次数");
		printf("\n\n  请选择: ");
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出: ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			displayallcompensations();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaddcompensation();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			prompteditcompensation();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptdeletebyno();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptdisplaychassiscompensations();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			promptcalcstationtotal();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			promptgetauditbycount();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
		system("pause");
	}
#endif
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}