#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LINE  "\n------------------------\n" 
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
#define T 1
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
	printf("\n%s的信息添加成功!\n", auditor);
}

void findcompensationbyno(char no[20], compensation **found)
{
	compensation *p = head;
	while (p != NULL)
	{
		if (strcmp(p->no, no) == 0)
		{
			*found = p;
			return;
		}
		p = p->next;
	}
}

int isnoexists(char no[20])
{
	compensation *found;
	findcompensationbyno(no, &found);
	return !found == NULL;
}

void promptaddcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
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

}

void prompteditcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	compensation *found;
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



int main()
{
	int choice = -1;
	compensation *found;

	createhead();
#if T
	addcompensation("01", "s1", "c1", "a1", 1, "d1");
	addcompensation("02", "s2", "c2", "a2", 2, "d2");
	addcompensation("03", "s3", "c3", "a3", 3, "d3");
	displayallcompensations();
	//promptdeletebyno();
	//promptaddcompensation();

	//findcompensationbyno("03", &found);
	//editcompensation(found, "s-", "c-", "a-", 99, "d-");
	prompteditcompensation();
	displayallcompensations();

#else
	while (choice != 0)
	{
		printf("\n\t 索赔录管理");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 添加联系人信息");
		printf("\n\t 2. 查看所有联系人信息");
		printf("\n\t 3. 删除联系人信息");
		printf("\n\t 4. 根据联系人名字查找");
		printf("\n\t 5. 插入联系人信息");
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
			//addcompensation();
			promptaddcompensation();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallcompensations();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptdeletebyauditor();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptsearchbyauditor();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
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