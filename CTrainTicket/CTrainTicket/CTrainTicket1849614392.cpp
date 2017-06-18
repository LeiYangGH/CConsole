#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TRAIN_COUNT 10
#define MAX_CARRIAGE_COUNT 20
#define SEAT_COUNT 45

typedef struct shift
{
	char id[20];
	int hour;
	int minute;
	char start[20];
	char end[20];
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

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


void displayshift(shift s)
{
	printf("%s\t%02d:%02d\t%s\t%s\t%d\t%d\n",
		s.id, s.hour, s.minute, s.start, s.end, 45, s.leftseats);
}

void displayallshifts()
{
	int i;
	printf("����%dλ�����Ϣ����\r\n", allshiftscount);
	printf("���\tʱ��\t���\t�յ�\t��λ\t��Ʊ\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allshiftscount; i++)
	{
		displayshift(allshifts[i]);
	}
	printf("--------------------------------------------\r\n");
}



//qsort�ǿ�������Ҫ������д��������age����
int cmpfunc(const void * a, const void * b)
{
	int ha = ((shift*)a)->hour;
	int ma = ((shift*)a)->minute;
	int hb = ((shift*)b)->hour;
	int mb = ((shift*)b)->minute;
	return (ha - hb) * 60 + ma - mb;
}

void sortshiftsbyageanddisplay()
{
	int i;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("��ÿ������������������\r\n");
	displayallshifts();
}

//���ݱ�Ų�����������
int getshiftidexbyno(char id[50])
{
	int i;
	for (i = 0; i < allshiftscount; i++)
	{
		if (streq(allshifts[i].id, id))
			return i;
	}
	return -1;//û�ҵ�
}


void editshift(char id[50])
{
	int i;
	i = getshiftidexbyno(id);
	if (i >= 0)
	{
		printf("\n�������·���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
		scanf("%d%d", &allshifts[i].hour, &allshifts[i].minute);
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	}
}

void prompteditshift()
{
	char id[50];
	printf("������Ҫ�޸ĵİ��:");
	scanf("%s", &id);
	editshift(id);
}

void addshift(char id[], int hour, int minute)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, "����");
	strcpy(s.end, "����");
	s.leftseats = SEAT_COUNT;
	allshifts[allshiftscount++] = s;
}


void promptaddshift()
{
	char id[20];
	int hour;
	int minute;
	printf("\n�������Σ����ظ���:\n");
	scanf("%s", id);
	if (getshiftidexbyno(id) >= 0)
	{
		printf("��������а���ظ���\n");
		return;
	}
	printf("\n�������·���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
	scanf("%d%d", &hour, &minute);
	addshift(id, hour, minute);
	printf("��ɵ�%dλ���¼��!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allshiftscount - 1; i++)
			allshifts[i] = allshifts[i + 1];
		allshiftscount--;
		printf("ɾ����ϣ�ʣ��%d����\r\n", allshiftscount);
	}
	else
	{
		printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	}

}

void promptremoveshift()
{
	char id[20];
	printf("������Ҫɾ���İ��:");
	scanf("%s", id);
	removeshift(id);
}


void searcbetweenage(int from, int to)
{
	//int i, found = 0;
	//for (i = 0; i < allshiftscount; i++)
	//	if (allshifts[i].age >= from && allshifts[i].age <= to)
	//	{
	//		displayshift(allshifts[i]);
	//		found = 1;
	//	}
	//if (!found)
	//	printf("û�ҵ���Ӧ��ε���Ϣ��\r\n");
}

void promptsearchbetweenage()
{
	int from, to;
	printf("������Ҫ���ҵ���ͺ��������(���������ո�ָ�):");
	scanf("%d%d", &from, &to);
	searcbetweenage(from, to);
}

int order[MAX_TRAIN_COUNT][MAX_CARRIAGE_COUNT][SEAT_COUNT];
int traincount = 0;
int carriagecount = 0;
int seatcount = 0;
int initdone = 0;
#define TEST 0

void inputnum(int *num, int max, char *description)
{
	int input = 0;
	do
	{
		printf("\n������%s,(��Χ1~%d):", description, max);
		scanf("%d", &input);
		fseek(stdin, 0, SEEK_END);
	} while (input<1 || input>max);
	*num = input;
}

void init()
{
	int i, j, k;
#if TEST
	traincount = 2;
	carriagecount = 2;
	seatcount = 2;
#else
	if (initdone)
	{
		printf("�Ѿ���ʼ�����������ٳ�ʼ��\n");
		return;
	}
	inputnum(&traincount, MAX_TRAIN_COUNT, "������");
	inputnum(&carriagecount, MAX_CARRIAGE_COUNT, "ÿ���εĳ�����");
	inputnum(&seatcount, SEAT_COUNT, "ÿ�������λ��");
	for (i = 0; i < traincount; i++)
		for (j = 0; j < carriagecount; j++)
			for (k = 0; k < seatcount; k++)
				order[i][j][k] = 0;
	initdone = 1;

#endif
}

void showavailableseats(int trainid, int carriageid)
{
	int train, i, j, k;
	printf("��%d���� ��%d����ʣ����λ������:\n", trainid + 1, carriageid + 1);
	printf("--------------------------------------------\n");
	for (k = 0; k < seatcount; k++)
	{
		if (order[trainid][carriageid][k] == 0)
		{
			printf("%d\t", k + 1);
		}
	}
	printf("\n--------------------------------------------\n");
}



void showavailable(int trainid)
{
	int j;
	for (j = 0; j < carriagecount; j++)
		showavailableseats(trainid, j);
}

void promptshowavailable()
{
	int i;
	if (!initdone)
	{
		printf("���ȳ�ʼ����ִ����������\n");
		return;
	}
	inputnum(&i, carriagecount, "Ҫ��ѯ��Ʊ�ĳ���");
	showavailable(i - 1);
}

void buy(int trainid, int carriageid, int seatid)
{
	if (order[trainid][carriageid][seatid] == 0)
	{
		order[trainid][carriageid][seatid] = 1;
		printf("��Ʊ�ɹ�����%d���� ��%d���� ��%d����λ��\n", trainid + 1, carriageid + 1, seatid + 1);
	}
	else
		printf("��Ʊ�Ѿ�������");
}

void promptbuy()
{
	int i, j, k;
	if (!initdone)
	{
		printf("���ȳ�ʼ����ִ����������\n");
		return;
	}
	inputnum(&i, traincount, "Ҫ����ĳ���");
	inputnum(&j, carriagecount, "Ҫ����ĳ���");
	inputnum(&k, seatcount, "Ҫ�������λ");
	buy(i - 1, j - 1, k - 1);
}



int main()
{
	int choice = -1;
#if 1
	promptaddshift();
	displayallshifts();

	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �𳵶�Ʊϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ʼ��");
		printf("\n\t 2. ��ѯ");
		printf("\n\t 3. ��Ʊ");
		//printf("\n\t 4. ��Ʊ");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			init();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptshowavailable();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptbuy();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			//promptcancel();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

