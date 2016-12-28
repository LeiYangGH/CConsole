#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define new (cd *)malloc(sizeof(cd))
#define new1 (rentcd *)malloc(sizeof(rentcd))
typedef struct cd
{
	int no;
	char name[20];
	struct cd *next;
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
cd* create();
void add(cd *head, int *no);
void display(cd *head);
cd *search(cd *head, int *no);
cd * deleteone(cd *head, int *no);
rentcd *creater();
void * rent(rentcd *head1, int *no);
main()
{
	int a;
	int no, number1;
	cd *head = NULL, *s;
	rentcd *head1 = NULL, *s1;
	printf("*******************欢迎使用音像店管理系统**********************\n\n\n");
	printf("\n\n\n0.输入店中当前所有录像带\n\n1.输入所有已出租录像带\n\n2.新录像带入库\n\n3.录像带出租\n\n4.录像带返还\n\n5.显示所有录像带清单\n\n6.查找录像带\n\n7.删除录像带\n\n8.查看某客户录像带租借情况\n\n9.租金管理\n\n");
	printf("\n\n请输入需要进行的操作：");
	scanf("%d", &a);
	switch (a)
	{
	case 0:
		head = create();
		break;
	case 1:
		head1 = creater();
	case 2:
		printf("请输入新录像带编号：");
		scanf("%ld", &no);
		add(head, no);
		break;
	case 3:
		printf("请输入租出录像带编号：");
		scanf("%ld", &no);
		rent(head1, no);
		deleteone(head, no);
		break;
	case 4:
		BACK(rentcd);
		break;
	case 5:
		display(head);
		break;
	case 6:
		printf("请输入需要查找的录像带编号：");
		scanf("%d", &no);
		s = search(head, no);
		if (s != NULL)
		{
			printf("\n录像带编号为%ld，录像带名称为%s\n", s->no, s->name);
		}
		else
		{
			printf("该录像带当前不在店中。\n");
		}
		break;
	case 7:
		printf("请输入需要删除的录像带编号：");
		scanf("%ld", &no);
		deleteone(head, no);
		break;
	case 8:
		CONSUMER(customer);
		break;
	case 9:
		MONEY(rentcd);
		break;
	}
	printf("感谢使用！！\n\n\n");
	return 0;
}
cd* create()/*创建录像带清单*/
{
	int i, n;
	cd *head, *p, *q;
	printf("\n\n请输入总录像带数：");
	scanf("%d", &n);
	head = new;
	p = head;
	for (i == 0; i < n; i++)
	{
		q = new;
		p->next = q;
		printf("\n请输入录像带编号：");
		scanf("%ld", &q->no);
		printf("\n请输入录像带名称：");
		scanf("%s", q->name);
		p = q;
	}
	q->next = NULL;
	return head; void add(cd *head, int *no)
}
void add(cd *head, int *no)/*插入新录像带*/
{
	cd *p, *q;
	q = head;
	p = new;
	p->no = no;
	printf("请输入录像带名称：");
	scanf("%s", p->name);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
void display(cd *head)/*输出店内录像带清单*/
{
	cd *p = head->next;
	printf("\t录像带表编号\t\t录像带名称\n\n");
	while (p != NULL)
	{
		printf("\t%-8ld\t%s\n", p->no, p->name);
		p = p->next;
	}
}
cd *search(cd *head, int *no)/*查找某录像带*/
{
	cd *p = head->next;
	while (p != NULL&&no != p->no)
	{
		p = p->next;
	}
	return p;
}
cd * deleteone(cd *head, int *no)/*删除录像带信息*/
{
	cd *p = head, *q = head->next;
	while (q != NULL&&no != q->no)
	{
		q = q->next;
		p = p->next;
	}
	if (q == NULL)
	{
		printf("该编号录像带不存在！\n");
	}
	else
	{
		p->next = q->next;
		free(q);
		printf("删除成功！\n");
	}
	return head;
}
rentcd *creater()/*创建已借出录像带清单*/
{
	int i, n;
	rentcd *head1, *p, *q;
	printf("\n\n请输入总录像带数：");
	scanf("%d", &n);
	head1 = new1;
	p = head1;
	for (i == 0; i < n; i++)
	{
		q = new1;
		p->next = q;
		printf("\n请输入录像带编号：");
		scanf("%ld", &q->no);
		printf("\n请输入录像带名称：");
		scanf("%s", q->name);
		printf("请输入录像带借出时间：（例：20160721）");
		scanf("%ld", &q->date);
		p = q;
	}
	q->next = NULL;
	return head1;
}
void * rent(rentcd *head1, int *no)/*插入新录像带*/
{
	rentcd *p, *q;
	q = head1;
	p = new1;
	p - no = no;
	printf("请输入录像带名称：");
	scanf("%s", p->name);
	printf("请输入录像带租出时间：（例：20160721）");
	scanf("%ld", p->date);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
