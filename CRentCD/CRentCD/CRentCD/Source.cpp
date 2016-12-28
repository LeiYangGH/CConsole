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
	printf("*******************��ӭʹ����������ϵͳ**********************\n\n\n");
	printf("\n\n\n0.������е�ǰ����¼���\n\n1.���������ѳ���¼���\n\n2.��¼������\n\n3.¼�������\n\n4.¼�������\n\n5.��ʾ����¼����嵥\n\n6.����¼���\n\n7.ɾ��¼���\n\n8.�鿴ĳ�ͻ�¼���������\n\n9.������\n\n");
	printf("\n\n��������Ҫ���еĲ�����");
	scanf("%d", &a);
	switch (a)
	{
	case 0:
		head = create();
		break;
	case 1:
		head1 = creater();
	case 2:
		printf("��������¼�����ţ�");
		scanf("%ld", &no);
		add(head, no);
		break;
	case 3:
		printf("���������¼�����ţ�");
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
		printf("��������Ҫ���ҵ�¼�����ţ�");
		scanf("%d", &no);
		s = search(head, no);
		if (s != NULL)
		{
			printf("\n¼������Ϊ%ld��¼�������Ϊ%s\n", s->no, s->name);
		}
		else
		{
			printf("��¼�����ǰ���ڵ��С�\n");
		}
		break;
	case 7:
		printf("��������Ҫɾ����¼�����ţ�");
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
	printf("��лʹ�ã���\n\n\n");
	return 0;
}
cd* create()/*����¼����嵥*/
{
	int i, n;
	cd *head, *p, *q;
	printf("\n\n��������¼�������");
	scanf("%d", &n);
	head = new;
	p = head;
	for (i == 0; i < n; i++)
	{
		q = new;
		p->next = q;
		printf("\n������¼�����ţ�");
		scanf("%ld", &q->no);
		printf("\n������¼������ƣ�");
		scanf("%s", q->name);
		p = q;
	}
	q->next = NULL;
	return head; void add(cd *head, int *no)
}
void add(cd *head, int *no)/*������¼���*/
{
	cd *p, *q;
	q = head;
	p = new;
	p->no = no;
	printf("������¼������ƣ�");
	scanf("%s", p->name);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
void display(cd *head)/*�������¼����嵥*/
{
	cd *p = head->next;
	printf("\t¼�������\t\t¼�������\n\n");
	while (p != NULL)
	{
		printf("\t%-8ld\t%s\n", p->no, p->name);
		p = p->next;
	}
}
cd *search(cd *head, int *no)/*����ĳ¼���*/
{
	cd *p = head->next;
	while (p != NULL&&no != p->no)
	{
		p = p->next;
	}
	return p;
}
cd * deleteone(cd *head, int *no)/*ɾ��¼�����Ϣ*/
{
	cd *p = head, *q = head->next;
	while (q != NULL&&no != q->no)
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
rentcd *creater()/*�����ѽ��¼����嵥*/
{
	int i, n;
	rentcd *head1, *p, *q;
	printf("\n\n��������¼�������");
	scanf("%d", &n);
	head1 = new1;
	p = head1;
	for (i == 0; i < n; i++)
	{
		q = new1;
		p->next = q;
		printf("\n������¼�����ţ�");
		scanf("%ld", &q->no);
		printf("\n������¼������ƣ�");
		scanf("%s", q->name);
		printf("������¼������ʱ�䣺������20160721��");
		scanf("%ld", &q->date);
		p = q;
	}
	q->next = NULL;
	return head1;
}
void * rent(rentcd *head1, int *no)/*������¼���*/
{
	rentcd *p, *q;
	q = head1;
	p = new1;
	p - no = no;
	printf("������¼������ƣ�");
	scanf("%s", p->name);
	printf("������¼������ʱ�䣺������20160721��");
	scanf("%ld", p->date);
	while (q->next)
		q = q->next;
	p->next = q->next;
	q->next = p;
}
