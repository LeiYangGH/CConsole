#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//1.�����������У����������л�С����2-5-203��100������һ����1500��13700000001��
typedef struct house
{
	char name[20];
	char address[50];
	char area[20];
	char type[20];
	int price;
	char telephone[20];
	int isrent;
}house;

house allhouses[20];
int allhousescount = 0;
int filteredindex[20] = { -1 };
int filteredindexcount = 0;
//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

char *isrentstring(int index)
{
	return allhouses[index].isrent ? "����" : "δ��";
}

void displayhouse(int i)
{
	house s = allhouses[i];
	printf("%4d %4s %20s %3s %6s %5d %11s %s\n",
		i + 1, s.name, s.address, s.area, s.type, s.price, s.telephone, isrentstring(i));
}

int cmpprice(const void * a, const void * b)
{
	return ((house*)a)->price - ((house*)b)->price;
}

void displayallhouses(int isrent, char location[50], char type[20])
{
	int i;
	char *msg[2] = { "δ��","����" };
	printf("����%s��Դ��Ϣ����\r\n", msg[isrent]);
	//���������������ݵ�ַ�����С�����С�������ƺţ������ݵ�ַ����һ���ֶΣ���������������ݸ�֣����磺һ��һ����������۸���ϵ�绰
	printf("%4s %4s %20s %3s %6s %5s %11s %s\n", "���",
		"����", "��ַ", "���", "���", "�۸�", "�绰", "״̬");
	printf("--------------------------------------------\r\n");
	filteredindexcount = 0;
	for (i = 0; i < allhousescount; i++)
	{
		if (isrent == allhouses[i].isrent
			&& (streq(location, "") || streq(allhouses[i].address, location))
			&& (streq(type, "") || streq(allhouses[i].type, type)))
		{
			displayhouse(i);
			filteredindex[filteredindexcount++] = i;
		}
	}
	printf("--------------------------------------------\r\n");
}

void addhouse(char location[50], char area[20], char type[20], int price)
{
	house s;
	strcpy(s.name, "?");
	strcpy(s.address, location);
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
	addhouse(location, area, type, price);
	printf("��ɵ�%d��Դ¼��!\r\n", allhousescount);
}

int isindexinfiltered(int index)
{
	int i;
	for (i = 0; i < filteredindexcount; i++)
		if (filteredindex[i] == index)
			return 1;
	return 0;
}

void removehouse(int index)
{
	int i;
	if (index >= 0 && index < allhousescount)
	{
		if (!allhouses[index].isrent)
		{
			printf("���Ϊ%d�ķ�Դ��δ���⣬�޷�ɾ����\n", index + 1);
			return;
		}
		for (i = index; i < allhousescount - 1; i++)
			allhouses[i] = allhouses[i + 1];
		allhousescount--;
		printf("ɾ����ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ����Ϊ%d�ķ�Դ��\r\n", index + 1);
	}

}

void promptremovehouse()
{
	int id;
	printf("������Ҫɾ���ķ�Դ�����:");
	scanf("%d", &id);
	removehouse(id - 1);
}

void renthouse(int index)
{
	int i;
	char name[20];
	char telephone[20];
	if (isindexinfiltered(index))
	{
		if (allhouses[index].isrent)
		{
			printf("���Ϊ%d�ķ�Դ�Ѿ����⣬�޷����⣡\n", index + 1);
			return;
		}
		printf("\n��������������� �绰�����ǲ����ո���ַ���), �ո������\n");
		scanf("%s%s", name, telephone);

		strcpy(allhouses[index].name, name);
		strcpy(allhouses[index].telephone, telephone);
		allhouses[index].isrent = 1;
		printf("����ɹ���\r\n");
	}
	else
	{
		printf("���Ϊ%d�ķ�Դû��ɸѡ�����Χ�ڡ�\r\n", index + 1);
	}

}

void promptrenthouse()
{
	int id;
	printf("������Ҫ����ķ�Դ�����:");
	scanf("%d", &id);
	renthouse(id - 1);
}

void add4houses()
{
	addhouse("�����б������л�С��2-5-203", "100", "����һ��", 1500);
	addhouse("add2", "200", "type2", 2500);
	addhouse("add3", "300", "typex", 350);
	addhouse("add4", "400", "typex", 45);

}

void menu1()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t �������޹���ϵͳ");
		printf("\n\t 0. �����ϼ��˵�");
		printf("\n\t  ��Ҫ����");
		printf("\n\t\t 1 ��ӷ�Դ");
		printf("\n\t\t 2 ɾ��������Ϣ");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			promptaddhouse();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallhouses(1, "", "");
			promptremovehouse();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
}

void menu22()
{
	int choice = -1;
	char location[50];
	char type[20];
	while (choice != 0)
	{
		printf("\n\t �������޹���ϵͳ");
		printf("\n\t 0. �����ϼ��˵�");
		printf("\n\t   ��Ҫ�ⷿ");
		printf("\n\t\t    ����");
		printf("\n\t\t\t  1 ���յ�ַ����");
		printf("\n\t\t\t  2 ���ո�ֲ���");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			printf("������Ҫ��ѯ�ķ��ݵ�ַ�����뾫ȷƥ�䣩��");
			scanf("%s", location);
			qsort(allhouses, allhousescount, sizeof(house), cmpprice);
			displayallhouses(0, location, "");
			if (filteredindexcount > 0)
			{
				promptrenthouse();
			}
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			printf("������Ҫ��ѯ�ķ��ݸ�֣����뾫ȷƥ�䣩��");
			scanf("%s", type);
			qsort(allhouses, allhousescount, sizeof(house), cmpprice);
			displayallhouses(0, "", type);
			if (filteredindexcount > 0)
			{
				promptrenthouse();
			}
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
}


void menu2()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t �������޹���ϵͳ");
		printf("\n\t 0. �����ϼ��˵�");
		printf("\n\t   ��Ҫ�ⷿ");
		printf("\n\t\t  1 ��Դ��Ϣ");
		printf("\n\t\t  2 ����");
		printf("\n\t\t\t   ���յ�ַ����");
		printf("\n\t\t\t   ���ո�ֲ���");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			displayallhouses(0, "", "");
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			menu22();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
}

int main()
{
	int choice = -1;
	add4houses();
#if 0
	displayallhouses(0, "", "");

	//promptaddhouse();
	//displayallhouses();
	//allhouses[1].leftseats = 44;
	//promptaddhouse();
	//promptedithouse();
	//promptsearchandrent();
	//searchandrent(7, 0);
	//promptremovehouse();
	promptremovehouse();
	displayallhouses(0, "", "");
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �������޹���ϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��Ҫ����");
		printf("\n\t\t   ��ӷ�Դ");
		printf("\n\t\t   ɾ��������Ϣ");
		printf("\n\t 2. ��Ҫ�ⷿ");
		printf("\n\t\t   ��Դ��Ϣ");
		printf("\n\t\t   ����");
		printf("\n\t\t\t   ���յ�ַ����");
		printf("\n\t\t\t   ���ո�ֲ���");
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
			menu1();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			menu2();
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

