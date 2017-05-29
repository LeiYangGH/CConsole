#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 20
#define N 5
//����������ʽ��Ϊ�˷��㣬������N=5��д����
//#define FORMAT "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%.2f\r\n"
#define FORMAT "%s\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.2f\r\n"
#define MEMBERS stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4], stu.score[5]
//#define N 2
typedef struct student
{
	char no[12];
	char name[10];
	float score[N + 1];  /*  �������һ��Ԫ����������ƽ���ɼ�  */
	struct student  *next;
}student;

//�ַ������
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
		printf("\n\n������ѧ��ѧ��(q����):");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ѧ������:");
		scanf("%s", name);
		strcpy(p1->no, no);
		strcpy(p1->name, name);
		for (i = 0; i < N; i++)
		{
			printf("\n�������%d�ſγ̳ɼ�:", i + 1);
			scanf("%d", &score);
			p1->score[i] = score;
		}
		p1->score[N] = 0;
		p2->next = p1;
		p2 = p1;
		p1 = (student*)malloc(sizeof(student));
		printf("\nѧ��%s��Ϣ���ӳɹ�!\n", name);
	}
	p2->next = NULL;
	return head;
}

int deletestudentbyno(student *L, char * no)
{
	student *p1 = L, *p2;
	if (L == NULL)
	{
		printf("\nѧ������Ϊ��!\n");
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
			printf("��ɾ��ѧ��Ϊ%s��ѧ���ĳɼ���\r\n", no);
			return 1;
		}
	}
	else
	{
		printf("û�ҵ�ѧ��Ϊ%s��ѧ��!\r\n", no);
		return 0;
	}
}

//�����ɼ�
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
	printf("ƽ���ɼ��������\r\n");
}


void displayallstudents(student *head)  //�������ѧ����Ϣ
{
	student *p = head->next;
	printf("����ѧ���ɼ�����\r\n");
	printf("ѧ��\t����\t�γ�1\t�γ�2\t�γ�3\t�γ�4\t�γ�5\tƽ��\r\n");
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
		printf("\n\t ѧ���ɼ�¼��ɾ������");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��ѧ���ɼ�");
		printf("\n\t 2. ����ƽ��");
		printf("\n\t 3. ����ѧ��ɾ��");
		printf("\n\t 4. �鿴���гɼ�");
		printf("\n\n  ��ѡ��: ");
		choice = getche();
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			L = inputstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			calcaverage(L);
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			printf("\n\n������ѧ��ѧ��:");
			scanf("%s", &no);
			deletestudentbyno(L, no);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallstudents(L);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}