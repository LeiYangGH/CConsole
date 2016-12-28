#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define COU_CNT 7
#define MAX_STRLEN 20
#define FORMAT_CD "%d\t%s\r\n"
#define MEMBERS_CD cd.no, cd.name
//#define FORMAT_STU "%s\t%s\t%s\t%d\r\n"
//#define MEMBERS_STU stu.no, stu.name, stu.sex, stu.totalpoints, stu.supplement
#define LINE  "\n------------------------\n"


typedef struct vcd
{
	int no;
	char name[20];
	struct vcd *next;
}cd;
typedef struct rentcd
{
	int no;
	char name[20];
	int date;
	struct rentcd *next;
}rentcd;
typedef struct customer
{
	char name[20];
	int vip;
	struct customer *next;
}customer;

vcd *cdhead;

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

void displaycd(vcd cd)
{
	printf(FORMAT_CD, MEMBERS_CD);
	printf("\n");
}
void displayallvcds()
{
	vcd *p = cdhead->next;
	if (cdhead == NULL)
	{
		printf("还没有输入任何CD信息！\r\n");
	}
	printf("所有CD情况如下\r\n");
	printf(LINE);
	printf("编号\t名称\r\n");
	while (p != NULL)
	{
		displaycd(*p);
		p = p->next;
	}
}
void findcdbyno(int  no, vcd **cd)  //根据名字查找CD
{
	int found = 0;
	vcd *p = cdhead;

	while (p != NULL)
	{
		if (p->no == no)
		{
			*cd = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("没找到编号名为%d的课程\r\n", no);
		*cd = NULL;
	}
}

void addvcds(vcd **p1, vcd **p2, int no, char *name)
{
	(*p1)->no = no;
	strcpy((*p1)->name, name);
	(*p2)->next = (*p1);
	(*p2) = (*p1);
	(*p1) = (vcd*)malloc(sizeof(vcd));
}

void inputvcds()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	vcd *p1, *p2;
	cdhead = (vcd *)malloc(sizeof(vcd));
	p1 = p2 = (vcd *)malloc(sizeof(vcd));
	cdhead->next = p1;
#if DEV
#else
	while (1)
#endif
	{

#if DEV
		addvcds(&p1, &p2, 1, "cd1");
		addvcds(&p1, &p2, 2, "cd2");
		addvcds(&p1, &p2, 3, "cd3");
#else
		printf("\n\n请输入CD编号，不重复整数(0结束):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入CD名:");
		scanf("%s", name);
		addvcds(&p1, &p2, no, name);
#endif
		printf("\nCD %s信息添加成功!\n", name);
	}
	p2->next = NULL;
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
//void findvcdbyname(char *name, vcd **stu)
//{
//	int found = 0;
//	vcd *p = stuhead;
//
//	while (p != NULL)
//	{
//		if (streq(p->name, name))
//		{
//			*stu = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("没找到姓名为%s的CD\r\n", name);
//		*stu = NULL;
//	}
//}

//int selectonecd(vcd *stu, int couno)
//{
//	cd *cd;
//
//	if (stu->selcouscnt >= 5)
//	{
//		printf("选课不能超过5门\r\n");
//		return 0;
//	}
//	findcdbyno(couno, &cd);
//	if (cd != NULL)
//	{
//		if (cd->stucnt < cd->no)
//		{
//			stu->selcds[stu->selcouscnt] = couno;
//			stu->totalpoints += cd->points;
//			stu->selcouscnt++;
//			cd->stucnt++;
//			printf("选课成功！\r\n");
//			return 1;
//		}
//		else
//		{
//			printf("课程%s已经选满！\r\n", cd->name);
//			return 0;
//		}
//	}
//}
//
//void selectcds(vcd *stu)
//{
//	int no;
//	if (stu == NULL)
//	{
//		printf("请先输入姓名再选课！\n");
//		return;
//	}
//	do
//	{
//		printf("请输入要选择的课程号（1～7），0结束选择：");
//		scanf("%d", &no);
//		fseek(stdin, 0, SEEK_END);
//		if (no == 0)
//		{
//			if (stu->selcouscnt >= 3)
//			{
//				printf("你已退出了课程选择。\n");
//				break;
//			}
//			else
//			{
//				printf("必须选满至少3门课程！\n");
//			}
//		}
//		selectonecd(stu, no);
//	} while (stu->selcouscnt <= 5);
//	printf("选课结束。\n");
//}


int main()
{
	int choice = -1;
	inputvcds();
	displayallvcds();
#if DEV
	//vcd *stu;
	//strcpy(curstuname, "ly");
	//displayallcds();

	//findvcdbyname(curstuname, &curstu);
	//selectonecd(curstu, 1);
	//selectonecd(curstu, 2);
	//selectonecd(curstu, 3);
	//selectonecd(curstu, 4);
	//selectonecd(curstu, 5);
	//selectonecd(curstu, 6);
	//findvcdbyname("sm", &stu);
	//selectonecd(stu, 1);
	//selectonecd(stu, 2);
	//selectonecd(stu, 5);
	//displayallstuselcds();
	//sortanddisplayallvcds();
#else
	while (choice != 0)
	{
		printf("\n\t CD选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入CD信息");
		//printf("\n\t 2. 查看所有课程");
		printf("\n\t 3. 查看所有CD");
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
			//case '2':
			//	printf("\n\n你选择了 2\n");
			//	displayallcds();
			//	break;
		case '3':
			printf("\n\n你选择了 3\n");
			displayallvcds();
			break;
			//case '4':
			//	printf("\n\n你选择了 4\n");
			//	printf("请输入您的姓名，回车结束:");
			//	scanf("%s", curstuname);
			//	findvcdbyname(curstuname, &curstu);
			//	printf("当前CD姓名：%s\n", curstuname);
			//	break;
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