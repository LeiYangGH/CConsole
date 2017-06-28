//����Ա��¼
//¼�����Ϣ������յ㣬��ʱ�䣬����ʱ�䣬���Σ�ϯ����Ʊ��
//��ɾ��Ϣ �޸���Ϣ
//�û���¼�� �ж������ID�Ƿ���ȷ��
//ͨ�� ���� ��ѯ����
//����Ҫ�����Ʊ�ĳ���
//�鿴�ѹ����Ʊ
//������ɹ�����ϵͳʱ������ʱ�������Сʱ
//��Ʊ����س�Ʊ�������۳��������˻����˻�
//��ǩ���ظ���Ʊ�׶Σ���س�Ʊ��� - 1���۳�������
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ADMIN "admin"
typedef struct shift
{
	char id[20];
	int hour;
	int minute;
	char start[20];
	char end[20];
	char seattype[20];
	int totalseats;
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

typedef struct user//�û�
{
	char name[20];//����
	char password[20];//����
}user;
user allusers[20];
int alluserscount = 0;

char currentusername[20] = "";


typedef struct buy//�û�
{
	char id[20];
	char name[20];
}buy;
buy allbuys[20];
int allbuyscount = 0;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

int getuseridexbyuname(char uname[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		user u = allusers[i];
		if (streq(u.name, uname))
			return i;
	}
	return -1;
}
void registeruser(char name[20], char password[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	allusers[alluserscount++] = u;
}

int userlogin()
{
	int i, index, retryleft = 2;
	char name[20] = "";
	char pwd[20] = "^";
	char exppwd[20] = "";


	printf("\n�������û�����");
	scanf("%s", name);
	index = getuseridexbyuname(name);
	if (index < 0)
	{
		printf("\n�û���������\n");
		return 0;
	}

	strcpy(exppwd, allusers[index].password);

	printf("����������: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", pwd);

	if (streq(exppwd, pwd))
	{
		printf("%s��¼�ɹ���\n", name);
		strcpy(currentusername, name);
		return 1;
	}
	else
	{
		printf("��Ǹ����������¼ʧ��");
		return 0;
	}
}

int adminlogin()
{
	int i;
	char uname[20] = "";
	char pwd[20] = "";
	printf("\n���������Ա�û�����");
	scanf("%s", uname);
	printf("\n���������Ա���룺");
	scanf("%s", pwd);

	if (streq(uname, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s��¼�ɹ���\n", uname);
		strcpy(currentusername, ADMIN);
		return 1;
	}
	printf("�û�����������󣬵�¼ʧ�ܣ�\n");
	return 0;
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
		s.id, s.hour, s.minute, s.start, s.end, s.totalseats, s.leftseats);
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

void displaymyshifts(char name[20])
{
	int i, j;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("�ÿ�%s��������а����Ϣ����\n", name);
	printf("���\tʱ��\t���\t�յ�\t��λ\t��Ʊ\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allbuyscount; i++)
	{
		if (streq(allbuys[i].name, name))
		{
			j = getshiftidexbyno(allbuys[i].id);
			displayshift(allshifts[j]);
		}
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
		if (allshifts[i].leftseats < allshifts[i].totalseats)
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

void addshift(char id[], int hour, int minute, char start[20], char end[20], char seattype[20], int totalseats)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, start);
	strcpy(s.end, end);
	strcpy(s.seattype, seattype);
	s.totalseats = totalseats;
	s.leftseats = totalseats;
	allshifts[allshiftscount++] = s;
}

void promptaddshift()
{
	char id[20];
	int hour;
	int minute;
	int exphour;
	char start[20];
	char end[20];
	char seattype[20];
	int expminute;
	int totalseats;
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
	printf("\n������ʼ��վ���յ�վ(�ո��������");
	scanf("%s%s", start, end);
	printf("\n������ϯ�����λ��(�ո��������");
	scanf("%s%d", seattype, &totalseats);
	addshift(id, exphour, expminute, start, end, seattype, totalseats);
	printf("��ɵ�%d���¼��!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		if (allshifts[index].leftseats < allshifts[index].totalseats)
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


void addbuy(char id[20], char name[20])
{
	int i;
	buy b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	i = getshiftidexbyno(id);
	allshifts[i].leftseats--;
	allbuys[allbuyscount++] = b;
}


void searchandbuy(char id[20])
{
	int i;
	char c;
	i = getshiftidexbyno(id);
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
				addbuy(id, currentusername);
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
	char id[20];
	printf("������Ҫ����ĳ��Σ�");
	scanf("%s", id);
	searchandbuy(id);
}

void addsampleshifts()
{
	addshift("d001", 6, 0, "����", "�Ϻ�", "Ӳ��", 3);
	addshift("k002", 11, 20, "�ɶ�", "����", "Ӳ��", 6);
	addshift("k003", 15, 0, "��ɳ", "����", "����", 9);
}

int main()
{
	int choice = -1;
	addsampleshifts();
	registeruser("u1", "p1");
	registeruser("u3", "p3");
	registeruser("u2", "p2");
#if 1
	displayallshifts();

	strcpy(currentusername, "u1");
	searchandbuy("d001");
	searchandbuy("k002");
	displaymyshifts(currentusername);

	strcpy(currentusername, "u2");
	searchandbuy("d001");
	displaymyshifts(currentusername);

	//promptaddshift();
	//allshifts[1].leftseats = 44;
	//promptaddshift();
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

