#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
//#define FORMAT3DSD "%d\t%s\t%d\r\n"
#define LINE  "\n------------------------\n"
typedef struct address
{
	int no;
	char name[30];//定义通讯录联系人姓名
	char home[30];//定义联系人的家庭住址
	char tel[30];//定义联系人的电话号码
	char qq[20];//定义联系人的qq号码
	char email[30];//定义联系人的邮箱地址
	address *next;
}address;

address *head;

//字符串转整数
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}



//显示一个成绩
void displayaddress(address add)
{
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\n", add.no, add.name, add.home, add.tel, add.qq, add.email);
	//printf("\r\n");
}

//读取所有成绩到链表
void readalladdresss()
{
	char line[200];
	address *p1, *p2;

	p1 = p2 = (address *)malloc(sizeof(address));
	head = p1;

	p2->next = NULL;
}

//输入某种提示的字符串
void inputstring(char str[], char *description)
{
	printf("请输入%s:", description);
	scanf("%s", str);
	printf("您输入的%s为 %s \n", description, str);
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
//获取一个新的学生信息
int getnewno(address **tail)
{
	int newno = 0;
	address *p = head;
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
	*tail = p;
	return newno;
}

//新增成绩
void addaddress()
{
	int newno = 0, score;//新成绩编号，当前最大+1
	char name[30] = "";
	char home[30] = "";
	char tel[30] = "";
	char qq[20] = "";
	char email[30] = "";
	address *p = head;
	address *n;

	inputstring(name, "姓名");
	inputstring(home, "家庭地址");
	inputstring(tel, "手机号");
	inputstring(qq, "qq号");
	inputstring(email, "邮箱");

	newno = getnewno(&p);

	n = (address *)malloc(sizeof(address));

	n->no = newno;
	strcpy(n->name, name);
	strcpy(n->home, home);
	strcpy(n->tel, tel);
	strcpy(n->qq, qq);
	strcpy(n->email, email);

	p->next = n;
	n->next = NULL;
	printf("\n%s的信息添加成功!\n", name);
}


bool insert(address *pHead, int front, char *name, int score)
{
	int i = 0, newno;
	address *_node = pHead;
	address *pSwap;
	address *pNew;
	address *x;
	newno = getnewno(&x);
	if ((front < 1) && (NULL != _node))
	{
		return false;
	}
	while (i < front - 1)
	{
		_node = _node->next;
		++i;
	}
	pNew = (address*)malloc(sizeof(address));

	pNew->no = newno;
	strcpy(pNew->name, name);
	//pNew->score = score;
	pSwap = _node->next;
	_node->next = pNew;
	pNew->next = pSwap;
	return true;

}



//http://blog.csdn.net/iwm_next/article/details/7450734
void deleteaddress(char * name)  //删除成绩
{
	address *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n成绩为空!\n");
		return;
	}
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (strcmp(p1->name, name) == 0)
	{

		if (p1 == head)
			head = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("已删除姓名为%s的学生的成绩。\r\n", name);
		}
	}
	else
		printf("没找到姓名为%s的学生!\r\n", name);
}



void displayaddress(char * name)  //按姓名输出
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的成绩如下\r\n", name);

			printf("序号    姓名    成绩\n");

			displayaddress(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的学生\r\n", name);
}

void addaddress(char * name)  //追加学生信息
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的成绩如下\r\n", name);

			printf("序号    姓名    成绩\n");

			displayaddress(*p);
			printf("更改学生成绩为：");
			getchar();
			/*	scanf("%d", &p->score);
				printf("修改成功，更改后的学生成绩是：%d。\n", p->score);*/
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的学生\r\n", name);
}

//********************其实可以考虑作为一个通用函数，但我懒得改其他函数了
void searchbyname(char * name, address **f)  //根据名字查找学生
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			*f = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("没找到名为%s的学生\r\n", name);
		*f = NULL;
	}
}

void displayalladdresss()  //输出所有学生信息
{
	address *p = head->next;

	printf("所有学生成绩如下\n");
	printf(LINE);

	printf("姓名%t住址%t手机号%tqq%t邮箱\n");
	while (p != NULL)
	{
		displayaddress(*p);
		p = p->next;
	}
	printf(LINE);
}

void promptinsertbeforeno()  //按编号插入
{
	int no, score;
	char name[50] = "";
	printf("\n请输入要在哪个编号的学生之后插入?\n");
	scanf("%d", &no);

	//inputstring(name);
	score = inputscore();
	if (insert(head, no, name, score))
		printf("\n插入成功！\n");
}



void promptsearchtotalbyname()  //按姓名查找
{
	char name[50] = "";
	//inputstring(name);
	displayaddress(name);
}



void promptdeletebyname()  //按姓名删除
{
	char name[50] = "";
	//inputstring(name);
	deleteaddress(name);
}



int main()
{
	int choice = -1;

	//createsampleaddresss();

	readalladdresss();

	while (choice != 0)
	{
		printf("\n\t 歌唱比赛评分");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 添加联系人信息");
		printf("\n\t 2. 查看所有联系人信息");
		printf("\n\t 3. 删除联系人信息");
		printf("\n\t 4. 根据联系人名字查找");
		printf("\n\t 5. 插入联系人信息");
		printf("\n\n  请选择: ");
		choice = getchar();//输入一个字符
		switch (choice)
		{
		case '0':
			//writealladdresss();
			printf("\n\n 你选择了退出: ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			addaddress();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayalladdresss();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptdeletebyname();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptsearchtotalbyname();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptinsertbeforeno();
			break;

		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}