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
	printf("*******************��ӭʹ����������ϵͳ**********************\n\n\n");
	printf("\n\n\n0.������е�ǰ����¼���\n\n1.���������ѳ���¼���\n\n2.��¼������\n\n3.¼�������\n\n4.¼�������\n\n5.��ʾ����¼����嵥\n\n6.����¼���\n\n7.ɾ��¼���\n\n8.�鿴ĳ�ͻ�¼���������\n\n9.������\n\n");
	printf("\n\n��������Ҫ���еĲ�����");
	scanf("%d", &a);
	switch (a)
	{
	case 0:
		head = CREAT();
		break;
	case 1:
		head1 = CREAT1();
	case 2:
		printf("��������¼�����ţ�");
		scanf("%ld", &number);
		NEW(head, number);
		break;
	case 3:
		printf("���������¼�����ţ�");
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
		printf("��������Ҫ���ҵ�¼�����ţ�");
		scanf("%d", &number);
		s = SEARCH(head, number);
		if (s != NULL)
		{
			printf("\n¼������Ϊ%ld��¼�������Ϊ%s\n", s->number, s->name);
		}
		else
		{
			printf("��¼�����ǰ���ڵ��С�\n");
		}
		break;
	case 7:
		printf("��������Ҫɾ����¼�����ţ�");
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
	printf("��лʹ�ã���\n\n\n");
	return 0;
}
VID* CREAT()/*����¼����嵥*/
{
	int i, n;
	VID *head, *p, *q;
	printf("\n\n��������¼�������");
	scanf("%d", &n);
	head = new;
	p = head;
	for (i == 0; i < n; i++)
	{
		q = new;
		p->next = q;
		printf("\n������¼�����ţ�");
		scanf("%ld", &q->number);
		printf("\n������¼������ƣ�");
		scanf("%s", q->name);
		p = q;
	}
	q->next = NULL;
	return head; void NEW(VID *head, long *number)
}
void NEW(VID *head, long *number)/*������¼���*/
{
	VID *p, *q;
	q = head;
	p = new;
	p->number = number;
	printf("������¼������ƣ�");
	scanf("%s", p->name);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
void LIST(VID *head)/*�������¼����嵥*/
{
	VID *p = head->next;
	printf("\t¼�������\t\t¼�������\n\n");
	While(p != NULL)
	{
		printf("\t%-8ld\t%s\n", p->number, p->name);
		p = p->next;
	}
}
VID *SEARCH(VID *head, long *number)/*����ĳ¼���*/
{
	VID *p = head->next;
	While(p != NULL&&number != p->number)
	{
		p = p->next;
	}
	return p;
}
VID * DELETE(VID *head, long *number)/*ɾ��¼�����Ϣ*/
{
	VID *p = head, *q = head->next;
	while (q != NULL&&number != q->number)
	{
		q = q->next;
		p = p->next;
	}
	if (q == NULL)
	{
		printf("�ñ��¼��������ڣ�\n");
	}
	else
	{
		p->next = q->next;
		free(q);
		printf("ɾ���ɹ���\n");
	}
	return head;
}
VID1 *CREAT1()/*�����ѽ��¼����嵥*/
{
	int i, n;
	VID1 *head1, *p, *q;
	printf("\n\n��������¼�������");
	scanf("%d", &n);
	head1 = new1;
	p = head1;
	for (i == 0; i < n; i++)
	{
		q = new1;
		p->next = q;
		printf("\n������¼�����ţ�");
		scanf("%ld", &q->number);
		printf("\n������¼������ƣ�");
		scanf("%s", q->name);
		printf("������¼������ʱ�䣺������20160721��");
		scanf("%ld", &q->date);
		p = q;
	}
	q->next = NULL;
	return head1;
}
void * RENT(VID1 *head1, long *number)/*������¼���*/
{
	VID1 *p, *q;
	q = head1;
	p = new1;
	p - number = number;
	printf("������¼������ƣ�");
	scanf("%s", p->name);
	printf("������¼������ʱ�䣺������20160721��");
	scanf("%ld", p->date);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
