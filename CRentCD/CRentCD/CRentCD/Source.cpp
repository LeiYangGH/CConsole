#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define new (VID *)malloc(sizeof(VID))
#define new1 (VID1 *)malloc(sizeof(VID1))
typedef struct video
{
	long number;
	char name[20];
	struct video *next;
}VID;
typedef struct video1
{
	long number;
	char name[20];
	long date;
	struct video1 *next;
}VID1;
typedef struct consumer
{
	long ID;
	long number;
	char name[20];
	struct consumer *next;
}CON;
VID* CREAT();
void NEW(VID *head, long *number);
void LIST(VID *head);
VID *SEARCH(VID *head, long *number);
VID * DELETE(VID *head, long *number);
VID1 *CREAT1();
void * RENT(VID1 *head1, long *number);
main()
{
	int a;
	long number, number1;
	VID *head = NULL, *s;
	VID1 *head1 = NULL, *s1;
	printf("*******************欢迎使用音像店管理系统**********************\n\n\n");
	printf("\n\n\n0.输入店中当前所有录像带\n\n1.输入所有已出租录像带\n\n2.新录像带入库\n\n3.录像带出租\n\n4.录像带返还\n\n5.显示所有录像带清单\n\n6.查找录像带\n\n7.删除录像带\n\n8.查看某客户录像带租借情况\n\n9.租金管理\n\n");
	printf("\n\n请输入需要进行的操作：");
	scanf("%d", &a);
	switch (a)
	{
	case 0:
		head = CREAT();
		break;
	case 1:
		head1 = CREAT1();
	case 2:
		printf("请输入新录像带编号：");
		scanf("%ld", &number);
		NEW(head, number);
		break;
	case 3:
		printf("请输入租出录像带编号：");
		scanf("%ld", &number);
		RENT(head1, number);
		DELETE(head, number);
		break;
	case 4:
		BACK(video1);
		break;
	case 5:
		LIST(head);
		break;
	case 6:
		printf("请输入需要查找的录像带编号：");
		scanf("%d", &number);
		s = SEARCH(head, number);
		if (s != NULL)
		{
			printf("\n录像带编号为%ld，录像带名称为%s\n", s->number, s->name);
		}
		else
		{
			printf("该录像带当前不在店中。\n");
		}
		break;
	case 7:
		printf("请输入需要删除的录像带编号：");
		scanf("%ld", &number);
		DELETE(head, number);
		break;
	case 8:
		CONSUMER(consumer);
		break;
	case 9:
		MONEY(video1);
		break;
	}
	printf("感谢使用！！\n\n\n");
	return 0;
}
VID* CREAT()/*创建录像带清单*/
{
	int i, n;
	VID *head, *p, *q;
	printf("\n\n请输入总录像带数：");
	scanf("%d", &n);
	head = new;
	p = head;
	for (i == 0; i < n; i++)
	{
		q = new;
		p->next = q;
		printf("\n请输入录像带编号：");
		scanf("%ld", &q->number);
		printf("\n请输入录像带名称：");
		scanf("%s", q->name);
		p = q;
	}
	q->next = NULL;
	return head; void NEW(VID *head, long *number)
}
void NEW(VID *head, long *number)/*插入新录像带*/
{
	VID *p, *q;
	q = head;
	p = new;
	p->number = number;
	printf("请输入录像带名称：");
	scanf("%s", p->name);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
void LIST(VID *head)/*输出店内录像带清单*/
{
	VID *p = head->next;
	printf("\t录像带表编号\t\t录像带名称\n\n");
	While(p != NULL)
	{
		printf("\t%-8ld\t%s\n", p->number, p->name);
		p = p->next;
	}
}
VID *SEARCH(VID *head, long *number)/*查找某录像带*/
{
	VID *p = head->next;
	While(p != NULL&&number != p->number)
	{
		p = p->next;
	}
	return p;
}
VID * DELETE(VID *head, long *number)/*删除录像带信息*/
{
	VID *p = head, *q = head->next;
	while (q != NULL&&number != q->number)
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
VID1 *CREAT1()/*创建已借出录像带清单*/
{
	int i, n;
	VID1 *head1, *p, *q;
	printf("\n\n请输入总录像带数：");
	scanf("%d", &n);
	head1 = new1;
	p = head1;
	for (i == 0; i < n; i++)
	{
		q = new1;
		p->next = q;
		printf("\n请输入录像带编号：");
		scanf("%ld", &q->number);
		printf("\n请输入录像带名称：");
		scanf("%s", q->name);
		printf("请输入录像带借出时间：（例：20160721）");
		scanf("%ld", &q->date);
		p = q;
	}
	q->next = NULL;
	return head1;
}
void * RENT(VID1 *head1, long *number)/*插入新录像带*/
{
	VID1 *p, *q;
	q = head1;
	p = new1;
	p - number = number;
	printf("请输入录像带名称：");
	scanf("%s", p->name);
	printf("请输入录像带租出时间：（例：20160721）");
	scanf("%ld", p->date);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
