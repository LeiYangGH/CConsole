#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define FILE_COM "compensation.txt"
#define LINE  "------------------------\n" 
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
#define T 0
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

int getdatestringpart(char* str, int from, int to)
{
	int i;
	char  x[5];
	for (i = from; i <= to; i++)
		x[i - from] = str[i];
	x[to - from + 1] = 0;
	return toint(x);
}

int  validatedate(char* str)
{

	int d, m, y;
	int daysinmonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int legit = 0;
	if (strlen(str) != 8)
		return 0;
	y = getdatestringpart(str, 0, 3);
	m = getdatestringpart(str, 4, 5);
	d = getdatestringpart(str, 6, 7);
	//printf("%d\t%d\t%d\n", y, m, d);
	if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
		daysinmonth[1] = 29;
	if (m < 13)
	{
		if (d <= daysinmonth[m - 1])
			legit = 1;
	}
	return legit == 1;
}



void displaycompensation(compensation com)
{
	printf("%s\t%s\t%s\t%s\t%d\t%s\n",
		com.no, com.station, com.chassis, com.auditor, com.money, com.date);
}


void createhead()
{
	char line[200];
	compensation *p1, *p2;
	p1 = p2 = (compensation *)malloc(sizeof(compensation));
	head = p1;
	p2->next = NULL;
}

void checkandreinputdate(char expected[20], char str[20])
{
	while (!validatedate(str))
	{
		printf("������Ϸ�����(8λ���֣�����20170614�����㲹0):");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", str);
	}
	strcpy(expected, str);
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
	while (p->next != NULL)
	{
		p = p->next;
	}
	*tail = p;
}

void writeallcompensations()
{
	int i;
	compensation stu;
	compensation *p = head->next;
	FILE *fp = fopen(FILE_COM, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_COM);
		getchar();
		exit(1);
	}


	//�����š�����վ���ơ����̺š�����ˡ��������������
	while (p != NULL)
	{
		fprintf(fp, "%s %s %s %s %d %s\n",
			p->no, p->station, p->chassis, p->auditor, p->money, p->date);
		p = p->next;
	}

	fclose(fp);
}

void addcompensation(char no[20], char station[20], char chassis[20], char auditor[20], int money, char date[20])
{
	compensation *p = head;
	compensation *n;

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
	writeallcompensations();
}

void findcompensationbyno(char no[20], compensation **found)
{
	compensation *p = head;
	while (p != NULL)
	{
		if (streq(p->no, no))
		{
			*found = p;
			return;
		}
		p = p->next;
	}
}

int isnoexists(char no[20])
{
	compensation *found = NULL;
	findcompensationbyno(no, &found);
	return !(found == NULL);
}

void getcompensationfromline(char *line, compensation *com)
{
	char *part;
	int index = 0;
	//compensation com;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(com->no, part);
			break;
		case 2:
			strcpy(com->station, part);
			break;
		case 3:
			strcpy(com->chassis, part);
			break;
		case 4:
			strcpy(com->auditor, part);
			break;
		case 5:
			com->money = toint(part);
			break;
		case 6:
			strcpy(com->date, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
}

void readallcompensations()
{
	char line[200];
	FILE *fp = fopen(FILE_COM, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_COM);
	}
	else
	{

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;

			//allcompensations[allcompensationscount++] = getcompensationfromline(line);
			compensation *n = (compensation *)malloc(sizeof(compensation));
			getcompensationfromline(line, n);
			addcompensation(n->no, n->station, n->chassis, n->auditor,
				n->money, n->date);
		}
		printf("\n�Ѷ����ļ�!", FILE_COM);
	}
}


void promptaddcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	char expecteddate[20];
	printf("\n��������:");
	scanf("%s", no);
	if (isnoexists(no))
	{
		printf("���%s�Ѿ����ڣ������ظ�������Ʒ!", no);
		return;
	}
	//�����š�����վ���ơ����̺š�����ˡ��������������

	printf("\n���������վ���ơ����̺š�����ˣ����ǲ����ո���ַ��������ո����\n");
	scanf("%s%s%s", station, chassis, auditor);
	printf("\n��������������������������ڣ���ʽ20170614�����ո����\n");
	scanf("%d%s", &money, date);
	checkandreinputdate(expecteddate, date);
	addcompensation(no, station, chassis, auditor, money, date);
	printf("���¼��!\r\n");
}


