// ConsoleApplication19.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"//comment in vc6
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include "windows.h"
#define MAX_CELL_TEXT_LENTH 20
#define ORDER_FORMAT_STRING "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\r\n"
//#define LYDEV 1


typedef struct order
{
	char no[7];//������
	char name[MAX_CELL_TEXT_LENTH];//�ͻ���
	char contact[MAX_CELL_TEXT_LENTH];//��ϵ��ʽ�����δȷ������
	char totalpersons[MAX_CELL_TEXT_LENTH];//�ò�����
	char eatdate[MAX_CELL_TEXT_LENTH];//�ò�ʱ��
	char eatroom[MAX_CELL_TEXT_LENTH];//����������
	char eatmeal[MAX_CELL_TEXT_LENTH];//����Ĳ�
	char orderdate[15];//��������
	char canceldate[15];//ȡ�����ڣ����δȡ������
	char cancelreason[MAX_CELL_TEXT_LENTH];//ȡ��ԭ�����δȡ������
	char comments[MAX_CELL_TEXT_LENTH];//�ͻ�����
}order;

char currentname[MAX_CELL_TEXT_LENTH] = "";//��ǰ��¼�Ŀͻ���
order orders[50]; //ȫ�ִ洢���ж���
int orderscount;

char *orderfile = "Order.txt";
char *userfile = "user.txt";
order *head;


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

//��һ���ı���ֳ����� 
order getorderfromline(char *line)
{
	order od;
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(od.no, part);
			break;
		case 2:
			strcpy(od.name, part);
			break;
		case 3:
			strcpy(od.contact, part);
			break;
		case 4:
			strcpy(od.totalpersons, part);
			break;
		case 5:
			strcpy(od.eatdate, part);
			break;
		case 6:
			strcpy(od.eatroom, part);
			break;
		case 7:
			strcpy(od.eatmeal, part);
			break;
		case 8:
			strcpy(od.orderdate, part);
			break;
		case 9:
			strcpy(od.canceldate, part);
			break;
		case 10:
			strcpy(od.cancelreason, part);
			break;
		case 11:
			strcpy(od.comments, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return od;
}

void displaytitle(char *title)
{
	printf("\r\n-------------%s-------------\r\n", title);
}

//��ʾһ������ 
void displayorder(order od)
{
	printf(ORDER_FORMAT_STRING, od.no, od.name, od.contact, od.totalpersons, od.eatdate, od.eatroom, od.eatmeal, od.orderdate, od.canceldate, od.cancelreason, od.comments);
	printf("\r\n");
}

//��ʾ���к���˿���Ϣ 
void displayallorders()
{
	int i;
	displaytitle("���ж�����Ϣ");

	for (i = 0; i < orderscount; i++)
	{
		displayorder(orders[i]);
	}
}

//��ȡ���ж���������
void readallorders()
{
	char line[200];
	FILE *fp = fopen(orderfile, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�ʧ��!");
		getchar();
		exit(1);
	}
	orderscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;//
		++orderscount;
		orders[orderscount - 1] = getorderfromline(line);
	}
}


//�������ж���
void writeallorders()
{
	FILE *fp = fopen(orderfile, "wb");
	if (fp == NULL)
	{
		printf("\n���ļ�ʧ��!");
		getchar();
		exit(1);
	}

	int i;
	order od;
	for (i = 0; i < orderscount; i++)
	{
		od = orders[i];
		fprintf(fp, ORDER_FORMAT_STRING,
			od.no, od.name, od.contact, od.totalpersons, od.eatdate, od.eatroom, od.eatmeal, od.orderdate, od.canceldate, od.cancelreason, od.comments);
	}
	fclose(fp);
	printf("�ѱ��浽�ļ���");
}


