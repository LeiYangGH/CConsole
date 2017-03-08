#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TRAIN_COUNT 10
#define MAX_CARRIAGE_COUNT 20
#define MAX_SEAT_COUNT 130

int order[MAX_TRAIN_COUNT][MAX_CARRIAGE_COUNT][MAX_SEAT_COUNT];
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
	inputnum(&seatcount, MAX_SEAT_COUNT, "ÿ�������λ��");
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


void cancel(int trainid, int carriageid, int seatid)
{
	if (order[trainid][carriageid][seatid] == 1)
	{
		order[trainid][carriageid][seatid] = 0;
		printf("��Ʊ�ɹ���");
	}
	else
		printf("��Ʊδ������������Ʊ��");
}

void promptcancel()
{
	int i, j, k;
	if (!initdone)
	{
		printf("���ȳ�ʼ����ִ����������\n");
		return;
	}
	inputnum(&i, traincount, "Ҫ��Ʊ�ĳ���");
	inputnum(&j, carriagecount, "Ҫ��Ʊ�ĳ���");
	inputnum(&k, seatcount, "Ҫ��Ʊ����λ");
	cancel(i - 1, j - 1, k - 1);
}

int main()
{
	int choice = -1;
#if TEST
	init();
	//showavailable(0);
	//showavailable(1);
	buy(0, 0, 1);
	//buy(0, 0, 1);
	//showavailable(0);
	//buy(0, 1, 1);
	showavailable(0);
	cancel(0, 0, 1);
	showavailable(0);

	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �𳵶�Ʊϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ʼ��");
		printf("\n\t 2. ��ѯ");
		printf("\n\t 3. ��Ʊ");
		printf("\n\t 4. ��Ʊ");
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
			promptcancel();
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

