#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SEAT_COUNT 45

//1.�����������У����������л�С����2-5-203��100������һ����1500��13700000001��
typedef struct house
{
	//int id;
	char name[20];
	char location[50];
	char area[20];
	char type[20];
	int price;
	char telephone[20];
	int isrent;
}house;

house allhouses[20];
int allhousescount = 0;

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

//char *isrentstring[2] = { "δ��","����" };

char *isrentstring(int index)
{
	return allhouses[index].isrent ? "����" : "δ��";
}

void displayhouse(int i)
{
	house s = allhouses[i];
	printf("%4d %4s %20s %3s %6s %5d %11s %s\n",
		i + 1, s.name, s.location, s.area, s.type, s.price, s.telephone, isrentstring(i));
}

int cmpfunc(const void * b, const void * a)
{
	return ((house*)a)->price - ((house*)b)->price;
}

void displayallhouses()
{
	int i;
	//qsort(allhouses, allhousescount, sizeof(house), cmpfunc);
	printf("����%dλ�����Ϣ����\r\n", allhousescount);
	//���������������ݵ�ַ�����С�����С�������ƺţ������ݵ�ַ����һ���ֶΣ���������������ݸ�֣����磺һ��һ����������۸���ϵ�绰
	//printf("���\t����\t��ַ\t���\t���\t�۸�\t�绰\n");
	printf("%4s %4s %20s %3s %6s %5s %11s %s\n", "���",
		"����", "��ַ", "���", "���", "�۸�", "�绰", "״̬");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allhousescount; i++)
	{
		displayhouse(i);
	}
	printf("--------------------------------------------\r\n");
}

int gethouseidexbytime(int hour, int minute)
{
	int i;
	//for (i = 0; i < allhousescount; i++)
	//{
	//	if (allhouses[i].hour == hour
	//		&& allhouses[i].minute == minute)
	//		return i;
	//}
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


int gethouseidexbyno(char id[50])
{
	int i;
	//for (i = 0; i < allhousescount; i++)
	//{
	//	if (streq(allhouses[i].id, id))
	//		return i;
	//}
	return -1;//û�ҵ�
}

void edithouse(char id[50])
{
	int i;
	int hour;
	int minute;
	int exphour;
	int expminute;
	i = gethouseidexbyno(id);
	//if (i >= 0)
	//{
	//	if (allhouses[i].price < SEAT_COUNT)
	//	{
	//		printf("�����г��Ѿ���Ʊ�۳����޷��޸�ʱ�䣡\n");
	//		return;
	//	}
	//	printf("\n�������·���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
	//	scanf("%d%d", &hour, &minute);
	//	checktimevalid(hour, minute, &exphour, &expminute);
	//	if (gethouseidexbytime(exphour, expminute) >= 0)
	//	{
	//		printf("ʱ�������а���ظ���\n");
	//		return;
	//	}
	//	allhouses[i].hour = exphour;
	//	allhouses[i].minute = expminute;
	//	printf("�޸���ϡ�\r\n");
	//}
	//else
	//{
	//	printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	//}
}

void promptedithouse()
{
	char id[50];
	printf("������Ҫ�޸�ʱ��İ��:");
	scanf("%s", &id);
	edithouse(id);
}

void addhouse(char location[50], char area[20], char type[20], int price)
{
	house s;
	strcpy(s.name, "?");
	strcpy(s.location, location);
	strcpy(s.area, area);
	strcpy(s.type, type);
	s.price = price;
	strcpy(s.telephone, "?");
	s.isrent = 0;
	allhouses[allhousescount++] = s;
}

void promptaddhouse()
{
	char location[50];
	char area[20];
	char type[20];
	int price;
	printf("\n�������ַ ��� ��֣����ǲ����ո���ַ���) �ͼ۸�(����), �ո������\n");
	scanf("%s%s%s%d", location, area, type, &price);
	/*checktimevalid(hour, minute, &exphour, &expminute);
	if (gethouseidexbytime(exphour, expminute) >= 0)
	{
		printf("ʱ�������а���ظ���\n");
		return;
	}*/
	addhouse(location, area, type, price);
	printf("��ɵ�%d���¼��!\r\n", allhousescount);
}


void removehouse(char no[20])
{
	int i;
	int index;
	index = gethouseidexbyno(no);
	if (index >= 0)
	{
		if (allhouses[index].price < SEAT_COUNT)
		{
			printf("�����г��Ѿ���Ʊ�۳����޷�ɾ����\n");
			return;
		}
		for (i = index; i < allhousescount - 1; i++)
			allhouses[i] = allhouses[i + 1];
		allhousescount--;
		printf("ɾ����ϣ�ʣ��%d�Ρ�\r\n", allhousescount);
	}
	else
	{
		printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	}

}

void promptremovehouse()
{
	int id;
	//printf("������Ҫɾ���İ��:");
	//scanf("%s", id);
	//removehouse(id);
}

void searchandbuy(int hour, int minute)
{
	int i;
	char c;
	i = gethouseidexbytime(hour, minute);
	//if (i >= 0)
	//{
	//	printf("�鵽�˰����Ϣ���£�\r\n");
	//	displayhouse(allhouses[i]);
	//	if (allhouses[i].price > 0)
	//	{
	//		printf("Ҫ����Ʊ������y����������ȡ��:");
	//		fseek(stdin, 0, SEEK_END);
	//		c = getchar();
	//		if (c == 'y' || c == 'Y')
	//		{
	//			allhouses[i].price--;
	//			printf("�ɹ�����Ʊ��\n");
	//		}
	//	}
	//	else
	//		printf("��Ǹ���˳���Ʊ�����ꡣ");
	//}
	//else
	//{
	//	printf("û�ҵ���Ӧ��εİ�Ρ�\r\n");
	//}

}

void promptsearchandbuy()
{
	int hour;
	int minute;
	printf("������Ҫ��ѯ�ķ���ʱ�䣨24Сʱ��ʱ �֣��ո��������");
	scanf("%d%d", &hour, &minute);
	searchandbuy(hour, minute);
}

void add8houses()
{
	addhouse("�����б������л�С��2-5-203", "100", "����һ��", 1500);

}

int main()
{
	int choice = -1;
	//add8houses();
#if 1
	promptaddhouse();
	//displayallhouses();
	//allhouses[1].leftseats = 44;
	//promptaddhouse();
	//promptedithouse();
	//promptsearchandbuy();
	//searchandbuy(7, 0);
	//promptremovehouse();
	displayallhouses();
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
			promptaddhouse();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptedithouse();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptremovehouse();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptsearchandbuy();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			displayallhouses();
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