//���붩����Ϣ
void inputstring(char str[], int maxlenth, char* purpose)
{
	int len = -1;
	char input[MAX_CELL_TEXT_LENTH] = "";
	while (len<1 || len > maxlenth)
	{
		printf("������%s��%d���ַ����ڣ����ܴ��ո�Tab��س���:", purpose, maxlenth);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("���� %s Ϊ %s \r\n\r\n", purpose, str);
}


//������ʼ/���������� 
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

int getorderscountat(char *datestring)
{
	int i;
	int cnt = 0;
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].orderdate, datestring) == 0)
			cnt++;
	}
	return cnt;
}

void formatorderno(time_t dt, int existingcount, char *str)
{
	struct tm *ptr;
	char cntstr[3];
	ptr = localtime(&dt);
	strftime(str, 20, "%m%d", ptr);
	sprintf(cntstr, "%d", existingcount + 1);
	strcat(str, cntstr);
}

//��������
void addorder()
{
	order od;
	char nostr[7];
	char todaystring[20];
	time_t today = getcurdate();
	formatdate(today, todaystring);
	formatorderno(getcurdate(), getorderscountat(todaystring) + 1, nostr);

	strcpy(od.no, nostr);
	inputstring(od.name, MAX_CELL_TEXT_LENTH, "�ͻ���");
	strcpy(od.contact, " ");
	inputstring(od.totalpersons, MAX_CELL_TEXT_LENTH, "�ò�����");
	inputstring(od.eatdate, MAX_CELL_TEXT_LENTH, "�ò�ʱ��");
	inputstring(od.eatroom, MAX_CELL_TEXT_LENTH, "����������");
	inputstring(od.eatmeal, MAX_CELL_TEXT_LENTH, "����Ĳ�");
	strcpy(od.orderdate, "2016-08-30");
	strcpy(od.canceldate, " ");
	strcpy(od.cancelreason, " ");
	strcpy(od.comments, " ");

	orders[orderscount++] = od;
	writeallorders();
}

void login()
{
	inputstring(currentname, LOCALE_NAME_MAX_LENGTH, "��¼�ͻ���");
	if (strlen(currentname) > 1)
	{
		printf("��ϲ���¼�ɹ���");
	}
}


//��ǰ��¼�ͻ��Ƿ����ض������ͻ���һ��
int isorderofcurrentname(order* od)
{
	return strcmp(od->name, currentname) == 0;
}

int isordercancelled(order* od)
{
	return strlen(od->canceldate) > 2;
}

//�Ϸ�����1������0
int checknameorcancelbeforechange(order* od)
{
	if (isordercancelled(od))
	{
		printf("�˶����Ѿ�ȡ���������ٸ��ģ�");
		return 0;
	}
	else if (!isorderofcurrentname(od))
	{
		printf("��ǰ��¼�ͻ���Ϊ%s�����ܲ鿴���˵Ķ�����", currentname);
		return 0;
	}
	return 1;
}


//ȷ�϶���
void confirmorder(order* od)
{
	char contactstr[MAX_CELL_TEXT_LENTH];
	if (checknameorcancelbeforechange(od))
	{
		inputstring(contactstr, MAX_CELL_TEXT_LENTH, "ȷ�϶��͵���ϵ��ʽ(����11λ)");
		if (strlen(contactstr) < 11)
			printf("�������ϵ��ʽ̫�̣�ȷ��ʧ�ܣ�");
		else
		{
			strcpy(od->contact, contactstr);
			writeallorders();
			printf("\r\nȷ�ϳɹ���");
		}
	}
}

//ȡ������
void cancelorder(order* od)
{
	char reasonstr[MAX_CELL_TEXT_LENTH];
	char todaystring[20];

	if (checknameorcancelbeforechange(od))
	{
		inputstring(reasonstr, MAX_CELL_TEXT_LENTH, "ȡ��ԭ��");
		if (strlen(reasonstr) < 2)
			printf("�����ȡ��ԭ��̫�̣�ȡ��ʧ�ܣ�");
		else
		{
			time_t today = getcurdate();
			formatdate(today, todaystring);
			strcpy(od->canceldate, todaystring);
			strcpy(od->cancelreason, reasonstr);
			writeallorders();
			printf("\r\nȡ���ɹ���");
		}
	}
}

