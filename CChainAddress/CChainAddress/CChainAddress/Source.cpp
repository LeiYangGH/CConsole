#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
//#define FORMAT3DSD "%d\t%s\t%d\r\n"
#define LINE  "\n------------------------\n"
typedef struct address
{
	int no;
	char name[30];//����ͨѶ¼��ϵ������
	char home[30];//������ϵ�˵ļ�ͥסַ
	char tel[30];//������ϵ�˵ĵ绰����
	char qq[20];//������ϵ�˵�qq����
	char email[30];//������ϵ�˵������ַ
	address *next;
}address;

address *head;

//�ַ���ת����
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}



//��ʾһ���ɼ�
void displayaddress(address add)
{
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\n", add.no, add.name, add.home, add.tel, add.qq, add.email);
	//printf("\r\n");
}

//��ȡ���гɼ�������
void readalladdresss()
{
	char line[200];
	address *p1, *p2;

	p1 = p2 = (address *)malloc(sizeof(address));
	head = p1;

	p2->next = NULL;
}

//����ĳ����ʾ���ַ���
void inputstring(char str[], char *description)
{
	printf("������%s:", description);
	scanf("%s", str);
	printf("�������%sΪ %s \n", description, str);
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
int getnewno(address **tail)
{
	int newno = 0;
	address *p = head;
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
void addaddress()
{
	int newno = 0, score;//�³ɼ���ţ���ǰ���+1
	char name[30] = "";
	char home[30] = "";
	char tel[30] = "";
	char qq[20] = "";
	char email[30] = "";
	address *p = head;
	address *n;

	inputstring(name, "����");
	inputstring(home, "��ͥ��ַ");
	inputstring(tel, "�ֻ���");
	inputstring(qq, "qq��");
	inputstring(email, "����");

	newno = getnewno(&p);

	n = (address *)malloc(sizeof(address));

	n->no = newno;
	strcpy(n->name, name);
	strcpy(n->home, home);
	strcpy(n->tel, tel);
	strcpy(n->qq, qq);
	strcpy(n->email, email);

	p->next = n;
	n->next = NULL;
	printf("\n%s����Ϣ��ӳɹ�!\n", name);
}


bool insert(address *pHead, int front, char *name, int score)
{
	int i = 0, newno;
	address *_node = pHead;
	address *pSwap;
	address *pNew;
	address *x;
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
	pNew = (address*)malloc(sizeof(address));

	pNew->no = newno;
	strcpy(pNew->name, name);
	//pNew->score = score;
	pSwap = _node->next;
	_node->next = pNew;
	pNew->next = pSwap;
	return true;

}



//http://blog.csdn.net/iwm_next/article/details/7450734
void deleteaddress(char * name)  //ɾ���ɼ�
{
	address *p1 = head, *p2;
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



void displayaddress(char * name)  //���������
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s�ĳɼ�����\r\n", name);

			printf("���    ����    �ɼ�\n");

			displayaddress(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
}

void addaddress(char * name)  //׷��ѧ����Ϣ
{
	int found = 0;
	address *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s�ĳɼ�����\r\n", name);

			printf("���    ����    �ɼ�\n");

			displayaddress(*p);
			printf("����ѧ���ɼ�Ϊ��");
			getchar();
			/*	scanf("%d", &p->score);
				printf("�޸ĳɹ������ĺ��ѧ���ɼ��ǣ�%d��\n", p->score);*/
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
}

//********************��ʵ���Կ�����Ϊһ��ͨ�ú������������ø�����������
void searchbyname(char * name, address **f)  //�������ֲ���ѧ��
{
	int found = 0;
	address *p = head;

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

void displayalladdresss()  //�������ѧ����Ϣ
{
	address *p = head->next;

	printf("����ѧ���ɼ�����\n");
	printf(LINE);

	printf("����%tסַ%t�ֻ���%tqq%t����\n");
	while (p != NULL)
	{
		displayaddress(*p);
		p = p->next;
	}
	printf(LINE);
}

void promptinsertbeforeno()  //����Ų���
{
	int no, score;
	char name[50] = "";
	printf("\n������Ҫ���ĸ���ŵ�ѧ��֮�����?\n");
	scanf("%d", &no);

	//inputstring(name);
	score = inputscore();
	if (insert(head, no, name, score))
		printf("\n����ɹ���\n");
}



void promptsearchtotalbyname()  //����������
{
	char name[50] = "";
	//inputstring(name);
	displayaddress(name);
}



void promptdeletebyname()  //������ɾ��
{
	char name[50] = "";
	//inputstring(name);
	deleteaddress(name);
}



int main()
{
	int choice = -1;

	//createsampleaddresss();

	readalladdresss();

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
			//writealladdresss();
			printf("\n\n ��ѡ�����˳�: ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			addaddress();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayalladdresss();
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