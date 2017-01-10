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

char *scoresfile = "scores.txt";
student *head;

//�ַ���ת����
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}

 

//��ʾһ���ɼ�
void displaystudent(student stu)
{
	printf(FORMAT3DSD, stu.no, stu.name, stu.score);
	printf("\r\n");
}

//��ȡ���гɼ�������
void readallstudents()
{
	char line[200];
	student *p1, *p2;
	/*FILE *fp = fopen(scoresfile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		fp = fopen(scoresfile, "a+");
		getchar();
	}*/

	p1 = p2 = (student *)malloc(sizeof(student));
	head = p1;
	//while (fgets(line, 1024, fp) != NULL)
	//{
	//	if (strlen(line) < 5)
	//		break;
	//	//����������ȥ��ĩβ���з�����Ҫ
	//	//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
	//	strtok(line, "\n");
	//	getstudentfromline(line, p1);
	//	if (head == NULL)
	//		head = p1;
	//	else
	//		p2->next = p1;
	//	p2 = p1;
	//	p1 = (student*)malloc(sizeof(student));
	//}
	p2->next = NULL;
}

//����ɼ���Ϣ
void inputname(char str[])
{
	printf("����������:");
	scanf("%s", str);
	printf("�����������ΪΪ %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("���������1��100:");
		scanf("%d", &n);
	}
	return n;
}
//��ȡһ���µ�ѧ����Ϣ
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

//�����ɼ�
void addstudent()
{
	int newno = 0, score;//�³ɼ���ţ���ǰ���+1
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
	printf("\n%s�ɼ�%d��ӳɹ�!\n", name, score);
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



//http://blog.csdn.net/iwm_next/article/details/7450734
void deletestudent(char * name)  //ɾ���ɼ�
{
	student *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n�ɼ�Ϊ��!\n");
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
			printf("��ɾ������Ϊ%s��ѧ���ĳɼ���\r\n", name);
		}
	}
	else
		printf("û�ҵ�����Ϊ%s��ѧ��!\r\n", name);
}



void displaystudent(char * name)  //���������
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s�ĳɼ�����\r\n", name);

			printf("���    ����    �ɼ�\n");

			displaystudent(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
}

void addstudent(char * name)  //׷��ѧ����Ϣ
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s�ĳɼ�����\r\n", name);

			printf("���    ����    �ɼ�\n");

			displaystudent(*p);
			printf("����ѧ���ɼ�Ϊ��");
			getchar();
			scanf("%d", &p->score);
			printf("�޸ĳɹ������ĺ��ѧ���ɼ��ǣ�%d��\n", p->score);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
}

//********************��ʵ���Կ�����Ϊһ��ͨ�ú������������ø�����������
void searchbyname(char * name, student **f)  //�������ֲ���ѧ��
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			*f = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
		*f = NULL;
	}
}

void displayallstudents()  //�������ѧ����Ϣ
{
	student *p = head->next;

	printf("����ѧ���ɼ�����\n");
	printf("---------------------\n");

	printf("���    ����    �ɼ�\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
	printf("---------------------\n");

}

void promptinsertbeforeno()  //����Ų���
{
	int no, score;
	char name[50] = "";
	printf("\n������Ҫ���ĸ���ŵ�ѧ��֮�����?\n");
	scanf("%d", &no);

	inputname(name);
	score = inputscore();
	if (insert(head, no, name, score))
		printf("\n����ɹ���\n");
}



void promptsearchtotalbyname()  //����������
{
	char name[50] = "";
	inputname(name);
	displaystudent(name);
}



void promptdeletebyname()  //������ɾ��
{
	char name[50] = "";
	inputname(name);
	deletestudent(name);
}

 

int main()
{
	int choice = -1;

	//createsamplestudents();

	readallstudents();

	while (choice != 0)
	{
		printf("\n\t �質��������");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �����ϵ����Ϣ");
		printf("\n\t 2. �鿴������ϵ����Ϣ");
		printf("\n\t 3. ɾ����ϵ����Ϣ");
		printf("\n\t 4. ������ϵ�����ֲ���");
		printf("\n\t 5. ������ϵ����Ϣ");
		printf("\n\n  ��ѡ��: ");
		choice = getchar();//����һ���ַ�
		switch (choice)
		{
		case '0':
			//writeallstudents();
			printf("\n\n ��ѡ�����˳�: ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			addstudent();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptdeletebyname();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptsearchtotalbyname();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptinsertbeforeno();
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