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

int n;

void fillstudent(student *n)
{
	printf("����������ѧ����ѧ�ţ�������3�ſγ̵ĳɼ�(����)���ո�������س�����\n");
	scanf("%s%s%d%d%d", n->no, n->name, &n->score[0], &n->score[1], &n->score[2]);
	fseek(stdin, 0, SEEK_END);
	printf("\n%s����Ϣ��ӳɹ�!\n", n->name);
}

student *create()
{
	int max = 3;
	student *head;       //ͷ�ڵ�
	student *p1 = NULL;  //p1���洴�����½ڵ�ĵ�ַ
	student *p2 = NULL;  //p2����ԭ�������һ���ڵ�ĵ�ַ

	n = 0;          //����ǰ����Ľڵ�����Ϊ0��������
	p1 = (student *)malloc(sizeof(student));   //����һ���½ڵ�
	p2 = p1;            //����ڵ㿪�ٳɹ�����p2�Ȱ�����ָ�뱣�������Ա�����

	if (p1 == NULL)        //�ڵ㿪�ٲ��ɹ�
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //�ڵ㿪�ٳɹ�
	{
		head = NULL;        //��ʼheadָ��NULL
		//strcpy(p1->name, "n1");
		//strcpy(p1->tel, "111");
		fillstudent(p1);
	}
#if 1
	while (n < max)      //ֻҪѧ�Ų�Ϊ0���ͼ���¼����һ���ڵ�
	{
		n += 1;         //�ڵ���������1��
		if (n == 1)      //����ڵ�������1����headָ��մ����Ľڵ�p1
		{
			head = p1;
			p2->next = NULL;  //��ʱ��p2����p1,Ҳ����p1->nextָ��NULL��
		}
		else
		{
			p2->next = p1;   //ָ���ϴ�����ոտ��ٵ��½ڵ�
		}

		p2 = p1;            //��p1�ĵ�ַ��p2������Ȼ��p1�����µĽڵ�

		p1 = (student *)malloc(sizeof(student));

		if (n < max)
			fillstudent(p1);
		//n++;
		/*++nn;
		sprintf(name, "n%d", nn * 2);
		sprintf(tel, "t%d", nn * 22);
		strcpy(p1->name, name);
		strcpy(p1->tel, tel);*/
	}
#endif
	p2->next = NULL;     //�˾���Ǹ��ݵ�����������һ���ڵ�Ҫָ��NULL

	free(p1);           //p1->numΪ0��ʱ��������whileѭ���������ͷ�p1
	p1 = NULL;          //�ر�Ҫ���ǰ��ͷŵı��������ΪNULL,����ͱ��"Ұָ��"������ַ��ȷ����ָ��
	return head;        //���ش��������ͷָ��
}


void print(student *head)
{
	student *p;
	//printf("\nNow , These %d records are:\n", n);
	p = head;
	//p = head->next;
	if (head != NULL)        //ֻҪ���ǿ�������������������нڵ�
	{
		//printf("head is %o\n", head);    //���ͷָ��ָ��ĵ�ַ
		do
		{
			/*
			�����Ӧ��ֵ����ǰ�ڵ��ַ�����ֶ�ֵ����ǰ�ڵ����һ�ڵ��ַ��
			����������ڶ������󿴵�һ�����������ڼ�����еĴ洢�ṹ��������
			��Ƶ�ͼʾ��һģһ���ġ�
			*/
			//printf("%s %s\n", p->name, p->tel);
			student stu = *p;

			printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2]);

			p = p->next;     //�Ƶ���һ���ڵ�
		} while (p != NULL);
	}
}

//��ʾһ��ͨѶ��Ϣ
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2]);
}



//����ͨѶ��Ϣ






int main()
{
	student *head = create();


#if 1

	print(head);
#endif


	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}