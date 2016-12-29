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
#define FORMAT_CU "%d\t%s\t%d\n"
#define MEMBERS_CU cu.no, cu.name, cu.vip
#define LINE  "\n------------------------\n"


typedef struct vcd
{
	int no;
	char name[MAX_STRLEN];
}cd;
typedef struct rentcd
{
	int no;
	char name[MAX_STRLEN];
	int date;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
	int vip;
}customer;

vcd allvcds[MAX_COUNT];
int allvcdscount = 0;

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
	printf("所有CD情况如下\r\n");
	printf("编号\t名称\r\n");
	printf(LINE);
	for (i = 0; i < allvcdscount; i++)
	{
		displayvcd(allvcds[i]);
	}
	printf(LINE);
}
void findcdbyno(int  no, vcd **cd)  //根据名字查找CD
{
	//int i;
	//int found = 0;
	//for (i = 0; i < allvcdscount; i++)
	//{
	//	if (allvcds[i].no == no)
	//	{
	//		*cd = &allvcds[i];
	//		found = 1;
	//		break;
	//	}
	//}
	//if (!found)
	//{
	//	printf("没找到编号名为%d的CD\r\n", no);
	//	*cd = NULL;
	//}
}
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
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

//int deletevcdbyno(vcd *L, char * no)
//{
//	vcd *p1 = L, *p2;
//	if (L == NULL)
//	{
//		printf("\nCD链表为空!\n");
//		return 0;
//	}
//	while (!streq(p1->no, no) && p1->next != NULL)
//	{
//		p2 = p1;
//		p1 = p1->next;
//	}
//	if (streq(p1->no, no))
//	{
//		if (p1 == L)
//			L = p1->next;
//		else
//		{
//			p2->next = p1->next;
//			free(p1);
//			printf("已删除学号为%s的CD的成绩。\r\n", no);
//			return 1;
//		}
//	}
//	else
//	{
//		printf("没找到学号为%s的CD!\r\n", no);
//		return 0;
//	}
//}
//
//void findvcdbyname(char *name, vcd **cu)
//{
//	int found = 0;
//	vcd *p = stuhead;
//
//	while (p != NULL)
//	{
//		if (streq(p->name, name))
//		{
//			*cu = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("没找到姓名为%s的CD\r\n", name);
//		*cu = NULL;
//	}
//}

//int selectonecd(vcd *cu, int couno)
//{
//	cd *cd;
//
//	if (cu->selcouscnt >= 5)
//	{
//		printf("选课不能超过5门\r\n");
//		return 0;
//	}
//	findcdbyno(couno, &cd);
//	if (cd != NULL)
//	{
//		if (cd->stucnt < cd->no)
//		{
//			cu->selcds[cu->selcouscnt] = couno;
//			cu->totalpoints += cd->points;
//			cu->selcouscnt++;
//			cd->stucnt++;
//			printf("选课成功！\r\n");
//			return 1;
//		}
//		else
//		{
//			printf("CD%s已经选满！\r\n", cd->name);
//			return 0;
//		}
//	}
//}
//
//void selectcds(vcd *cu)
//{
//	int no;
//	if (cu == NULL)
//	{
//		printf("请先输入姓名再选课！\n");
//		return;
//	}
//	do
//	{
//		printf("请输入要选择的CD号（1～7），0结束选择：");
//		scanf("%d", &no);
//		fseek(stdin, 0, SEEK_END);
//		if (no == 0)
//		{
//			if (cu->selcouscnt >= 3)
//			{
//				printf("你已退出了CD选择。\n");
//				break;
//			}
//			else
//			{
//				printf("必须选满至少3门CD！\n");
//			}
//		}
//		selectonecd(cu, no);
//	} while (cu->selcouscnt <= 5);
//	printf("选课结束。\n");
//}

//////add cus start/////
customer allcustomers[MAX_COUNT];
int allcustomerscount = 0;

void displaycustomer(customer cu)
{
	printf(FORMAT_CU, MEMBERS_CU);
	printf("\n");
}
void displayallcustomers()
{
	int i;
	printf("所有客户如下\r\n");
	printf("学号\t姓名\r\n");
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

//////add cus end/////
int main()
{
	int choice = -1;
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");
	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);
	//displayallvcds();
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
		//printf("\n\t 4. CD登录（登录后才能选课）");
		//printf("\n\t 5. 当前CD选课");
		//printf("\n\t 6. 查看所有CD选课");
		//printf("\n\t 7. CD按学分总积分排列输出");
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
			//case '5':
			//	printf("\n\n你选择了 5\n");
			//	selectcds(curstu);
			//	break;
			//case '6':
			//	printf("\n\n你选择了 6\n");
			//	displayallstuselcds();
			//	break;
			//case '7':
			//	printf("\n\n你选择了 7\n");
			//	sortanddisplayallvcds();
			//	break;
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