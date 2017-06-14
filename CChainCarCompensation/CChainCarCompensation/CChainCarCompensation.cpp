#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LINE  "\n------------------------\n" 
typedef struct compensation
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	compensation *next;
}compensation;

compensation *head;
#define T 1
//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}


//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaycompensation(compensation com)
{
	printf("%s\t%s\t%s\t%s\t%d\t%s\n",
		com.no, com.station, com.chassis, com.auditor, com.money, com.date);
}


void createheadddresss()
{
	char line[200];
	compensation *p1, *p2;

	p1 = p2 = (compensation *)malloc(sizeof(compensation));
	head = p1;

	p2->next = NULL;
}


void inputstring(char str[], char *description)
{
	printf("������%s:", description);
	scanf("%s", str);
	printf("�������%sΪ %s \n", description, str);
}

void gettail(compensation **tail)
{
	int newno = 0;
	compensation *p = head;
	/*if (head->no > newno)
		newno = head->no;*/
	while (p->next != NULL)
	{
		/*if (p->no > newno)
			newno = p->no;*/
		p = p->next;
	}
	*tail = p;
}


//void addcompensation(char no[20], char station[20], char chassis[20], char auditor[20], int money, char date[20])
//{
//	compensation stu;
//	strcpy(stu.no, no);
//	strcpy(stu.station, station);
//	strcpy(stu.chassis, chassis);
//	strcpy(stu.auditor, auditor);
//	stu.money = money;
//	strcpy(stu.date, date);
//	allcompensations[allcompensationscount++] = stu;
//	writeallcompensations();
//}

//void promptaddcompensation()


void addcompensation(char no[20], char station[20], char chassis[20], char auditor[20], int money, char date[20])
{

	compensation *p = head;
	compensation *n;

	/*inputstring(no, "���");
	inputstring(station, "station");
	inputstring(chassis, "chassis");
	inputstring(auditor, "auditor");
	printf("������۸�\n", auditor);
	scanf("%d", &money);
	inputstring(date, "date");*/
	gettail(&p);
	n = (compensation *)malloc(sizeof(compensation));

	strcpy(n->no, no);
	strcpy(n->auditor, auditor);
	strcpy(n->station, station);
	strcpy(n->chassis, chassis);
	n->money = money;
	strcpy(n->date, date);

	p->next = n;
	n->next = NULL;
	printf("\n%s����Ϣ��ӳɹ�!\n", auditor);
}

int isnoexists(char no[20])
{
	compensation *p = head;
	while (p != NULL)
	{
		if (streq(p->no, no))
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

void promptaddcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	printf("\n��������:");
	scanf("%s", no);
	if (isnoexists(no))
	{
		printf("���%s�Ѿ����ڣ������ظ������Ʒ!", no);
		return;
	}
	//�����š�����վ���ơ����̺š�����ˡ��������������

	printf("\n���������վ���ơ����̺š�����ˣ����ǲ����ո���ַ��������ո����\n");
	scanf("%s%s%s", station, chassis, auditor);
	printf("\n��������������������������ڣ���ʽ20170614�����ո����\n");
	scanf("%d%s", &money, date);
	addcompensation(no, station, chassis, auditor, money, date);
	printf("���¼��!\r\n");
}

void deletecompensation(char * no)
{
	compensation *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n������ϢΪ��!\n");
		return;
	}
	while (strcmp(p1->no, no) != 0 && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (strcmp(p1->no, no) == 0)
	{

		if (p1 == head)
			head = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("��ɾ�����Ϊ%s��������Ϣ��������Ϣ��\r\n", no);
		}
	}
	else
		printf("û�ҵ����Ϊ%s��������Ϣ!\r\n", no);
}



void displaycompensation(char * auditor)
{
	int found = 0;
	compensation *p = head;

	while (p != NULL)
	{
		if (strcmp(p->auditor, auditor) == 0)
		{
			found = 1;
			printf("%s��������Ϣ����\r\n", auditor);

			//printf("���    ����    ������Ϣ\n");

			displaycompensation(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��������Ϣ\r\n", auditor);
}


void searchbyauditor(char * auditor, compensation **f)
{
	int found = 0;
	compensation *p = head;

	while (p != NULL)
	{
		if (strcmp(p->auditor, auditor) == 0)
		{
			*f = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("û�ҵ���Ϊ%s��������Ϣ\r\n", auditor);
		*f = NULL;
	}
}

void displayallcompensations()
{
	compensation *p = head->next;

	printf("����������Ϣ������Ϣ����\n");
	printf(LINE);
	//�����š�����վ���ơ����̺š�����ˡ��������������
	printf("���%t����վ%t����%t�����%t���%t����\n");
	while (p != NULL)
	{
		displaycompensation(*p);
		p = p->next;
	}
	printf(LINE);
}




void promptsearchbyno()
{
	char no[20] = "";
	inputstring(no, "Ҫ���Ҽ�¼�ı��");
	displaycompensation(no);
}



void promptdeletebyno()
{
	char no[20] = "";
	inputstring(no, "Ҫɾ����¼�ı��");
	deletecompensation(no);
}



int main()
{
	int choice = -1;

	createheadddresss();
#if T
	addcompensation("01", "s1", "c1", "a1", 1, "d1");
	addcompensation("02", "s2", "c2", "a2", 2, "d2");
	addcompensation("03", "s3", "c3", "a3", 3, "d3");
	displayallcompensations();
	promptdeletebyno();
	promptaddcompensation();
	displayallcompensations();

#else
	while (choice != 0)
	{
		printf("\n\t ����¼����");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �����ϵ����Ϣ");
		printf("\n\t 2. �鿴������ϵ����Ϣ");
		printf("\n\t 3. ɾ����ϵ����Ϣ");
		printf("\n\t 4. ������ϵ�����ֲ���");
		printf("\n\t 5. ������ϵ����Ϣ");
		printf("\n\n  ��ѡ��: ");
		choice = getchar();
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
			//addcompensation();
			promptaddcompensation();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallcompensations();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptdeletebyauditor();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptsearchbyauditor();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
		system("pause");
	}
#endif
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}