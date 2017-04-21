// ConsoleApplication19.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"//comment in vc6
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include "windows.h"
#define MAX_CELL_TEXT_LENTH 20
#define ORDER_FORMAT_STRING "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\r\n"
//#define LYDEV 1


typedef struct order
{
	char no[7];//订单号
	char name[MAX_CELL_TEXT_LENTH];//客户名
	char contact[MAX_CELL_TEXT_LENTH];//联系方式，如果未确认留空
	char totalpersons[MAX_CELL_TEXT_LENTH];//用餐人数
	char eatdate[MAX_CELL_TEXT_LENTH];//用餐时间
	char eatroom[MAX_CELL_TEXT_LENTH];//包间或餐桌号
	char eatmeal[MAX_CELL_TEXT_LENTH];//所点的菜
	char orderdate[15];//订单日期
	char canceldate[15];//取消日期，如果未取消留空
	char cancelreason[MAX_CELL_TEXT_LENTH];//取消原因，如果未取消留空
	char comments[MAX_CELL_TEXT_LENTH];//客户评价
}order;

char currentname[MAX_CELL_TEXT_LENTH] = "";//当前登录的客户名
order orders[50]; //全局存储所有订单
int orderscount;

char *orderfile = "Order.txt";
char *userfile = "user.txt";
order *head;


//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//下面是一些日期函数
//http://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c
time_t createdate(int y, int m, int d)
{
	struct tm date = { 0 };
	date.tm_year = y - 1900;
	date.tm_mon = m;
	date.tm_mday = d;
	return mktime(&date);
}

time_t convertdate(char* str)
{
	int y, m, d;
	struct tm date = { 0 };
	sscanf(str, "%d-%d-%d", &y, &m, &d);
	date.tm_year = y - 1900;
	date.tm_mon = m;
	date.tm_mday = d;
	return mktime(&date);
}

void formatdate(time_t dt, char *str)
{
	struct tm *ptr;
	ptr = localtime(&dt);
	strftime(str, 20, "%Y-%m-%d", ptr);
}

time_t getcurdate()
{
	return time(NULL);
}

//从一行文本拆分出订单 
order getorderfromline(char *line)
{
	order od;
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(od.no, part);
			break;
		case 2:
			strcpy(od.name, part);
			break;
		case 3:
			strcpy(od.contact, part);
			break;
		case 4:
			strcpy(od.totalpersons, part);
			break;
		case 5:
			strcpy(od.eatdate, part);
			break;
		case 6:
			strcpy(od.eatroom, part);
			break;
		case 7:
			strcpy(od.eatmeal, part);
			break;
		case 8:
			strcpy(od.orderdate, part);
			break;
		case 9:
			strcpy(od.canceldate, part);
			break;
		case 10:
			strcpy(od.cancelreason, part);
			break;
		case 11:
			strcpy(od.comments, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return od;
}

void displaytitle(char *title)
{
	printf("\r\n-------------%s-------------\r\n", title);
}

//显示一个订单 
void displayorder(order od)
{
	printf(ORDER_FORMAT_STRING, od.no, od.name, od.contact, od.totalpersons, od.eatdate, od.eatroom, od.eatmeal, od.orderdate, od.canceldate, od.cancelreason, od.comments);
	printf("\r\n");
}

//显示所有航班乘客信息 
void displayallorders()
{
	int i;
	displaytitle("所有订单信息");

	for (i = 0; i < orderscount; i++)
	{
		displayorder(orders[i]);
	}
}

//读取所有订单到链表
void readallorders()
{
	char line[200];
	FILE *fp = fopen(orderfile, "r");
	if (fp == NULL)
	{
		printf("\n打开文件失败!");
		getchar();
		exit(1);
	}
	orderscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;//
		++orderscount;
		orders[orderscount - 1] = getorderfromline(line);
	}
}


