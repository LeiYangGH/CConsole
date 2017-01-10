#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FORMAT3DSD "%d\t%s\t%d\r\n"

typedef struct student
{
	int no;
	char name[50];
	int score;
	student *next;
}student;

char *scoresfile = "scores.txt";
student *head;

//字符串转整数
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}

 

//显示一个成绩
void displaystudent(student stu)
{
	printf(FORMAT3DSD, stu.no, stu.name, stu.score);
	printf("\r\n");
}

//读取所有成绩到链表
void readallstudents()
{
	char line[200];
	student *p1, *p2;
	/*FILE *fp = fopen(scoresfile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		fp = fopen(scoresfile, "a+");
		getchar();
	}*/

	p1 = p2 = (student *)malloc(sizeof(student));
	head = p1;
	//while (fgets(line, 1024, fp) != NULL)
	//{
	//	if (strlen(line) < 5)
	//		break;
	//	//读进来的行去掉末尾换行符，重要
	//	//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
	//	strtok(line, "\n");
	//	getstudentfromline(line, p1);
	//	if (head == NULL)
	//		head = p1;
	//	else
	//		p2->next = p1;
	//	p2 = p1;
	//	p1 = (student*)malloc(sizeof(student));
	//}
	p2->next = NULL;
}

//输入成绩信息
void inputname(char str[])
{
	printf("请输入姓名:");
	scanf("%s", str);
	printf("您输入的姓名为为 %s \r\n", str);
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
int getnewno(student **tail)
{
	int newno = 0;
	student *p = head;
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
void addstudent()
{
	int newno = 0, score;//新成绩编号，当前最大+1
	student *p = head;
	student *n;
	char name[50] = "";

	inputname(name);

	newno = getnewno(&p);

	n = (student *)malloc(sizeof(student));

	n->no = newno;
	strcpy(n->name, name);
	score = inputscore();
	n->score = score;

	p->next = n;
	n->next = NULL;
	printf("\n%s成绩%d添加成功!\n", name, score);
}


bool insert(student *pHead, int front, char *name, int score)
{
	int i = 0, newno;
	student *_node = pHead;
	student *pSwap;
	student *pNew;
	student *x;
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
	pNew = (student*)malloc(sizeof(student));

	pNew->no = newno;
	strcpy(pNew->name, name);
	pNew->score = score;
	pSwap = _node->next;
	_node->next = pNew;
	pNew->next = pSwap;
	return true;

}



//http://blog.csdn.net/iwm_next/article/details/7450734
void deletestudent(char * name)  //删除成绩
{
	student *p1 = head, *p2;
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



void displaystudent(char * name)  //按姓名输出
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的成绩如下\r\n", name);

			printf("序号    姓名    成绩\n");

			displaystudent(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的学生\r\n", name);
}

void addstudent(char * name)  //追加学生信息
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的成绩如下\r\n", name);

			printf("序号    姓名    成绩\n");

			displaystudent(*p);
			printf("更改学生成绩为：");
			getchar();
			scanf("%d", &p->score);
			printf("修改成功，更改后的学生成绩是：%d。\n", p->score);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的学生\r\n", name);
}

//********************其实可以考虑作为一个通用函数，但我懒得改其他函数了
void searchbyname(char * name, student **f)  //根据名字查找学生
{
	int found = 0;
	student *p = head;

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

void displayallstudents()  //输出所有学生信息
{
	student *p = head->next;

	printf("所有学生成绩如下\n");
	printf("---------------------\n");

	printf("序号    姓名    成绩\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
	printf("---------------------\n");

}

void promptinsertbeforeno()  //按编号插入
{
	int no, score;
	char name[50] = "";
	printf("\n请输入要在哪个编号的学生之后插入?\n");
	scanf("%d", &no);

	inputname(name);
	score = inputscore();
	if (insert(head, no, name, score))
		printf("\n插入成功！\n");
}



void promptsearchtotalbyname()  //按姓名查找
{
	char name[50] = "";
	inputname(name);
	displaystudent(name);
}



void promptdeletebyname()  //按姓名删除
{
	char name[50] = "";
	inputname(name);
	deletestudent(name);
}

 

int main()
{
	int choice = -1;

	//createsamplestudents();

	readallstudents();

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
			//writeallstudents();
			printf("\n\n 你选择了退出: ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			addstudent();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallstudents();
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