#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 20
#define N 5
//下面两个格式，为了方便，利用了N=5，写死了
//#define FORMAT "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%.2f\r\n"
#define FORMAT "%s\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.2f\r\n"
#define MEMBERS stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4], stu.score[5]
//#define N 2
typedef struct student
{
	char no[12];
	char name[10];
	float score[N + 1];  /*  其中最后一个元素用来保存平均成绩  */
	struct student  *next;
}student;

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaystudent(student stu)
{
	printf(FORMAT, MEMBERS);
	printf("\r\n");
}

student * inputstudents()
{
	int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	student *p1, *p2, *head;
	head = (student *)malloc(sizeof(student));
	p1 = p2 = (student *)malloc(sizeof(student));
	head->next = p1;
	while (1)
	{
		printf("\n\n请输入学生学号(q结束):");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入学生姓名:");
		scanf("%s", name);
		strcpy(p1->no, no);
		strcpy(p1->name, name);
		for (i = 0; i < N; i++)
		{
			printf("\n请输入第%d门课程成绩:", i + 1);
			scanf("%d", &score);
			p1->score[i] = score;
		}
		p1->score[N] = 0;
		p2->next = p1;
		p2 = p1;
		p1 = (student*)malloc(sizeof(student));
		printf("\n学生%s信息添加成功!\n", name);
	}
	p2->next = NULL;
	return head;
}

int deletestudentbyno(student *L, char * no)
{
	student *p1 = L, *p2;
	if (L == NULL)
	{
		printf("\n学生链表为空!\n");
		return 0;
	}
	while (!streq(p1->no, no) && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (streq(p1->no, no))
	{
		if (p1 == L)
			L = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("已删除学号为%s的学生的成绩。\r\n", no);
			return 1;
		}
	}
	else
	{
		printf("没找到学号为%s的学生!\r\n", no);
		return 0;
	}
}

//新增成绩
void calcaverage(student *L)
{
	int i;
	float sum;
	student *n;
	n = L;
	while (n != NULL)
	{
		sum = 0;
		for (i = 0; i < N; i++)
		{
			sum += n->score[i];
		}
		n->score[N] = sum / N;
		n = n->next;
	}
	printf("平均成绩计算完毕\r\n");
}


void displayallstudents(student *head)  //输出所有学生信息
{
	student *p = head->next;
	printf("所有学生成绩如下\r\n");
	printf("学号\t姓名\t课程1\t课程2\t课程3\t课程4\t课程5\t平均\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}

int main()
{
	int choice = -1;
	char no[MAX_STRLEN] = "";
	student *L;
	while (choice != 0)
	{
		printf("\n\t 学生成绩录入删除计算");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入学生成绩");
		printf("\n\t 2. 计算平均");
		printf("\n\t 3. 根据学号删除");
		printf("\n\t 4. 查看所有成绩");
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
			L = inputstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			calcaverage(L);
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			printf("\n\n请输入学生学号:");
			scanf("%s", &no);
			deletestudentbyno(L, no);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallstudents(L);
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