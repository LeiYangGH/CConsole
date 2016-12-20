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

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

char *scoresfile = "scores.txt";
student *head;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//从一行文本拆分出成绩 
void getstudentfromline(char *line, student *adg)
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
			strcpy(adg->name, part);
			break;
		case 3:
			adg->score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}


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
	FILE *fp = fopen(scoresfile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (student *)malloc(sizeof(student));
	head = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//读进来的行去掉末尾换行符，重要
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getstudentfromline(line, p1);
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (student*)malloc(sizeof(student));
	}
	p2->next = NULL;
}


//保存所有成绩
void writeallstudents()
{
	student *p;
	FILE *fp = fopen(scoresfile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = head;

	while (p != NULL)
	{
		student stu = *p;

		fprintf(fp, FORMAT3DSD, stu.no, stu.name, stu.score);
		p = p->next;
	}
	fclose(fp);
	printf("已保存到文件。");
}


//输入成绩信息
void inputname(char str[])
{
	//int len = -1;
	//while (len < 2 || len > 49)
	//{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	//	scanf("%s", str);
	//	len = strlen(str);
	//}
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

//删除成绩
//http://blog.csdn.net/iwm_next/article/details/7450734
void deletestudent(char * name)
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

void viewstudent(char * name)
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s的成绩如下\r\n", name);

			displaystudent(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("没找到名为%s的学生\r\n", name);
}

void viewallstudents()
{
	student *p = head;

	printf("所有学生成绩如下\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}

void createsamplestudents()
{
	FILE *fp = fopen(scoresfile, "wb");
	printf("创建示例成绩数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMAT3DSD, 1, "Flex", 75);
	fprintf(fp, FORMAT3DSD, 2, "Tony", 80);
	fprintf(fp, FORMAT3DSD, 3, "测试中文姓名", 90);
	fprintf(fp, FORMAT3DSD, 4, "Lukas", 88);
	fprintf(fp, FORMAT3DSD, 5, "Shawn", 100);

	fclose(fp);
	printf("5条示例成绩数据已保存到student.txt。");
}

int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->score - ((student*)b)->score;
}
void sortandviewall()
{
	int i, cnt = 0;
	student all[50];
	student *p = head;

	printf("所有学生成绩升序排序输出如下\r\n");
	while (p != NULL)
	{
		student stu;
		stu.no = p->no;
		strcpy(stu.name, p->name);
		stu.score = p->score;
		all[cnt++] = stu;
		p = p->next;
	}
	qsort(all, cnt, sizeof(student), cmpfunc);
	for (i = 0; i < cnt; i++)
	{
		displaystudent(all[i]);
	}
}

void promptinsertbeforeno()
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

void promptsearchtotalbyname()
{
	char name[50] = "";
	inputname(name);
	viewstudent(name);
}

void promptdeletebyname()
{
	char name[50] = "";
	inputname(name);
	deletestudent(name);
}

int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入密码\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
}

int main()
{
	int choice = -1;

	if (login())
	{
		printf("login ok\n");
	}
	else
		printf("login fail\n");

	//createsamplestudents();

	//readallstudents();
	//viewallstudents();
	//addstudent();
	//writeallstudents();

	//char name[20] = "Miller";
	//deletestudent(delname);

	//viewstudent(name);
	//sortandviewall();

	/*char name[20] = "insert";
	int sc = 55;
	if (insert(head, 3, name, sc))
	printf("\nisnerted\n");*/
	//viewallstudents();
	//while (choice != 0)
	//{
	//	printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
	//	printf("\n\t------------------------------");
	//	printf("\n\n\t 0. 退出 0");
	//	printf("\n\n\t 1. 添加 1");
	//	printf("\n\t 2. 删除 2");
	//	printf("\n\t 3. 查看所有 3");
	//	printf("\n\t 4. 根据姓名查找单个 4");
	//	printf("\n\t 5. 按成绩递增排序 5");
	//	printf("\n\t 6. 插入 6");
	//	printf("\n\t 7. 保存 7");
	//	printf("\n\n 请选择: ");
	//	scanf("%1[01234567]d%*c", &choice);
	//	choice = getche();
	//	switch (choice)
	//	{
	//	case '0':
	//		printf("\n\n 你选择了退出: ");
	//		fseek(stdin, 0, SEEK_END);
	//		system("pause");
	//		exit(0);
	//		break;
	//	case '1':
	//		printf("\n\n你选择了 1\n");
	//		addstudent();
	//		break;
	//	case '2':
	//		printf("\n\n你选择了 2\n");
	//		promptdeletebyname();
	//		break;
	//	case '3':
	//		printf("\n\n你选择了 3\n");
	//		viewallstudents();
	//		break;
	//	case '4':
	//		printf("\n\n你选择了 4\n");
	//		promptsearchtotalbyname();
	//		break;
	//	case '5':
	//		printf("\n\n你选择了 5\n");
	//		sortandviewall();
	//		break;
	//	case '6':
	//		printf("\n\n你选择了 6\n");
	//		promptinsertbeforeno();
	//		break;
	//	case '7':
	//		printf("\n\n你选择了 7\n");
	//		writeallstudents();
	//		break;
	//	default:
	//		printf("\n\n输入有误，请重选\n");
	//		break;
	//	}
	//	getch();
	//}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

