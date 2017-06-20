//ͼ����Ϣ����ϵͳ
//ͼ����Ϣ������ͼ���š������������������浥λ������ʱ�䡢�۸�ȡ������һͼ����Ϣ����ϵͳ��ʹ֮���ṩ���¹��ܣ�
//1.ͼ����Ϣ¼�루ͼ����Ϣ���ļ����棬�����ڵ�����ֱ�Ӳ��Ҳ��򿪸��ļ���
//2.ͼ����Ϣ���
//3.������������
//4.��ѯ
//a.�����浥λ��ѯ
//b.��������ѯ
//5.ͼ����Ϣ��ɾ��
//5.ͼ����Ϣ���޸�
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_BOOK "book.txt"
#define MAX_STRLEN 20
typedef struct book
{
	char id[20];
	char name[20];
	char author[10];
	char publisher[30];
	char publishdate[50];
	int price;
}book;

book allbooks[100];
int allbookscount = 0;

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


void displaybook(book b)
{
	printf("%s\t%8s%10s%16s%10s\t%d\n",
		b.id, b.name, b.author, b.publisher, b.publishdate, b.price);
}

int cmpfunc(const void * a, const void * b)
{
	return ((book*)a)->author - ((book*)b)->author;
}

void displayallbooks()
{
	int i;
	qsort(allbooks, allbookscount, sizeof(book), cmpfunc);
	printf("����%d��ͼ����Ϣ����\r\n", allbookscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allbookscount; i++)
	{
		displaybook(allbooks[i]);
	}
	printf("--------------------------------------------\r\n");
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��book
book getbookfromline(char *line)
{
	char *part;
	int index = 0;
	book b;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(b.id, part);
			break;
		case 2:
			strcpy(b.name, part);
			break;
		case 3:
			strcpy(b.author, part);
			break;
		case 4:
			strcpy(b.publisher, part);
			break;
		case 5:
			strcpy(b.publishdate, part);
			break;
		case 6:
			b.price = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return b;
}

void readallbooks()
{
	char line[200];
	FILE *fp = fopen(FILE_BOOK, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_BOOK);
	}
	else
	{
		allbookscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allbooks[allbookscount++] = getbookfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_BOOK);
	}
}


int getbookidexbyno(char id[50])
{
	int i;
	for (i = 0; i < allbookscount; i++)
	{
		if (streq(allbooks[i].id, id))
			return i;
	}
	return -1;//û�ҵ�
}

void writeallbooks()
{
	int i;
	book b;
	FILE *fp = fopen(FILE_BOOK, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_BOOK);
		getchar();
		exit(1);
	}
	for (i = 0; i < allbookscount; i++)
	{
		b = allbooks[i];
		fprintf(fp, "%s %s %s %s %s %d\n",
			b.id, b.name, b.author, b.publisher, b.publishdate, b.price);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void editbook(char id[50])
{
	int i;
	i = getbookidexbyno(id);
	if (i >= 0)
	{
		printf("\n�������µĳ��浥λ������ʱ�䡢�۸񣬿ո����\n");
		scanf("%s%s%d", allbooks[i].publisher, allbooks[i].publishdate, &allbooks[i].price);
		writeallbooks();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧͼ���źŵ�ͼ�顣\r\n");
	}
}

void prompteditbook()
{
	char id[50];
	printf("������Ҫ�޸ĵ�ͼ���ź�:");
	scanf("%s", &id);
	editbook(id);
}

void addbook(char id[], char name[], char author[], char publisher[], char publishdate[], int price)
{
	book b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	strcpy(b.author, author);
	strcpy(b.publisher, publisher);
	strcpy(b.publishdate, publishdate);
	b.price = price;
	allbooks[allbookscount++] = b;
	writeallbooks();
}


void promptaddbook()
{
	char id[20];
	char name[20];
	char author[10];
	int price;
	char publisher[30];
	char publishdate[50];
	char telephone[20];
	printf("\n������ͼ���ţ����ظ���:\n");
	scanf("%s", id);
	if (getbookidexbyno(id) >= 0)
	{
		printf("ͼ����������ͼ���ظ���\n");
		return;
	}
	printf("\n�����������������������浥λ������ʱ�䣨���ǲ����ո���ַ��������۸�(����)���ո����\n");
	scanf("%s%s%s%s%d", name, author, publisher, publishdate, &price);
	addbook(id, name, author, publisher, publishdate, price);
	printf("��ɵ�%d��ͼ��¼��!\r\n", allbookscount);
}


void removebook(char no[20])
{
	int i;
	int index;
	index = getbookidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allbookscount - 1; i++)
			allbooks[i] = allbooks[i + 1];
		allbookscount--;
		writeallbooks();
		printf("ɾ����ϣ�ʣ��%d����\r\n", allbookscount);
	}
	else
	{
		printf("û�ҵ���Ӧͼ���źŵ�ͼ�顣\r\n");
	}

}

