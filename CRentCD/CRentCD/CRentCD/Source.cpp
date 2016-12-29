#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//conio.h仅仅是主菜单里用，主菜单输入数字选择时，不回显，方便一点，如果你不要这个头文件，主菜单改成scanf也可以
#include <conio.h> 
#define DEV 0 //调试时候1， 发布时候0
#define MAX_COUNT 20 //暂定最多20条数据，随便改
#define MAX_STRLEN 20 //字符串最长长度
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
	int isreturned;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
	int vip;
}customer;
//所有数据都存储在下面这3个结构体数组里面
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
//display all显示全部，调用displayvcd显示单行，下同
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
		if (allrentcds[i].isreturned == 0)
			displayrentcd(allrentcds[i]);
	}
}
//添加单个
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
	cd.isrent = 0;
	allvcds[allvcdscount++] = cd;
}

//要求用户输入，输入后调用addvcd，下同，分开两个函数是为了测试方便
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
		//这里vip可以有个默认值，当用户归还的时候自动计算vip，比如+1等，实现真正的vip动态计算
		printf("\n\n请输入客户vip，自然数(暂时只记录个数字，还没实现其功能):");
		scanf("%d", &vip);
		addcustomer(no, name, vip);
		printf("\n客户%s信息添加成功!\n", name);
	}
}

//通过名称查找cd，传进来的是vcd的指针，下同
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

//假设一定能找到
void findcunamebycdname(char *cdname, char *cuname)
{
	int i;
	for (i = 0; i < allrentcdscount; i++)
	{
		if (streq(allrentcds[i].cdname, cdname))
		{
			strcpy(cuname, allrentcds[i].cuname);
			break;
		}
	}
}

//出租
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
			rcd.isreturned = 0;
			allrentcds[allrentcdscount++] = rcd;
			cd->isrent = 1;
			printf("租借成功！\n");
		}
	}
}

//输入并出租
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

//归还
void addreturn(char *cdname)
{
	int i;
	vcd *cd;
	customer *cu;
	rentcd rcd;
	//也可以做根据cd编号来归还，模拟现实扫条码，但从作业测试容易程度还是通过cd name好些
	findvcdbyname(cdname, &cd);
	if (cd != NULL)
	{
		if (cd->isrent)
		{
			for (i = 0; i < allrentcdscount; i++)
			{
				rcd = allrentcds[i];
				if (streq(rcd.cdname, cdname))
				{
					findcustomerbyname(allrentcds[i].cuname, &cu);
					strcpy(allrentcds[i].cuname, "");
					allrentcds[i].cuno = 0;
					printf("租金为：%d，您为VIP贵宾，根据政策您可以减免费用： %d元 \n", allrentcds[i].days, cu->vip);//简单租金计算
					allrentcds[i].days = 0;
					//理论上只需要设置下面这个值也可以
					allrentcds[i].isreturned = 1;
					break;
				}
			}
			cd->isrent = 0;
			printf("归还成功！\n");
		}
		else
		{
			printf("CD %s 还没出租，不能归还！\n", cdname);//不应该发生，不可能走到这一步
		}
	}
}

//输入并归还
void inputreturn()
{
	char  cdname[MAX_STRLEN] = "";
	printf("请输入归还的CD名称（根据编号归还的功能你可以自己仿照加）:");
	scanf("%s", &cdname);
	addreturn(cdname);
}

//输出某客户的出租
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

//输入客户并显示其出租
void inputanddisplayonecustomerrentcds()
{
	char name[MAX_STRLEN] = "";
	printf("\n请输入要查询租借情况的客户姓名:");
	scanf("%s", name);
	displayonecustomerrentcds(name);
}

int main()
{
	int choice = -1;

	//下面这些是测试时方便测试的，可以删除
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	//addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");

#if DEV
	//下面这些是测试时方便测试的，可以删除
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	//addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");
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
		printf("\n\t 8. 归还CD");
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
		case '8':
			printf("\n\n你选择了 8\n");
			inputreturn();
			break;
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