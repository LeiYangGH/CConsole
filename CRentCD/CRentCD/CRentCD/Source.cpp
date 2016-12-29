#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define MAX_COUNT 20
#define MAX_STRLEN 20
#define FORMAT_CD "%d\t%s\n"
#define MEMBERS_CD cd.no, cd.name
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\t%d\n"
#define MEMBERS_CU cu.no, cu.name, cu.vip
#define LINE  "\n------------------------\n"


typedef struct vcd
{
	int no;
	char name[MAX_STRLEN];
	int isrent;
}vcd;
typedef struct rentcd
{
	int cdno;
	char cdname[MAX_STRLEN];
	int cuno;
	char cuname[MAX_STRLEN];
	int days;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
	int vip;
}customer;

vcd allvcds[MAX_COUNT];
int allvcdscount = 0;

rentcd allrentcds[MAX_COUNT];
int allrentcdscount = 0;

customer allcustomers[MAX_COUNT];
int allcustomerscount = 0;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displayvcd(vcd cd)
{
	printf(FORMAT_CD, MEMBERS_CD);
}
void displayallvcds()
{
	int i;
	printf("所有CD情况如下\n");
	printf("编号\t名称\n");
	printf(LINE);
	for (i = 0; i < allvcdscount; i++)
	{
		displayvcd(allvcds[i]);
	}
	printf(LINE);
}
//////////0
void displayrentcd(rentcd rcd)
{
	printf(FORMAT_RCD, MEMBERS_RCD);
}



void displayallrentcds()
{
	int i;
	printf("所有CD租借情况如下\n");
	printf("CD\t客户\t天数\n");
	printf(LINE);
	for (i = 0; i < allrentcdscount; i++)
	{
		displayrentcd(allrentcds[i]);
	}
}
///////////1
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
	cd.isrent = 0;
	allvcds[allvcdscount++] = cd;
}

void inputvcds()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入CD编号(整数，0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入CD名称:");
		scanf("%s", name);
		addvcd(no, name);
		printf("\nCD%s信息添加成功!\n", name);
	}
}


//////add cus start/////


void displaycustomer(customer cu)
{
	printf(FORMAT_CU, MEMBERS_CU);
	printf("\n");
}
void displayallcustomers()
{
	int i;
	printf("所有客户如下\n");
	printf("学号\t姓名\n");
	printf(LINE);
	for (i = 0; i < allcustomerscount; i++)
	{
		displaycustomer(allcustomers[i]);
	}
	printf(LINE);
}

void addcustomer(int no, char *name, int vip)
{
	int i;
	customer cu;
	cu.no = no;
	strcpy(cu.name, name);
	cu.vip = vip;//默认vip
	allcustomers[allcustomerscount++] = cu;
}

void inputcustomers()
{
	int i, no, vip;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入客户编号，不重复自然数(0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入客户姓名:");
		scanf("%s", name);
		printf("\n\n请输入客户vip，自然数(暂时只记录个数字，还没实现其功能):");
		scanf("%d", &vip);
		addcustomer(no, name, vip);
		printf("\n客户%s信息添加成功!\n", name);
	}
}

