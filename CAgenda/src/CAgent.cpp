// ConsoleApplication19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"//comment in vc6
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include "windows.h"

typedef struct user
{
	char name[20];
	char pwd[20];
	struct user *next;
}user;

typedef struct agenda
{
	int no;
	char affair[50];
	char createddt[15];
	//用开始日期来排序，因此是time_t类型
	//其他日期都只是看的，因此是字符串，免去读写时候转换麻烦
	time_t startdt;
	char enddt[15];
	char name[20];
	struct agenda *next;
}agenda;

char *agendafile = "agenda.txt";
char *userfile = "user.txt";
agenda *head;
user *allusers;
user curuser;

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

//从一行文本拆分出日程 
void getagendafromline(char *line, agenda *adg)
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
			strcpy(adg->affair, part);
			break;
		case 3:
			strcpy(adg->createddt, part);
			break;
		case 4:
			adg->startdt = convertdate(part);
			break;
		case 5:
			strcpy(adg->enddt, part);
			break;
		case 6:
			strcpy(adg->name, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}

//从一行文本拆分出日程 
void getuserfromline(char *line, user *usr)
{
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(usr->name, part);
			break;
		case 2:
			strcpy(usr->pwd, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}

//显示一个日程 
void displayagenda(agenda agd)
{
	char str[15] = "";
	formatdate(agd.startdt, str);
	printf("%d\t%s\t%s\t%s\t%s\t%s\r\n", agd.no, agd.affair, agd.createddt,
		str, agd.enddt, agd.name);
	printf("\r\n");
}

//读取所有日程到链表
void readallagendas()
{
	char line[200];
	agenda *p1, *p2;
	FILE *fp = fopen("Agenda.txt", "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (agenda *)malloc(sizeof(agenda));
	head = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//读进来的行去掉末尾换行符，重要
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getagendafromline(line, p1);
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (agenda*)malloc(sizeof(agenda));
	}
	p2->next = NULL;
}

//读取所有用户到链表
void readallusers()
{
	char line[200];
	user *p1, *p2;
	FILE *fp = fopen("user.txt", "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (user *)malloc(sizeof(user));
	allusers = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//读进来的行去掉末尾换行符，重要
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getuserfromline(line, p1);
		if (allusers == NULL)
			allusers = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (user*)malloc(sizeof(user));
	}
	p2->next = NULL;
}

//保存所有日程
void writeallagendas()
{
	char str[15] = "";
	agenda *p;
	FILE *fp = fopen(agendafile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = head;

	while (p != NULL)
	{
		agenda agd = *p;
		formatdate(agd.startdt, str);
		fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\r\n", agd.no, agd.affair, agd.createddt,
			str, agd.enddt, agd.name);
		p = p->next;
	}
	fclose(fp);
	printf("已保存到文件。");
}

//保存所有用户
void writeallusers()
{
	char str[15] = "";
	user *p;
	FILE *fp = fopen(userfile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = allusers;

	while (p != NULL)
	{
		user usr = *p;
		fprintf(fp, "%s\t%s\r\n", usr.name, usr.pwd);
		p = p->next;
	}
	fclose(fp);
	printf("已保存到文件。");
}

//输入日程信息
void inputaffair(char str[])
{
	int len = -1;
	while (len < 5 || len > 49)
	{
		printf("请输入日程内容(5-45个字符)，最好用英文，简短，不能带Tab或回车符:");
		scanf("%s", str);
		len = strlen(str);
	}
	printf("您的日程内容为 %s \r\n", str);
}


//日程开始/结束的日期 
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

//新增日程
void addagenda()
{
	int newno = 0;//新日程编号，当前最大+1
	char cur[15] = "";
	agenda *p = head;
	agenda *n;
	char info[50] = "";
	char sdt[15] = "";
	char edt[15] = "";
	inputaffair(info);
	inputdate(sdt, "开始");
	inputdate(edt, "结束");

	/*only test
	char info[] = "test event";
	char sdt[] = "2016-06-27";
	char edt[] = "2016-06-28";
	*/
	if (head->no > newno)
		newno = head->no;
	while (p->next != NULL)
	{
		if (p->no > newno)
			newno = p->no;
		p = p->next;
	}
	if (p->no > newno)
		newno = p->no;
	newno++;
	n = (agenda *)malloc(sizeof(agenda));

	n->no = newno;
	strcpy(n->affair, info);
	formatdate(getcurdate(), cur);
	strcpy(n->createddt, cur);
	n->startdt = convertdate(sdt);
	strcpy(n->enddt, edt);
	strcpy(n->name, curuser.name);

	p->next = n;
	n->next = NULL;

	writeallagendas();
}

//新增用户
void adduser()
{
	int exists = 0;
	user *p = allusers;
	user *n;
	//*
	char name[20] = "";
	char pwd[20] = "";
	printf("请输入注册的用户名:");
	scanf("%s", name);
	printf("请输入注册的密码:");
	scanf("%s", pwd);
	//TO DO: 验证密码强度和确认密码等
	//*/

	/*only test
	char name[] = "user2";
	char pwd[] = "pwd2";
	*/

	if (strcmp(allusers->name, name) == 0)
		exists = 1;
	while (p->next != NULL)
	{
		if (strcmp(p->name, name) == 0)
			exists = 1;
		p = p->next;
	}
	if (strcmp(p->name, name) == 0)
		exists = 1;
	if (exists)
	{
		printf("此用户已经存在，不能重复注册\r\n");
		return;
	}
	n = (user *)malloc(sizeof(user));

	strcpy(n->name, name);
	strcpy(n->pwd, pwd);

	p->next = n;
	n->next = NULL;

	writeallusers();

	strcpy(curuser.name, name);
	strcpy(curuser.pwd, pwd);
	printf("恭喜您注册成功！用户名 %s 密码 %s \r\n", name, pwd);
}

//删除日程
//http://blog.csdn.net/iwm_next/article/details/7450734
//To do: 删除第一条貌似有问题，自己改下
void deleteagenda(char * curname, int delno)//参数方便调试用
{
	agenda *p1 = head, *p2;
	if (delno <= 0)
	{
		printf("请输入要删除的日程编号\r\n");
		scanf("%d", &delno);
	}

	if (head == NULL)
	{
		printf("\n日程为空!\n");
		return;
	}
	while (delno != p1->no && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (delno == p1->no)
	{
		if (strcmp(p1->name, curname) == 0)
		{
			if (p1 == head)
				head = p1->next;
			else
			{
				p2->next = p1->next;
				free(p1);
				writeallagendas();
				printf("已删除编号为%d的日程。\r\n", delno);
			}
		}
		else
			printf("编号为%d的日程属于其他人，不能删除！\r\n", delno);
	}
	else
		printf("没找到编号为%d的日程!\r\n", delno);
}

//浏览日程
void viewagenda(char * curname, time_t curdate, int old)//curname, curdate方便调试用
{
	agenda *p = head;

	printf("您的%s日程如下\r\n", old ? "历史" : "未来");
	while (p != NULL)
	{
		if (strcmp(p->name, curname) == 0 &&
			(old && p->startdt < curdate ||
			!old && p->startdt >= curdate))
			displayagenda(*p);
		p = p->next;
	}
}

void login()
{
	int success = 0;
	user *p = allusers;
	char name[20] = "";
	char pwd[20] = "";
	printf("请输入您已注册的用户名:");
	scanf("%s", name);
	printf("请输入对应的密码:");
	scanf("%s", pwd);

	if (strcmp(allusers->name, name) == 0
		&& strcmp(allusers->pwd, pwd) == 0)
		success = 1;
	while (p->next != NULL)
	{
		if (strcmp(p->name, name) == 0
			&& strcmp(p->pwd, pwd) == 0)
			success = 1;
		p = p->next;
	}
	if (strcmp(p->name, name) == 0
		&& strcmp(p->pwd, pwd) == 0)
		success = 1;
	if (success)
	{
		printf("恭喜您登录成功！用户名 %s \r\n", name);
		strcpy(curuser.name, name);
		strcpy(curuser.pwd, pwd);
		return;
	}
	else
		printf("登录失败，请检查用户名和密码！\r\n");
}

void createsampleagendas()
{
	FILE *fp = fopen(agendafile, "wb");
	char *fmt = "%d\t%s\t%s\t%s\t%s\t%s\r\n";
	printf("创建示例日程数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, fmt, 1, "Meet Bbama", "2015-01-01", "2015-03-03", "2015-01-04", "Jim");
	fprintf(fp, fmt, 2, "Meet XiJinping", "2015-06-26", "2015-08-28", "2015-06-29", "Kathy");
	fprintf(fp, fmt, 3, "Quit EU", "2015-06-26", "2016-08-28", "2016-06-30", "Jim");
	fprintf(fp, fmt, 4, "test event", "2016-06-27", "2016-08-27", "2016-06-28", "Kathy");
	fclose(fp);
	printf("示例日程数据已保存到Agenda.txt。");
}

void createsampleusers()
{
	FILE *fp = fopen(userfile, "wb");
	char *fmt = "%s\t%s\r\n";
	printf("创建示例用户...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, fmt, "Jim", "123456");
	fprintf(fp, fmt, "Kathy", "QWERT");
	fprintf(fp, fmt, "user2", "pwd2");
	fprintf(fp, fmt, "leiyang", "password");
	fclose(fp);
	printf("示例用户已保存到user.txt。");
}

int main()
{
	int choice = -1;

	time_t curdate = getcurdate();
	//由于后来新增了不能预设输入文件要求，
	//新增创建文件并重新读入，如果从头知道这个需求，就不会重新读入
	//但对于小文件来说性能忽略不计
	createsampleagendas();
	createsampleusers();

	readallusers();
	readallagendas();

	strcpy(curuser.name, "user1");
	strcpy(curuser.pwd, "pwd");

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t------------------------------");
		printf("\n\n\t 0. 退出 0");
		printf("\n\n\t 1. 注册新用户 1");
		printf("\n\t 2. 登录 2");
		printf("\n\t 3. 新建日程 3");
		printf("\n\t 4. 查看历史日程 4");
		printf("\n\t 5. 查看未来日程 5");
		printf("\n\t 6. 删除日程 6");
		printf("\n\n 请选择: ");
		scanf("%1[0123456]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			adduser();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			login();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			addagenda();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			viewagenda(curuser.name, curdate, 1);
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			viewagenda(curuser.name, curdate, 0);
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			deleteagenda(curuser.name, 0);
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}

	system("pause");
	return 0;
}