//�������
void commentorder(order* od)
{
	char commentstr[MAX_CELL_TEXT_LENTH];

	if (checknameorcancelbeforechange(od))
	{
		inputstring(commentstr, MAX_CELL_TEXT_LENTH, "����");
		if (strlen(commentstr) < 2)
			printf("���������̫�̣�����ʧ�ܣ�");
		else
		{
			strcpy(od->comments, commentstr);
			writeallorders();
			printf("\r\n���۳ɹ���");
		}
	}
}

//���ض����б��±꣬���û�ҵ�����-1
int inputorderno()
{
	int i;
	int found = -1;
	char ordernostr[7];

	inputstring(ordernostr, 6, "������");
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].no, ordernostr) == 0)
		{
			found = i;
			break;
		}
	}
	if (found == -1)
	{
		printf("δ�ҵ��˶�����");
	}
	return found;
}

//�������
void viewaorder(char* orderno)
{
	int i;
	int found = 0;
	for (i = 0; i < orderscount; i++)
	{
		if (strcmp(orders[i].no, orderno) == 0)
		{
			if (isordercancelled(&orders[i]))
			{
				printf("�˶����Ѿ�ȡ�����ͻ����ܲ�ѯ��");
			}
			else
			{
				displaytitle("���ҵ��Ķ�����Ϣ");
				displayorder(orders[i]);
				found = 1;
			}
			break;
		}
	}
	if (found == 0)
	{
		printf("δ�ҵ��˶�����");
	}
}


void createsampleorders()
{
	FILE *fp = fopen(orderfile, "wb");
	printf("����ʾ����������...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, ORDER_FORMAT_STRING, "083001", "Obama", " ", "4��", "2017-09-01���ò�", "�ż�1"
		, "����ȫϯ", "2016-08-30", " ", " ", "�������´λ�����");
	fprintf(fp, ORDER_FORMAT_STRING, "090102", "ϰ��ƽ", "010-88888888", "1��", "2017-09-05���ò�", "����������"
		, "�Ĳ�һ��", "2016-08-30", " ", " ", "������û���ӣ�");
	fclose(fp);
	printf("ʾ�����������ѱ��浽Order.txt��");
}

int main()
{
#ifdef LYDEV
	//createsampleorders();
	readallorders();
	displayallorders();

	//addorder();
	//writeallorders();

	//confirmorder(&orders[0]);
	//cancelorder(&orders[1]);
	viewaorder("090102");//090102 //083001
#else
	int choice = -1;
	int orderindex = -1;

	time_t curdate = getcurdate();

	/*createsampleorders();
	createsampleusers();

	readallusers();*/
	readallorders();
	displayallorders();
	/*strcpy(curuser.name, "user1");
	strcpy(curuser.pwd, "pwd");*/

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t------------------------------");
		printf("\n\t 0. �˳� 0");
		printf("\n\t 1. �ͻ���¼ 1");
		printf("\n\t 2. ���κ��ˣ����� 2");
		printf("\n\t 3. (��¼�ͻ�)ȷ�϶��� 3");
		printf("\n\t 4. (��¼�ͻ�)ɾ������ 4");
		printf("\n\t 5. (��¼�ͻ�)�ͻ����� 5");
		printf("\n\t 6. ���Ƶ�ͳ�ƣ���ѯ���� 6");
		printf("\r\n");
		scanf("%1[0123456]d%*c", &choice);
		choice = getche();
		orderindex = -1;
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			login();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			addorder();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				confirmorder(&orders[orderindex]);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				cancelorder(&orders[orderindex]);
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			orderindex = inputorderno();
			if (orderindex > 0)
				commentorder(&orders[orderindex]);
			break;
		case
			'6':
			printf("\n\n��ѡ���� 6\n");
			displayallorders();
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
#endif
	system("pause");
	return 0;
}

