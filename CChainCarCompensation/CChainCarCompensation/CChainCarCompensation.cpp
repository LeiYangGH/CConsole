#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LINE  "\n------------------------\n" 
typedef struct address
{
	int no;
	char station[30]; 
	char name[30]; 
	char home[30];
	char tel[30];
	char qq[20];
	char email[30];
	address *next;
}address;

address *head;


void displayaddress(address add)
{
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\n", add.no, add.name, add.home, add.tel, add.qq, add.email);
}


void createheadddresss()
{
	char line[200];
	address *p1, *p2;

	p1 = p2 = (address *)malloc(sizeof(address));
	head = p1;

	p2->next = NULL;
}


void inputstring(char str[], char *description)
{
	printf("请输入%s:", description);
	scanf("%s", str);
	printf("您输入的%s为 %s \n", description, str);
}


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


void addaddress()
{
	int newno = 0, score;
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


bool insert(address *pHead, int front, char *name, char *home, char *tel, char *qq, char *email)
{
	int i = 0, newno;
	address *h = pHead;
	address *t;
	address *n;
	address *x;
	newno = getnewno(&x);
	if ((front < 1) && (NULL != h))
	{
		return false;
	}
	while (i < front - 1)
	{
		h = h->next;
		++i;
	}
	n = (address*)malloc(sizeof(address));

	n->no = newno;
	strcpy(n->name, name);
	strcpy(n->home, home);
	strcpy(n->tel, tel);
	strcpy(n->qq, qq);
	strcpy(n->email, email);

	t = h->next;
	h->next = n;
	n->next = t;
	return true;

}


void deleteaddress(char * name)  
{
	address *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n通讯信息为空!\n");
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
			printf("已删除姓名为%s的通讯信息的通讯信息。\r\n", name);
		}
	}
	else
		printf("没找到姓名为%s的通讯信息!\r\n", name);
}



void displayaddress(char * name)  
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的通讯信息如下\r\n", name);

			printf("序号    姓名    通讯信息\n");

			displayaddress(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的通讯信息\r\n", name);
}


void searchbyname(char * name, address **f)
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
		printf("没找到名为%s的通讯信息\r\n", name);
		*f = NULL;
	}
}

void displayalladdresss()  
{
	address *p = head->next;

	printf("所有通讯信息通讯信息如下\n");
	printf(LINE);

	printf("姓名%t住址%t手机号%tqq%t邮箱\n");
	while (p != NULL)
	{
		displayaddress(*p);
		p = p->next;
	}
	printf(LINE);
}

void promptinsertbeforeno()  
{
	int no, score;
	char name[30] = "";
	char home[30] = "";
	char tel[30] = "";
	char qq[20] = "";
	char email[30] = "";

	printf("\n请输入要在哪个编号的通讯信息之后插入?\n");
	scanf("%d", &no);

	inputstring(name, "姓名");
	inputstring(home, "家庭地址");
	inputstring(tel, "手机号");
	inputstring(qq, "qq号");
	inputstring(email, "邮箱");

	if (insert(head, no, name, home, tel, qq, email))
		printf("\n插入成功！\n");
}



void promptsearchbyname()  
{
	char name[50] = "";
	inputstring(name, "要查找记录的姓名");
	displayaddress(name);
}



void promptdeletebyname()  
{
	char name[50] = "";
	inputstring(name, "要删除记录的姓名");
	deleteaddress(name);
}



int main()
{
	int choice = -1;

	createheadddresss();

	while (choice != 0)
	{
		printf("\n\t 通讯录管理");
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
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptinsertbeforeno();
			break;

		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
		system("pause");
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}