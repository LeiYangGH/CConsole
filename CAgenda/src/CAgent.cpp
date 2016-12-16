// ConsoleApplication19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"//comment in vc6
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include "windows.h"

typedef struct user
{
	char name[20];
	char pwd[20];
	struct user *next;
}user;

typedef struct agenda
{
	int no;
	char affair[50];
	char createddt[15];
	//�ÿ�ʼ���������������time_t����
	//�������ڶ�ֻ�ǿ��ģ�������ַ�������ȥ��дʱ��ת���鷳
	time_t startdt;
	char enddt[15];
	char name[20];
	struct agenda *next;
}agenda;

char *agendafile = "agenda.txt";
char *userfile = "user.txt";
agenda *head;
user *allusers;
user curuser;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//������һЩ���ں���
//http://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c
time_t createdate(int y, int m, int d)
{
	struct tm date = { 0 };
	date.tm_year = y - 1900;
	date.tm_mon = m;
	date.tm_mday = d;
	return mktime(&date);
}

time_t convertdate(char* str)
{
	int y, m, d;
	struct tm date = { 0 };
	sscanf(str, "%d-%d-%d", &y, &m, &d);
	date.tm_year = y - 1900;
	date.tm_mon = m;
	date.tm_mday = d;
	return mktime(&date);
}

void formatdate(time_t dt, char *str)
{
	struct tm *ptr;
	ptr = localtime(&dt);
	strftime(str, 20, "%Y-%m-%d", ptr);
}

time_t getcurdate()
{
	return time(NULL);
}