void findvcdbyname(char *cdname, vcd **cd)
{
	int i;
	int found = 0;
	for (i = 0; i < allvcdscount; i++)
	{
		if (streq(allvcds[i].name, cdname))
		{
			*cd = &allvcds[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到名称为%s的CD\n", cdname);
		*cd = NULL;
	}
}

void findcustomerbyname(char *cuname, customer **cu)
{
	int i;
	int found = 0;
	for (i = 0; i < allcustomerscount; i++)
	{
		if (streq(allcustomers[i].name, cuname))
		{
			*cu = &allcustomers[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("没找到姓名为%s的客户\n", cuname);
		*cu = NULL;
	}
}

void addrent(char *cdname, char *cuname, int days)
{
	vcd *cd;
	customer *cu;
	rentcd rcd;
	findvcdbyname(cdname, &cd);
	findcustomerbyname(cuname, &cu);
	if (cd != NULL && cu != NULL)
	{
		if (cd->isrent)
		{
			printf("CD %s 已经出租，不能再出租！\n", cdname);
		}
		else
		{
			rcd.cdno = cd->no;
			strcpy(rcd.cdname, cdname);
			rcd.cuno = cu->no;
			strcpy(rcd.cuname, cuname);
			rcd.days = days;
			allrentcds[allrentcdscount++] = rcd;
			cd->isrent = 1;
			printf("租借成功！\n");
		}
	}
}

void inputrent()
{
	char  cdname[MAX_STRLEN] = "";
	char  cuname[MAX_STRLEN] = "";
	int days;
	/*printf("请输入租借要出租的CD名称:");
	scanf("%s", &cdname);
	printf("请输入要租借给客户的姓名:");
	scanf("%s", &cuname);
	printf("请输入租借天数(暂时是输入天数，后面可以改成自动按日期计算):");
	scanf("%d", &days);*/
	//两种输入哪个更好？
	printf("请输入租借要出租的CD名称、客户名称、出租天数(暂时是输入天数，后面可以改成自动按日期计算)，中间空格分隔，回车结束:");
	scanf("%s%s%d", &cdname, &cuname, &days);
	addrent(cdname, cuname, days);
}

void displayonecustomerrentcds(char *name)
{
	int i, pay = 0;
	rentcd rcd;
	customer *cu;
	findcustomerbyname(name, &cu);
	if (cu != NULL)
	{
		printf("客户 %s 所有CD租借情况如下\n", name);
		printf("CD\t客户\t天数\n");
		printf(LINE);
		for (i = 0; i < allrentcdscount; i++)
		{
			rcd = allrentcds[i];
			if (streq(rcd.cuname, name))
			{
				displayrentcd(rcd);
				pay += rcd.days;
			}
		}
		printf("总租金：%d\n", pay);
	}
}

void inputanddisplayonecustomerrentcds()
{
	char name[MAX_STRLEN] = "";
	printf("\n请输入要查询租借情况的客户姓名:");
	scanf("%s", name);
	displayonecustomerrentcds(name);
}

//////add cus end/////
int main()
{
	int choice = -1;
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
#if DEV

	//strcpy(curstuname, "ly");
	displayallvcds();


	displayallcustomers();
	//findvcdbyname(curstuname, &curstu);
	//selectonecd(curstu, 1);
	//selectonecd(curstu, 2);
	//selectonecd(curstu, 3);
	//selectonecd(curstu, 4);
	//selectonecd(curstu, 5);
	//selectonecd(curstu, 6);
	//findvcdbyname("sm", &cu);
	//selectonecd(cu, 1);
	//selectonecd(cu, 2);
	//selectonecd(cu, 5);
	//displayallstuselcds();
	//sortanddisplayallvcds();
#else
	while (choice != 0)
	{
		printf("\n\t CD选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入CD信息");
		printf("\n\t 2. 查看所有CD");
		printf("\n\t 3. 录入客户信息");
		printf("\n\t 4. 查看所有客户");
		printf("\n\t 5. 出租CD");
		printf("\n\t 6. 查看所有CD出租情况");
		printf("\n\t 7. 查看某位客户CD出租情况");
		//printf("\n\t 8. 输入所有CD成绩");
		//printf("\n\t 9. 一门和三门功课不及格的CD");
		printf("\n\n  请选择: ");
		choice = getche();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			inputvcds();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallvcds();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			inputcustomers();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallcustomers();
			/*printf("请输入您的姓名，回车结束:");
			scanf("%s", curstuname);
			findvcdbyname(curstuname, &curstu);
			printf("当前CD姓名：%s\n", curstuname);*/
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			inputrent();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			displayallrentcds();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			inputanddisplayonecustomerrentcds();
			break;
			//case '8':
			//	printf("\n\n你选择了 8\n");
			//	inputallstuscores();
			//	break;
			//case '9':
			//	printf("\n\n你选择了 9\n");
			//	listallnamesbelow60forcou(1);
			//	listallnamesbelow60forcou(3);
			//	break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}