void editcompensation(compensation *n, char station[20], char chassis[20], char auditor[20], int money, char date[20])
{
	strcpy(n->auditor, auditor);
	strcpy(n->station, station);
	strcpy(n->chassis, chassis);
	n->money = money;
	strcpy(n->date, date);
	writeallcompensations();
}

void prompteditcompensation()
{
	char no[20];
	char station[20];
	char chassis[20];
	char auditor[20];
	int money;
	char date[20];
	char expecteddate[20];
	compensation *found = NULL;
	printf("\n��������:");
	scanf("%s", no);
	findcompensationbyno(no, &found);
	if (found == NULL)
	{
		printf("���%s������!", no);
		return;
	}
	printf("\n���������վ���ơ����̺š�����ˣ����ǲ����ո���ַ��������ո����\n");
	scanf("%s%s%s", station, chassis, auditor);
	printf("\n��������������������������ڣ���ʽ20170614�����ո����\n");
	scanf("%d%s", &money, date);
	checkandreinputdate(expecteddate, date);
	editcompensation(found, station, chassis, auditor, money, date);
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
			writeallcompensations();
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

void calcstationtotal(char station[20])
{
	compensation *p = head->next;
	int total = 0, found = 0;
	//�����š�����վ���ơ����̺š�����ˡ��������������
	while (p != NULL)
	{
		if (streq(p->station, station))
		{
			found = 1;
			total += p->money;
		}
		p = p->next;
	}
	if (found == 1)
		printf("����վ%s��������Ϊ%dԪ��\n", station, total);
	else
		printf("û�ҵ�����վ%s��������Ϣ��\n", station);
}

void promptcalcstationtotal()
{
	char station[20] = "";
	inputstring(station, "Ҫ��ѯ��������ķ���վ����");
	calcstationtotal(station);
}

void getauditbycount(char auditor[20])
{
	compensation *p = head->next;
	int total = 0, found = 0;
	//�����š�����վ���ơ����̺š�����ˡ��������������
	while (p != NULL)
	{
		if (streq(p->auditor, auditor))
		{
			found = 1;
			total++;
		}
		p = p->next;
	}
	if (found == 1)
		printf("�����%s��˵��������Ϊ%d��\n", auditor, total);
	else
		printf("û�ҵ������%s��������Ϣ��\n", auditor);
}

void promptgetauditbycount()
{
	char auditor[20] = "";
	inputstring(auditor, "Ҫ��ѯ������������������˵�����");
	getauditbycount(auditor);
}

void displaychassiscompensations(char chassis[20])
{
	compensation *p = head->next;

	printf("���̱��Ϊ%��������������ʷ����\n", chassis);
	printf(LINE);
	//�����š�����վ���ơ����̺š�����ˡ��������������
	printf("���%t����վ%t����%t�����%t���%t����\n");
	while (p != NULL)
	{
		if (streq(p->chassis, chassis))
		{
			displaycompensation(*p);
		}
		p = p->next;
	}
	printf(LINE);
}
void promptdisplaychassiscompensations()
{
	char chassis[20] = "";
	inputstring(chassis, "Ҫ��ѯ������ʷ���������̱��");
	displaychassiscompensations(chassis);
}
int main()
{
	int choice = -1;
	compensation *found;

	createhead();
	readallcompensations();
#if T
	//addcompensation("01", "s1", "c1", "a1", 1, "d1");
	//addcompensation("02", "s2", "c2", "a2", 2, "d2");
	//addcompensation("03", "s3", "c3", "a3", 3, "d3");
	displayallcompensations();
	//calcstationtotal("s3");
	getauditbycount("a1");
	//int i = validatedate("2017x106");
	//printf("i=%d\n", i);

	//promptdeletebyno();
	//promptaddcompensation();
	//displayallcompensations();

	//findcompensationbyno("03", &found);
	//editcompensation(found, "s-", "c-", "a-", 99, "d-");
	//prompteditcompensation();
	//displayallcompensations();
	//writeallcompensations();

#else
	while (choice != 0)
	{
		printf("\n\t ����¼����");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �鿴����������Ϣ");
		printf("\n\t 2. ����������Ϣ");
		printf("\n\t 3. �޸�������Ϣ");
		printf("\n\t 4. ɾ��������Ϣ");
		printf("\n\t 5. �����������̱�Ų�ѯ������ʷ");
		printf("\n\t 6. ��ѯ����վ��������");
		printf("\n\t 7. ��ѯ�����������������");
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
			displayallcompensations();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaddcompensation();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			prompteditcompensation();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptdeletebyno();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptdisplaychassiscompensations();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			promptcalcstationtotal();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			promptgetauditbycount();
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