//��һ���ı���ֳ��ճ� 
void getagendafromline(char *line, agenda *adg)
{
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			adg->no = toint(part);
			break;
		case 2:
			strcpy(adg->affair, part);
			break;
		case 3:
			strcpy(adg->createddt, part);
			break;
		case 4:
			adg->startdt = convertdate(part);
			break;
		case 5:
			strcpy(adg->enddt, part);
			break;
		case 6:
			strcpy(adg->name, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}

//��һ���ı���ֳ��ճ� 
void getuserfromline(char *line, user *usr)
{
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(usr->name, part);
			break;
		case 2:
			strcpy(usr->pwd, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}

//��ʾһ���ճ� 
void displayagenda(agenda agd)
{
	char str[15] = "";
	formatdate(agd.startdt, str);
	printf("%d\t%s\t%s\t%s\t%s\t%s\r\n", agd.no, agd.affair, agd.createddt,
		str, agd.enddt, agd.name);
	printf("\r\n");
}

//��ȡ�����ճ̵�����
void readallagendas()
{
	char line[200];
	agenda *p1, *p2;
	FILE *fp = fopen("Agenda.txt", "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (agenda *)malloc(sizeof(agenda));
	head = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//����������ȥ��ĩβ���з�����Ҫ
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getagendafromline(line, p1);
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (agenda*)malloc(sizeof(agenda));
	}
	p2->next = NULL;
}

//��ȡ�����û�������
void readallusers()
{
	char line[200];
	user *p1, *p2;
	FILE *fp = fopen("user.txt", "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (user *)malloc(sizeof(user));
	allusers = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//����������ȥ��ĩβ���з�����Ҫ
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getuserfromline(line, p1);
		if (allusers == NULL)
			allusers = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (user*)malloc(sizeof(user));
	}
	p2->next = NULL;
}

//���������ճ�
void writeallagendas()
{
	char str[15] = "";
	agenda *p;
	FILE *fp = fopen(agendafile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = head;

	while (p != NULL)
	{
		agenda agd = *p;
		formatdate(agd.startdt, str);
		fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\r\n", agd.no, agd.affair, agd.createddt,
			str, agd.enddt, agd.name);
		p = p->next;
	}
	fclose(fp);
	printf("�ѱ��浽�ļ���");
}

//���������û�
void writeallusers()
{
	char str[15] = "";
	user *p;
	FILE *fp = fopen(userfile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = allusers;

	while (p != NULL)
	{
		user usr = *p;
		fprintf(fp, "%s\t%s\r\n", usr.name, usr.pwd);
		p = p->next;
	}
	fclose(fp);
	printf("�ѱ��浽�ļ���");
}

//�����ճ���Ϣ
void inputaffair(char str[])
{
	int len = -1;
	while (len < 5 || len > 49)
	{
		printf("�������ճ�����(5-45���ַ�)�������Ӣ�ģ���̣����ܴ�Tab��س���:");
		scanf("%s", str);
		len = strlen(str);
	}
	printf("�����ճ�����Ϊ %s \r\n", str);
}


//�ճ̿�ʼ/���������� 
void inputdate(char date[], char *purpose)
{
	int len = -1;
	char input[20] = "";
	//���ڸ�ʽӦ�ü��Ϊ��ʵ���ڣ��ұ�����δ������
	//�����ֻ��֤����Ϊ10 
	while (len != 10)
	{
		printf("����������%s���ڣ��ϸ����¸�ʽ2016-06-23:", purpose);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(date, input);
	printf("��ѡ���%s����Ϊ %s \r\n", purpose, input);
}

//�����ճ�
void addagenda()
{
	int newno = 0;//���ճ̱�ţ���ǰ���+1
	char cur[15] = "";
	agenda *p = head;
	agenda *n;
	char info[50] = "";
	char sdt[15] = "";
	char edt[15] = "";
	inputaffair(info);
	inputdate(sdt, "��ʼ");
	inputdate(edt, "����");

	/*only test
	char info[] = "test event";
	char sdt[] = "2016-06-27";
	char edt[] = "2016-06-28";
	*/
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
	n = (agenda *)malloc(sizeof(agenda));

	n->no = newno;
	strcpy(n->affair, info);
	formatdate(getcurdate(), cur);
	strcpy(n->createddt, cur);
	n->startdt = convertdate(sdt);
	strcpy(n->enddt, edt);
	strcpy(n->name, curuser.name);

	p->next = n;
	n->next = NULL;

	writeallagendas();
}

//�����û�
void adduser()
{
	int exists = 0;
	user *p = allusers;
	user *n;
	//*
	char name[20] = "";
	char pwd[20] = "";
	printf("������ע����û���:");
	scanf("%s", name);
	printf("������ע�������:");
	scanf("%s", pwd);
	//TO DO: ��֤����ǿ�Ⱥ�ȷ�������
	//*/

	/*only test
	char name[] = "user2";
	char pwd[] = "pwd2";
	*/

	if (strcmp(allusers->name, name) == 0)
		exists = 1;
	while (p->next != NULL)
	{
		if (strcmp(p->name, name) == 0)
			exists = 1;
		p = p->next;
	}
	if (strcmp(p->name, name) == 0)
		exists = 1;
	if (exists)
	{
		printf("���û��Ѿ����ڣ������ظ�ע��\r\n");
		return;
	}
	n = (user *)malloc(sizeof(user));

	strcpy(n->name, name);
	strcpy(n->pwd, pwd);

	p->next = n;
	n->next = NULL;

	writeallusers();

	strcpy(curuser.name, name);
	strcpy(curuser.pwd, pwd);
	printf("��ϲ��ע��ɹ����û��� %s ���� %s \r\n", name, pwd);
}

//ɾ���ճ�
//http://blog.csdn.net/iwm_next/article/details/7450734
//To do: ɾ����һ��ò�������⣬�Լ�����
void deleteagenda(char * curname, int delno)//�������������
{
	agenda *p1 = head, *p2;
	if (delno <= 0)
	{
		printf("������Ҫɾ�����ճ̱��\r\n");
		scanf("%d", &delno);
	}

	if (head == NULL)
	{
		printf("\n�ճ�Ϊ��!\n");
		return;
	}
	while (delno != p1->no && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (delno == p1->no)
	{
		if (strcmp(p1->name, curname) == 0)
		{
			if (p1 == head)
				head = p1->next;
			else
			{
				p2->next = p1->next;
				free(p1);
				writeallagendas();
				printf("��ɾ�����Ϊ%d���ճ̡�\r\n", delno);
			}
		}
		else
			printf("���Ϊ%d���ճ����������ˣ�����ɾ����\r\n", delno);
	}
	else
		printf("û�ҵ����Ϊ%d���ճ�!\r\n", delno);
}

//����ճ�
void viewagenda(char * curname, time_t curdate, int old)//curname, curdate���������
{
	agenda *p = head;

	printf("����%s�ճ�����\r\n", old ? "��ʷ" : "δ��");
	while (p != NULL)
	{
		if (strcmp(p->name, curname) == 0 &&
			(old && p->startdt < curdate ||
			!old && p->startdt >= curdate))
			displayagenda(*p);
		p = p->next;
	}
}

void login()
{
	int success = 0;
	user *p = allusers;
	char name[20] = "";
	char pwd[20] = "";
	printf("����������ע����û���:");
	scanf("%s", name);
	printf("�������Ӧ������:");
	scanf("%s", pwd);

	if (strcmp(allusers->name, name) == 0
		&& strcmp(allusers->pwd, pwd) == 0)
		success = 1;
	while (p->next != NULL)
	{
		if (strcmp(p->name, name) == 0
			&& strcmp(p->pwd, pwd) == 0)
			success = 1;
		p = p->next;
	}
	if (strcmp(p->name, name) == 0
		&& strcmp(p->pwd, pwd) == 0)
		success = 1;
	if (success)
	{
		printf("��ϲ����¼�ɹ����û��� %s \r\n", name);
		strcpy(curuser.name, name);
		strcpy(curuser.pwd, pwd);
		return;
	}
	else
		printf("��¼ʧ�ܣ������û��������룡\r\n");
}

void createsampleagendas()
{
	FILE *fp = fopen(agendafile, "wb");
	char *fmt = "%d\t%s\t%s\t%s\t%s\t%s\r\n";
	printf("����ʾ���ճ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, fmt, 1, "Meet Bbama", "2015-01-01", "2015-03-03", "2015-01-04", "Jim");
	fprintf(fp, fmt, 2, "Meet XiJinping", "2015-06-26", "2015-08-28", "2015-06-29", "Kathy");
	fprintf(fp, fmt, 3, "Quit EU", "2015-06-26", "2016-08-28", "2016-06-30", "Jim");
	fprintf(fp, fmt, 4, "test event", "2016-06-27", "2016-08-27", "2016-06-28", "Kathy");
	fclose(fp);
	printf("ʾ���ճ������ѱ��浽Agenda.txt��");
}

void createsampleusers()
{
	FILE *fp = fopen(userfile, "wb");
	char *fmt = "%s\t%s\r\n";
	printf("����ʾ���û�...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, fmt, "Jim", "123456");
	fprintf(fp, fmt, "Kathy", "QWERT");
	fprintf(fp, fmt, "user2", "pwd2");
	fprintf(fp, fmt, "leiyang", "password");
	fclose(fp);
	printf("ʾ���û��ѱ��浽user.txt��");
}

int main()
{
	int choice = -1;

	time_t curdate = getcurdate();
	//���ں��������˲���Ԥ�������ļ�Ҫ��
	//���������ļ������¶��룬�����ͷ֪��������󣬾Ͳ������¶���
	//������С�ļ���˵���ܺ��Բ���
	createsampleagendas();
	createsampleusers();

	readallusers();
	readallagendas();

	strcpy(curuser.name, "user1");
	strcpy(curuser.pwd, "pwd");

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t------------------------------");
		printf("\n\n\t 0. �˳� 0");
		printf("\n\n\t 1. ע�����û� 1");
		printf("\n\t 2. ��¼ 2");
		printf("\n\t 3. �½��ճ� 3");
		printf("\n\t 4. �鿴��ʷ�ճ� 4");
		printf("\n\t 5. �鿴δ���ճ� 5");
		printf("\n\t 6. ɾ���ճ� 6");
		printf("\n\n ��ѡ��: ");
		scanf("%1[0123456]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			adduser();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			login();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			addagenda();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			viewagenda(curuser.name, curdate, 1);
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			viewagenda(curuser.name, curdate, 0);
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			deleteagenda(curuser.name, 0);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}

	system("pause");
	return 0;
}

