#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 20
#define FORMAT "%s\t%s\t%.2f\r\n"
#define MEMBERS stu.no, stu.name, stu.score[N]
#define N 2
//#define N 5
typedef struct student
{
	char no[12];
	char name[10];
	float score[N + 1];  /*  其中最后一个元素用来保存平均成绩  */
	struct student  *next;
}student;

char *scoresfile = "scores.txt";
//student *head;

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

//显示一个成绩
void displaystudent(student stu)
{
	printf(FORMAT, MEMBERS);
	//printf("---------------------");
	printf("\r\n");
}


//新增成绩
student * addstudent(student *head)
{
	int i, score;
	float sum = 0;
	student *p = head;
	student *n;
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	printf("请输入学生学号:");
	scanf("%s", &no);
	printf("\n请输入学生姓名:");
	scanf("%s", name);
	n = (student *)malloc(sizeof(student));
	strcpy(n->no, no);
	strcpy(n->name, name);
	for (i = 0; i < N; i++)
	{
		printf("\n请输入第%d们课程成绩:", i + 1);
		scanf("%d", &score);
		n->score[i] = score;
		sum += score;
	}
	n->score[N] = sum / N;
	p->next = n;
	n->next = NULL;
	printf("\n学生%s信息添加成功!\n", name);
	return n;
}

student * inputstudents()
{

	student *p1, *p2, *head;
	head = (student *)malloc(sizeof(student));
	p1 = p2 = (student *)malloc(sizeof(student));
	int i, score;
	float sum = 0;
	head->next = p1;
	//student *p = head;
	//student *n;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入学生学号:");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入学生姓名:");
		scanf("%s", name);
		//n = (student *)malloc(sizeof(student));
		strcpy(p1->no, no);
		strcpy(p1->name, name);
		for (i = 0; i < N; i++)
		{
			printf("\n请输入第%d们课程成绩:", i + 1);
			scanf("%d", &score);
			p1->score[i] = score;
			sum += score;
		}
		p1->score[N] = sum / N;
		//if (head == NULL)
		//	head = p1;
		//else
		p2->next = p1;
		p2 = p1;
		p1 = (student*)malloc(sizeof(student));
		printf("\n学生%s信息添加成功!\n", name);
	}
	p2->next = NULL;
	return head;
}


//http://blog.csdn.net/iwm_next/article/details/7450734
void deletestudentbyno(student *L, char * no)
{
	//char no[MAX_STRLEN] = "";
	//printf("\n\n请输入学生学号:");
	//scanf("%s", &no);
	student *p1 = L, *p2;
	if (L == NULL)
	{
		printf("\n学生链表为空!\n");
		return;
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
		//L->next = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("已删除学号为%s的学生的成绩。\r\n", no);
		}
	}
	else
		printf("没找到学号为%s的学生!\r\n", no);
}




void displayallstudents(student *head)  //输出所有学生信息
{
	student *p = head->next;
	//student *p = head;

	printf("所有学生成绩如下\r\n");
	printf("序号    姓名    成绩\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}



int cmpfunc(const void * a, const void * b)   //成绩比较
{
	return ((student*)a)->score - ((student*)b)->score;
}


int main()
{
	int choice = -1;

	student *head;
	head = inputstudents();

	displayallstudents(head);
	deletestudentbyno(head, "a");
	displayallstudents(head);

	system("pause");
	return 0;
}