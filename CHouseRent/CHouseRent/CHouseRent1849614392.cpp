#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

int cmpfunc(const void * a, const void * b)
{
	int ha = ((shift*)a)->hour;
	int ma = ((shift*)a)->minute;
	int hb = ((shift*)b)->hour;
	int mb = ((shift*)b)->minute;
	return (ha - hb) * 60 + ma - mb;
}

void displayallshifts()
{
	int i;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("����%dλ�����Ϣ����\r\n", allshiftscount);
	printf("���\tʱ��\t���\t�յ�\t��λ\t��Ʊ\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allshiftscount; i++)
	{
		displayshift(allshifts[i]);
	}
	printf("--------------------------------------------\r\n");
}

int getshiftidexbytime(int hour, int minute)
{
	int i;
	for (i = 0; i < allshiftscount; i++)
	{
		if (allshifts[i].hour == hour
			&& allshifts[i].minute == minute)
			return i;
	}
	return -1;
}

void checktimevalid(int hour, int minute, int *exphour, int *expminute)
{
	while (hour > 23 || hour < 0 || minute > 59 || hour < 0)
	{
		printf("������Ϸ�ʱ��(2������������14 5):");
		fseek(stdin, 0, SEEK_END);
		scanf("%d%d", &hour, &minute);
	}
	*exphour = hour;
	*expminute = minute;
}


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
	int hour;
	int minute;
	int exphour;
	int expminute;
	i = getshiftidexbyno(id);
	if (i >= 0)
	{
		if (allshifts[i].leftseats < SEAT_COUNT)
		{
			printf("�����г��Ѿ���Ʊ�۳����޷��޸�ʱ�䣡\n");
			return;
		}
		printf("\n�������·���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
		scanf("%d%d", &hour, &minute);
		checktimevalid(hour, minute, &exphour, &expminute);
		if (getshiftidexbytime(exphour, expminute) >= 0)
		{
			printf("ʱ�������а���ظ���\n");
			return;
		}
		allshifts[i].hour = exphour;
		allshifts[i].minute = expminute;
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
	printf("������Ҫ�޸�ʱ��İ��:");
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
	int exphour;
	int expminute;
	printf("\n�������Σ����ظ���:\n");
	scanf("%s", id);
	if (getshiftidexbyno(id) >= 0)
	{
		printf("��������а���ظ���\n");
		return;
	}
	printf("\n�������·���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
	scanf("%d%d", &hour, &minute);
	checktimevalid(hour, minute, &exphour, &expminute);
	if (getshiftidexbytime(exphour, expminute) >= 0)
	{
		printf("ʱ�������а���ظ���\n");
		return;
	}
	addshift(id, exphour, expminute);
	printf("��ɵ�%d���¼��!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		if (allshifts[index].leftseats < SEAT_COUNT)
		{
			printf("�����г��Ѿ���Ʊ�۳����޷�ɾ����\n");
			return;
		}
		for (i = index; i < allshiftscount - 1; i++)
			allshifts[i] = allshifts[i + 1];
		allshiftscount--;
		printf("ɾ����ϣ�ʣ��%d�Ρ�\r\n", allshiftscount);
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

void searchandbuy(int hour, int minute)
{
	int i;
	char c;
	i = getshiftidexbytime(hour, minute);
	if (i >= 0)
	{
		printf("�鵽�˰����Ϣ���£�\r\n");
		displayshift(allshifts[i]);
		if (allshifts[i].leftseats > 0)
		{
			printf("Ҫ����Ʊ������y����������ȡ��:");
			fseek(stdin, 0, SEEK_END);
			c = getchar();
			if (c == 'y' || c == 'Y')
			{
				allshifts[i].leftseats--;
				printf("�ɹ�����Ʊ��\n");
			}
		}
		else
			printf("��Ǹ���˳���Ʊ�����ꡣ");
	}
	else
	{
		printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	}

}

void promptsearchandbuy()
{
	int hour;
	int minute;
	printf("������Ҫ��ѯ�ķ���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
	scanf("%d%d", &hour, &minute);
	searchandbuy(hour, minute);
}

void add8shifts()
{
	addshift("k001", 6, 0);
	addshift("k002", 7, 0);
	addshift("k003", 9, 0);
	addshift("k004", 10, 30);
	addshift("k005", 14, 0);
	addshift("k006", 15, 30);
	addshift("k007", 16, 30);
	addshift("k008", 17, 30);
}

int main()
{
	int choice = -1;
	add8shifts();
#if 0
	//promptaddshift();
	displayallshifts();
	allshifts[1].leftseats = 44;
	promptaddshift();
	//prompteditshift();
	//promptsearchandbuy();
	//searchandbuy(7, 0);
	//promptremoveshift();
	displayallshifts();
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �𳵶�Ʊϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ӳ���");
		printf("\n\t 2. �޸ķ���ʱ��");
		printf("\n\t 3. ɾ��");
		printf("\n\t 4. ��ѯ");
		printf("\n\t 5. ���");
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
			promptaddshift();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			prompteditshift();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptremoveshift();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptsearchandbuy();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			displayallshifts();
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