void promptremovebook()
{
	char id[20];
	printf("������Ҫɾ����ͼ���ź�:");
	scanf("%s", id);
	removebook(id);
}


void searchbyname(char name[20])
{
	int i, found = 0;
	for (i = 0; i < allbookscount; i++)
		if (strstr(allbooks[i].name, name) != NULL)
		{
			displaybook(allbooks[i]);
			found = 1;
		}
	if (!found)
		printf("û�ҵ���Ӧͼ�����Ϣ��\r\n");
}

void promptsearchbyname()
{
	char name[20];
	printf("������Ҫ���ҵ�����:");
	scanf("%s", name);
	searchbyname(name);
}

void searchbypublisher(char publisher[20])
{
	int i, found = 0;
	for (i = 0; i < allbookscount; i++)
		if (strstr(allbooks[i].publisher, publisher) != NULL)
		{
			displaybook(allbooks[i]);
			found = 1;
		}
	if (!found)
		printf("û�ҵ���Ӧͼ�����Ϣ��\r\n");
}

void promptsearchbypublisher()
{
	char publisher[20];
	printf("������Ҫ���ҵĳ�����:");
	scanf("%s", publisher);
	searchbypublisher(publisher);
}

int main()
{
	char choice = -1;
#if 0//�����ã�if���ɾ��
	readallbooks();
	//addbook("01", "��������", "�޹���", "���������", "1950-4-3", 99);
	//addbook("02", "C����", "̷��ǿ", "��е������", "1995-12-1", 50);

	//editbook("01");
	////printf("\n%d\n", allbookscount);
	displayallbooks();
	//promptsearchbypublisher();
	promptsearchbyname();
	//prompteditbook();
	//promptremovebook();
	//promptaddbook();
	//promptsearchbyname();
	//writeallbooks();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//sortbooksbytotalanddisplay();
	//displayallbooks();
	//sortbooksbytotal();
	//prompteditbook();
	////displayallbooks();


	system("pause");

#endif
	readallbooks();
	while (choice != 0)
	{
		printf("\n\t ͼ����Ϣ����ϵͳ");
		printf("\n\t 0---�˳�");
		printf("\n\t 1---ͼ����Ϣ¼��");
		printf("\n\t 2---ͼ����Ϣ���");
		printf("\n\t 3---�����浥λ��ѯ");
		printf("\n\t 4---��������ѯ");
		printf("\n\t 5---ͼ����Ϣɾ��");
		printf("\n\t 6---ͼ����Ϣ�޸�");
		printf("\n��ѡ��:");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0); break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			promptaddbook();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallbooks();
			break;
		case '3':
			printf("\n\n��ѡ���� c\n");
			promptsearchbypublisher();
			break;
		case '4':
			printf("\n\n��ѡ���� d\n");
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n��ѡ���� e\n");
			promptremovebook();
			break;
		case '6':
			printf("\n\n��ѡ���� f\n");
			prompteditbook();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