//保存所有订单
void writeallorders()
{
	FILE *fp = fopen(orderfile, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件失败!");
		getchar();
		exit(1);
	}

	int i;
	order od;
	for (i = 0; i < orderscount; i++)
	{
		od = orders[i];
		fprintf(fp, ORDER_FORMAT_STRING,
			od.no, od.name, od.contact, od.totalpersons, od.eatdate, od.eatroom, od.eatmeal, od.orderdate, od.canceldate, od.cancelreason, od.comments);
	}
	fclose(fp);
	printf("已保存到文件。");
}


//输入订单信息
void inputstring(char str[], int maxlenth, char* purpose)
{
	int len = -1;
	char input[MAX_CELL_TEXT_LENTH] = "";
	while (len<1 || len > maxlenth)
	{
		printf("请输入%s，%d个字符以内，不能带空格、Tab或回车符:", purpose, maxlenth);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("您的 %s 为 %s \r\n\r\n", purpose, str);
}


//订单开始/结束的日期 
void inputdate(char date[], char *purpose)
{
	int len = -1;
	char input[20] = "";
	//日期格式应该检查为真实日期，且必须是未来日期
	//简单起见只验证长度为10 
	while (len != 10)
	{
		printf("请输入您的%s日期，严格按如下格式2016-06-23:", purpose);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(date, input);
	printf("您选择的%s日期为 %s \r\n", purpose, input);
}

int getorderscountat(char *datestring)
{
	int i;
	int cnt = 0;
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].orderdate, datestring) == 0)
			cnt++;
	}
	return cnt;
}

void formatorderno(time_t dt, int existingcount, char *str)
{
	struct tm *ptr;
	char cntstr[3];
	ptr = localtime(&dt);
	strftime(str, 20, "%m%d", ptr);
	sprintf(cntstr, "%d", existingcount + 1);
	strcat(str, cntstr);
}

//新增订单
void addorder()
{
	order od;
	char nostr[7];
	char todaystring[20];
	time_t today = getcurdate();
	formatdate(today, todaystring);
	formatorderno(getcurdate(), getorderscountat(todaystring) + 1, nostr);

	strcpy(od.no, nostr);
	inputstring(od.name, MAX_CELL_TEXT_LENTH, "客户名");
	strcpy(od.contact, " ");
	inputstring(od.totalpersons, MAX_CELL_TEXT_LENTH, "用餐人数");
	inputstring(od.eatdate, MAX_CELL_TEXT_LENTH, "用餐时间");
	inputstring(od.eatroom, MAX_CELL_TEXT_LENTH, "包间或餐桌号");
	inputstring(od.eatmeal, MAX_CELL_TEXT_LENTH, "所点的菜");
	strcpy(od.orderdate, "2016-08-30");
	strcpy(od.canceldate, " ");
	strcpy(od.cancelreason, " ");
	strcpy(od.comments, " ");

	orders[orderscount++] = od;
	writeallorders();
}

void login()
{
	inputstring(currentname, LOCALE_NAME_MAX_LENGTH, "登录客户名");
	if (strlen(currentname) > 1)
	{
		printf("恭喜你登录成功！");
	}
}


//当前登录客户是否与特定订单客户名一致
int isorderofcurrentname(order* od)
{
	return strcmp(od->name, currentname) == 0;
}

int isordercancelled(order* od)
{
	return strlen(od->canceldate) > 2;
}

//合法返回1，否则0
int checknameorcancelbeforechange(order* od)
{
	if (isordercancelled(od))
	{
		printf("此订单已经取消，不能再更改！");
		return 0;
	}
	else if (!isorderofcurrentname(od))
	{
		printf("当前登录客户名为%s，不能查看别人的订单！", currentname);
		return 0;
	}
	return 1;
}


//确认订单
void confirmorder(order* od)
{
	char contactstr[MAX_CELL_TEXT_LENTH];
	if (checknameorcancelbeforechange(od))
	{
		inputstring(contactstr, MAX_CELL_TEXT_LENTH, "确认订餐的联系方式(至少11位)");
		if (strlen(contactstr) < 11)
			printf("输入的联系方式太短，确认失败！");
		else
		{
			strcpy(od->contact, contactstr);
			writeallorders();
			printf("\r\n确认成功！");
		}
	}
}

