#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct student
{
	char no[20];
	char name[20];
	char score[3];
	student *next;
}student;

int count;//ʵ������ĸ���������ʱ�����û��10��

void fillstudent(student *n)
{
	printf("����������ѧ����ѧ�ţ�������3�ſγ̵ĳɼ�(����)���ո�������س�����\n");
	scanf("%s%s%d%d%d", n->no, n->name, &n->score[0], &n->score[1], &n->score[2]);
	fseek(stdin, 0, SEEK_END);
	printf("%s����Ϣ��ӳɹ�!\n", n->name);
}

student *create(int maxcount)
{
	student *head;
	student *p1 = NULL;
	student *p2 = NULL;

	count = 0;
	p1 = (student *)malloc(sizeof(student));
	p2 = p1;

	if (p1 == NULL)
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else
	{
		head = NULL;
		fillstudent(p1);
	}
	while (count < maxcount)
	{
		count += 1;
		if (count == 1)
		{
			head = p1;
			p2->next = NULL;
		}
		else
		{
			p2->next = p1;
		}

		p2 = p1;

		p1 = (student *)malloc(sizeof(student));
		if (count < maxcount)
			fillstudent(p1);
	}
	p2->next = NULL;

	free(p1);
	p1 = NULL;
	return head;
}


void print(student *head)
{
	student *p;
	p = head;
	if (head != NULL)
	{
		do
		{
			printf("%s\t%s\t%d\t%d\t%d\n",
				p->no, p->name, p->score[0], p->score[1], p->score[2]);
			p = p->next;
		} while (p != NULL);
	}
}

float calccourseave(student *head, int courseid)
{
	int sum = 0;
	student *p;
	p = head;
	if (head != NULL)
	{
		do
		{
			sum += p->score[courseid];
			p = p->next;
		} while (p != NULL);
	}
	return sum / (float)count;
}

void calcbeststu(student *head)
{
	int sum = 0, bestsum = 0;

	student beststu;

	student *p;
	p = head;
	if (head != NULL)
	{
		do
		{
			sum = p->score[0] + p->score[1] + p->score[2];
			if (bestsum < sum)
			{
				bestsum = sum;
				beststu = *p;
			}
			p = p->next;
		} while (p != NULL);
	}
	printf("�ܷ���ߵ�ѧ��ѧ��:%s������:%s��3�ſγ̳ɼ�:%d %d %d��ƽ������:%.1f\n",
		beststu.no, beststu.name,
		beststu.score[0], beststu.score[1], beststu.score[2],
		bestsum / 3.0f);

}

int main()
{
	int courseid;
	printf("����λ10��ѧ���ĳɼ���Ϣ��\n");
	student *head = create(10);
	//print(head);//�������ѧ����Ϣ
	for (courseid = 0; courseid < 3; courseid++)
	{
		printf("��%d�Ƶ�ƽ���ɼ���%.1f\n", courseid, calccourseave(head, courseid));
	}
	calcbeststu(head);
	system("pause");
	return 0;
}