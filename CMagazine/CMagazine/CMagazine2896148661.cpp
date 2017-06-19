//��־���Ĺ�����־������Ϣ
//��־����  ���Ļ���  ���֤��  ���ķ���  ����  С��
//122          ��ƽ        4512245    2            5.5    11.0
//�������޸ġ�ɾ�������ܰ����֤�Ų��Ҷ��Ļ���������Լ�ͳ��ָ����־�Ķ��ķ�����
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_per "magazine.txt"
#define MAX_STRLEN 20
typedef struct magazine
{
	char id[20];
	char name[20];
	char card[20];
	int quantity;
	float price;
	float total;
}magazine;

magazine allmagazines[100];
int allmagazinescount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}


int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}
float tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void calctotal(magazine *m)
{
	m->total = m->price*m->quantity;
}

void displaymagazine(magazine m)
{
	printf("%s\t%s\t%s\t%d\t%.1f\t%.1f\n",
		m.id, m.name, m.card, m.quantity, m.price, m.total);
}



void displayallmagazines()
{
	int i;
	printf("����%dλ��־������Ϣ��Ϣ����\r\n", allmagazinescount);
	printf("%s\t%s\t%s\t%s\t%s\t%s\n",
		"����", "����", "���֤", "����", "����", "С��");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allmagazinescount; i++)
	{
		displaymagazine(allmagazines[i]);
	}
	printf("--------------------------------------------\r\n");
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��magazine
magazine getmagazinefromline(char *line)
{
	char *part;
	int index = 0;
	magazine m;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(m.id, part);
			break;
		case 2:
			strcpy(m.name, part);
			break;
		case 3:
			strcpy(m.card, part);
			break;
		case 4:
			m.quantity = toint(part);
			break;
		case 5:
			m.price = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	calctotal(&m);
	return m;
}

void readallmagazines()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
	}
	else
	{
		allmagazinescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allmagazines[allmagazinescount++] = getmagazinefromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_per);
	}
}





//���ݱ�Ų�����������
int getmagazineidexbycard(char card[50])
{
	int i;
	for (i = 0; i < allmagazinescount; i++)
	{
		if (streq(allmagazines[i].card, card))
			return i;
	}
	return -1;//û�ҵ�
}

void writeallmagazines()
{
	int i;
	magazine m;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allmagazinescount; i++)
	{
		m = allmagazines[i];
		fprintf(fp, "%s\t%s\t%s\t%d\t%.1f\n",
			m.id, m.name, m.card, m.quantity, m.price);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void editmagazine(char card[50])
{
	int i;
	i = getmagazineidexbycard(card);
	if (i >= 0)
	{
		printf("\n�������µĶ����������۸񣬿ո����:");
		scanf("%d%f", &allmagazines[i].quantity, &allmagazines[i].price);
		calctotal(&allmagazines[i]);
		writeallmagazines();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧ���֤�ŵ���־������Ϣ��\r\n");
	}
}

void prompteditmagazine()
{
	char card[50];
	printf("������Ҫ�޸ĵ����֤��:");
	scanf("%s", &card);
	editmagazine(card);
}


void addmagazine(char id[], char name[], char card[], int quantity, float price)
{
	magazine m;
	strcpy(m.id, id);
	strcpy(m.name, name);
	strcpy(m.card, card);
	m.quantity = quantity;
	m.price = price;
	calctotal(&m);
	allmagazines[allmagazinescount++] = m;
	writeallmagazines();
}


void promptaddmagazine()
{
	char id[20];
	char name[20];
	char card[20];
	int quantity;
	float price;

	printf("\n��������־����  ���Ļ���  ���֤�ţ����ǲ����ո���ַ����� ���ķ���  ���ۣ��ո����\n");
	scanf("%s%s%s%d%f", id, name, card, &quantity, &price);
	addmagazine(id, name, card, quantity, price);
	printf("��ɵ�%d����־������Ϣ¼��!\r\n", allmagazinescount);
}


void removemagazine(char no[20])
{
	int i;
	int index;
	index = getmagazineidexbycard(no);
	if (index >= 0)
	{
		for (i = index; i < allmagazinescount - 1; i++)
			allmagazines[i] = allmagazines[i + 1];
		allmagazinescount--;
		writeallmagazines();
		printf("ɾ����ϣ�ʣ��%d����\r\n", allmagazinescount);
	}
	else
	{
		printf("û�ҵ���Ӧ���֤�ŵ���־������Ϣ��\r\n");
	}

}

void promptremovemagazine()
{
	char id[20];
	printf("������Ҫɾ�������֤��:");
	scanf("%s", id);
	removemagazine(id);
}


void searchbycard(char card[20])
{
	int i, found = 0;
	for (i = 0; i < allmagazinescount; i++)
		if (streq(allmagazines[i].card, card))
		{
			displaymagazine(allmagazines[i]);
			found = 1;
		}
	if (!found)
		printf("û�ҵ���Ӧ��־������Ϣ����Ϣ��\r\n");
}

void promptsearchbycard()
{
	char card[20];
	printf("������Ҫ���ҵĶ����ߵ����֤��:");
	scanf("%s", card);
	searchbycard(card);
}

//
void gettotalquantitybyid(char id[20])
{
	int i, total = 0;
	for (i = 0; i < allmagazinescount; i++)
		if (streq(allmagazines[i].id, id))
		{
			total += allmagazines[i].quantity;
		}
	printf("���%s����־��������Ϊ:%d\n", id, total);
}

void promptgettotalquantitybyid()
{
	char id[20];
	printf("������Ҫ���ҵ���־�ı��:");
	scanf("%s", id);
	gettotalquantitybyid(id);
}

//

int main()
{
	char choice = -1;
#if 0//�����ã�if���ɾ��
	readallmagazines();
	//addmagazine("05", "n5", "20170605", 41, 92, 93);
	//addmagazine("06", "n6", "20170606", 46, 96, 96);

	//editmagazine("01");
	////printf("\n%d\n", allmagazinescount);
	displayallmagazines();
	promptgettotalquantitybyid();
	//promptaddmagazine();
	//prompteditmagazine();
	//promptremovemagazine();
	promptsearchbycard();
	//displayallmagazines();
	//promptsearchbetweenquantity();
	//writeallmagazines();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//sortmagazinesbytotalanddisplay();
	//displayallmagazines();
	//sortmagazinesbytotal();
	//prompteditmagazine();
	//displayallmagazines();


	system("pause");

#endif
	readallmagazines();
	while (choice != 0)
	{
		printf("\n\t ��־������Ϣ��Ϣ����ϵͳ");
		printf("\n\t 0---�˳�");
		printf("\n\t 1---��־������Ϣ���");
		printf("\n\t 2---��־������Ϣ�޸�");
		printf("\n\t 3---��־������Ϣɾ��");
		printf("\n\t 4---�鿴������־������Ϣ");
		printf("\n\t 5---�����֤��ѯ");
		printf("\n\t 6---����־���ͳ��");
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
			promptaddmagazine();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			prompteditmagazine();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptremovemagazine(); 
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallmagazines();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptsearchbycard();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			promptgettotalquantitybyid();
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