//取消订单
void cancelorder(order* od)
{
	char reasonstr[MAX_CELL_TEXT_LENTH];
	char todaystring[20];

	if (checknameorcancelbeforechange(od))
	{
		inputstring(reasonstr, MAX_CELL_TEXT_LENTH, "取消原因");
		if (strlen(reasonstr) < 2)
			printf("输入的取消原因太短，取消失败！");
		else
		{
			time_t today = getcurdate();
			formatdate(today, todaystring);
			strcpy(od->canceldate, todaystring);
			strcpy(od->cancelreason, reasonstr);
			writeallorders();
			printf("\r\n取消成功！");
		}
	}
}

//添加评论
void commentorder(order* od)
{
	char commentstr[MAX_CELL_TEXT_LENTH];

	if (checknameorcancelbeforechange(od))
	{
		inputstring(commentstr, MAX_CELL_TEXT_LENTH, "评价");
		if (strlen(commentstr) < 2)
			printf("输入的评价太短，评价失败！");
		else
		{
			strcpy(od->comments, commentstr);
			writeallorders();
			printf("\r\n评价成功！");
		}
	}
}

//返回订单列表下标，如果没找到返回-1
int inputorderno()
{
	int i;
	int found = -1;
	char ordernostr[7];

	inputstring(ordernostr, 6, "订单号");
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].no, ordernostr) == 0)
		{
			found = i;
			break;
		}
	}
	if (found == -1)
	{
		printf("未找到此订单！");
	}
	return found;
}

//浏览订单
void viewaorder(char* orderno)
{
	int i;
	int found = 0;
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].no, orderno) == 0)
		{
			if (isordercancelled(&orders[i]))
			{
				printf("此订单已经取消，客户不能查询！");
			}
			else
			{
				displaytitle("查找到的订单信息");
				displayorder(orders[i]);
				found = 1;
			}
			break;
		}
	}
	if (found == 0)
	{
		printf("未找到此订单！");
	}
}


void createsampleorders()
{
	FILE *fp = fopen(orderfile, "wb");
	printf("创建示例订单数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, ORDER_FORMAT_STRING, "083001", "Obama", " ", "4人", "2017-09-01日用餐", "雅间1"
		, "满汉全席", "2016-08-30", " ", " ", "好评，下次还来！");
	fprintf(fp, ORDER_FORMAT_STRING, "090102", "习近平", "010-88888888", "1人", "2017-09-05日用餐", "顶级豪华间"
		, "四菜一汤", "2016-08-30", " ", " ", "差评，没包子！");
	fclose(fp);
	printf("示例订单数据已保存到Order.txt。");
}

int main()
{
#ifdef LYDEV
	//createsampleorders();
	readallorders();
	displayallorders();

	//addorder();
	//writeallorders();

	//confirmorder(&orders[0]);
	//cancelorder(&orders[1]);
	viewaorder("090102");//090102 //083001
#else
	int choice = -1;
	int orderindex = -1;

	time_t curdate = getcurdate();

	/*createsampleorders();
	createsampleusers();

	readallusers();*/
	readallorders();
	displayallorders();
	/*strcpy(curuser.name, "user1");
	strcpy(curuser.pwd, "pwd");*/

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t------------------------------");
		printf("\n\t 0. 退出 0");
		printf("\n\t 1. 客户登录 1");
		printf("\n\t 2. （任何人）订餐 2");
		printf("\n\t 3. (登录客户)确认订单 3");
		printf("\n\t 4. (登录客户)删除订单 4");
		printf("\n\t 5. (登录客户)客户评价 5");
		printf("\n\t 6. （酒店统计）查询订单 6");
		printf("\r\n");
		scanf("%1[0123456]d%*c", &choice);
		choice = getche();
		orderindex = -1;
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			login();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			addorder();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				confirmorder(&orders[orderindex]);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				cancelorder(&orders[orderindex]);
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				commentorder(&orders[orderindex]);
			break;
		case
			'6':
			printf("\n\n你选择了 6\n");
			displayallorders();
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
#endif
	system("pause");
	return 0;
}

