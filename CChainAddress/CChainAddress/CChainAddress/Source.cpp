#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

address *head;//ͷ���

//��ʾһ��ͨѶ��Ϣ
void displayaddress(address add)
{
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\n", add.no, add.name, add.home, add.tel, add.qq, add.email);
	//printf("\r\n");
}

//��ȡ����ͨѶ��Ϣ������
void createheadddresss()
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


//��ȡһ���µ�ͨѶ��Ϣ��Ϣ
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

//����ͨѶ��Ϣ
void addaddress()
{
	int newno = 0, score;//��ͨѶ��Ϣ��ţ���ǰ���+1
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


bool insert(address *pHead, int front, char *name, char *home, char *tel, char *qq, char *email)
{
	int i = 0, newno;
	address *h = pHead;
	address *t;
	address *n;
	address *x;
	newno = getnewno(&x);
	if ((front < 1) && (NULL != h))
	{
		return false;
	}
	while (i < front - 1)
	{
		h = h->next;
		++i;
	}
	n = (address*)malloc(sizeof(address));

	n->no = newno;
	strcpy(n->name, name);
	strcpy(n->home, home);
	strcpy(n->tel, tel);
	strcpy(n->qq, qq);
	strcpy(n->email, email);

	t = h->next;
	h->next = n;
	n->next = t;
	return true;

}

//http://blog.csdn.net/iwm_next/article/details/7450734
void deleteaddress(char * name)  //ɾ��ͨѶ��Ϣ
{
	address *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\nͨѶ��ϢΪ��!\n");
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
			printf("��ɾ������Ϊ%s��ͨѶ��Ϣ��ͨѶ��Ϣ��\r\n", name);
		}
	}
	else
		printf("û�ҵ�����Ϊ%s��ͨѶ��Ϣ!\r\n", name);
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
			printf("%s��ͨѶ��Ϣ����\r\n", name);

			printf("���    ����    ͨѶ��Ϣ\n");

			displayaddress(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ͨѶ��Ϣ\r\n", name);
}

//�������ֲ���ͨѶ��Ϣ
void searchbyname(char * name, address **f)
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
		printf("û�ҵ���Ϊ%s��ͨѶ��Ϣ\r\n", name);
		*f = NULL;
	}
}

void displayalladdresss()  //�������ͨѶ��Ϣ��Ϣ
{
	address *p = head->next;

	printf("����ͨѶ��ϢͨѶ��Ϣ����\n");
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
	char name[30] = "";
	char home[30] = "";
	char tel[30] = "";
	char qq[20] = "";
	char email[30] = "";

	printf("\n������Ҫ���ĸ���ŵ�ͨѶ��Ϣ֮�����?\n");
	scanf("%d", &no);

	inputstring(name, "����");
	inputstring(home, "��ͥ��ַ");
	inputstring(tel, "�ֻ���");
	inputstring(qq, "qq��");
	inputstring(email, "����");

	if (insert(head, no, name, home, tel, qq, email))
		printf("\n����ɹ���\n");
}



void promptsearchbyname()  //����������
{
	char name[50] = "";
	inputstring(name, "Ҫ���Ҽ�¼������");
	displayaddress(name);
}



void promptdeletebyname()  //������ɾ��
{
	char name[50] = "";
	inputstring(name, "Ҫɾ����¼������");
	deleteaddress(name);
}



int main()
{
	int choice = -1;

	createheadddresss();

	while (choice != 0)
	{
		printf("\n\t ͨѶ¼����");
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
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptinsertbeforeno();
			break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
		system("pause");
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}