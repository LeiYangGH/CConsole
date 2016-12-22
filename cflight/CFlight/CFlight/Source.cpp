#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 20

typedef struct flight
{
	char no[MAX_STRLEN];
	char from[MAX_STRLEN];
	char to[MAX_STRLEN];
	int seats;
	int left;
}flight;

flight allflights[100];
int allflightscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void addstudent(char no[], char from[], char to[], int seats)
{
	flight stu;
	strcpy(stu.no, no);
	strcpy(stu.from, from);
	strcpy(stu.to, to);
	stu.seats = seats;
	allflights[allflightscount++] = stu;
}

void promptaddstudent()
{
	char no[MAX_STRLEN] = "";
	char from[MAX_STRLEN] = "";
	char to[MAX_STRLEN] = "";
	int seats = 0;
	printf("\n请输入航班号\n");
	scanf("%s", &no);
	printf("\n请输入始发地\n");
	scanf("%s", from);
	printf("\n请输入目的地\n");
	scanf("%s", to);
	printf("\n请输入座位数\n");
	scanf("%d", &seats);
	addstudent(no, from, to, seats);
	printf("完成第%d个航班录入!\r\n", allflightscount);
}

void displayflight(flight stu)
{
	printf("\r\n");
	printf("%s\t%s\t%s\t%d\n", stu.no, stu.from, stu.to, stu.left);
}

void searchflight(char *from, char *to)
{
	int i;
	for (i = 0; i < allflightscount; i++)
		if (streq(allflights[i].from, from)
			&& streq(allflights[i].to, to))
			displayflight(allflights[i]);
	printf("没找到对应航班的信息。\r\n");
}

void promptsearflight()
{
	char no[MAX_STRLEN] = "";
	char from[MAX_STRLEN] = "";
	char to[MAX_STRLEN] = "";
	printf("\n请输入查询始发地\n");
	scanf("%s", from);
	printf("\n请输入查询目的地\n");
	scanf("%s", to);
	searchflight(from, to);
}

void bookflight(char *no)
{
	int i, found = 0;
	for (i = 0; i < allflightscount; i++)
		if (streq(allflights[i].no, no))
		{
			found = 1;
			if (allflights[i].left > 0)
			{
				allflights[i].left--;
				printf("订票成功！\r\n");
			}
			else
			{
				printf("没有余票了！\r\n");
			}
			break;

		}
	if (found == 0)
		printf("没找到对应航班的信息。\r\n");
}

void promptbookflight()
{
	char no[MAX_STRLEN] = "";
	printf("\n请输入航班号\n");
	scanf("%s", &no);
	bookflight(no);
}


int main()
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        考试系统          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. 输入航班信息\n");
		printf("\n\t 2. 查询航班\n");
		printf("\n\t 3. 订票\n");
		printf("\n\t 4. 统计航班\n");
		printf("\n\t 0. 退出");
		printf("\n\n 请选择: ");
		scanf("%1[01234]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			promptaddstudent();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptsearflight();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptbookflight();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			printf("\n\n正在做！！！2\n");
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	system("pause");
	return 0;
}
