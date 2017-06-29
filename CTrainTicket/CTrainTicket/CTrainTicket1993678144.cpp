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
	int price;
	int totalseats;
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

typedef struct user//�û�
{
	char name[20];//����
	char password[20];//����
	int money;//���
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

int getuseridexbyname(char name[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		user u = allusers[i];
		if (streq(u.name, name))
			return i;
	}
	return -1;
}

int getbuyidbyshiftuser(char name[], char id[])
{
	int i;
	for (i = allbuyscount - 1; i >= 0; i--)
		if (streq(allbuys[i].name, name)
			&& streq(allbuys[i].id, id))
		{
			return i;
		}
	return -1;
}

int iscurrentuseradmin()
{
	return streq(currentusername, ADMIN);
}

int iscurrentuserpassenger()
{
	int i = getuseridexbyname(currentusername);
	return i >= 0;
}

void registeruser(char name[20], char password[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	u.money = 1000;
	allusers[alluserscount++] = u;
}

int userbuyin()
{
	int i, index, retryleft = 2;
	char name[20] = "";
	char pwd[20] = "^";
	char exppwd[20] = "";


	printf("\n�������û�����");
	scanf("%s", name);
	index = getuseridexbyname(name);
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

int adminbuyin()
{
	int i;
	char name[20] = "";
	char pwd[20] = "";
	printf("\n���������Ա�û�����");
	scanf("%s", name);
	printf("\n���������Ա���룺");
	scanf("%s", pwd);

	if (streq(name, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s��¼�ɹ���\n", name);
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
	printf("%s\t%02d:%02d\t%s\t%s\t%d\t%d\t%d\n",
		s.id, s.hour, s.minute, s.start, s.end, s.price, s.totalseats, s.leftseats);
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
	printf("���\tʱ��\t���\t�յ�\t�۸�\t��Ʊ��\t��Ʊ\n"),
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
	int i, j, u;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("�ÿ�%s��������а����Ϣ����\n", name);
	printf("���\tʱ��\t���\t�յ�\t�۸�\t��Ʊ��\t��Ʊ\n"),
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
	u = getuseridexbyname(name);
	printf("�ÿ�%s�����Ϊ%d\n", name, allusers[u].money);

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
	int price;
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
		printf("\n�������¼۸�����������");
		scanf("%d", &price);
		allshifts[i].hour = exphour;
		allshifts[i].minute = expminute;
		allshifts[i].price = price;
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
	int price;
	printf("������Ҫ�޸�ʱ��İ��:");
	scanf("%s", &id);
	editshift(id);
}

void addshift(char id[], int hour, int minute, char start[20], char end[20], int price, int totalseats)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, start);
	strcpy(s.end, end);
	s.price = price;
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
	int price;
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
	printf("\n������۸����λ��(���������ո��������");
	scanf("%d%d", &price, &totalseats);
	addshift(id, exphour, expminute, start, end, price, totalseats);
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
	int i, uindex;
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
				uindex = getuseridexbyname(currentusername);
				if (allusers[uindex].money < allshifts[i].price)
				{
					printf("�ÿ�%s����Ǹ����������(%dԪ)����Ʊʧ�ܣ�\n", currentusername, allusers[uindex].money);
					return;
				}
				addbuy(id, currentusername);
				allusers[uindex].money -= allshifts[i].price;
				printf("�ÿ�%s�����򳵴�%s�ɹ������%d��\n", currentusername, id, allusers[uindex].money);
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



int returnticket(char name[], char id[])
{
	int i, sindex, uindex;
	int bindex = getbuyidbyshiftuser(name, id);
	buy b = allbuys[bindex];
	if (bindex < 0)
	{
		printf("�ÿ�%s����Ǹ��û�в鵽�����򳵴�%s�ļ�¼����Ʊʧ�ܣ�\n", name, id);
		return 0;
	}


	for (i = bindex; i < allbuyscount - 1; i++)
		allbuys[i] = allbuys[i + 1];
	allbuyscount--;

	sindex = getshiftidexbyno(id);
	allshifts[sindex].leftseats++;

	uindex = getuseridexbyname(name);
	allusers[uindex].money += allshifts[sindex].price*0.15;
	printf("�ÿ�%s����Ʊ����%s�ɹ������%d��\n", name, id, allusers[uindex].money);

	return 1;
}

void promptreturnticket()
{
	char id[20];
	int sindex, quantity;
	printf("�𾴵��ÿ�%s����������Ʊ�ĳ���:", currentusername);
	scanf("%s", id);
	sindex = getshiftidexbyno(id);
	if (sindex < 0)
	{
		printf("�𾴵��ÿ�%s��������ĳ����Ҳ�����������������룬лл��", currentusername);
		return;
	}
	returnticket(currentusername, id);
}


//id0 id1 valid
int changeticket(char name[], char id0[], char id1[])
{
	int i, sindex0, sindex1, uindex, reducemoney;
	int bindex0 = getbuyidbyshiftuser(name, id0);
	int bindex1 = getbuyidbyshiftuser(name, id1);
	if (bindex0 < 0)
	{
		printf("�ÿ�%s����Ǹ��û�в鵽�����򳵴�%s�ļ�¼����ǩʧ�ܣ�\n", name, id0);
		return 0;
	}

	if (bindex1 >= 0)
	{
		printf("�ÿ�%s����Ǹ����ǩ�ĳ���%s���ܺ��Ѿ�����ĳ���һ��һ������ǩʧ�ܣ�\n", name, id0);
		return 0;
	}


	uindex = getuseridexbyname(name);
	sindex0 = getshiftidexbyno(id0);
	sindex1 = getshiftidexbyno(id1);
	reducemoney = (allshifts[sindex1].price - allshifts[sindex0].price) + allshifts[sindex0].price*0.15;
	if (allusers[uindex].money < reducemoney)
	{
		printf("�ÿ�%s����Ǹ���������㣨%d������ǩʧ�ܣ�\n", name, allusers[uindex].money);
		return 0;
	}


	allshifts[sindex0].leftseats++;

	allshifts[sindex1].leftseats--;

	strcpy(allbuys[bindex0].id, id1);

	allusers[uindex].money -= reducemoney;
	printf("�ÿ�%s����ǩ����%sΪ%s�ɹ������%d��\n", name, id0, id1, allusers[uindex].money);

	return 1;
}

void promptchangeticket()
{
	char id0[20], id1[20];
	int sindex0, sindex1, quantity;
	printf("�𾴵��ÿ�%s�����������ѹ�����Ҫ��ǩ�ĳ���:", currentusername);
	scanf("%s", id0);
	sindex0 = getshiftidexbyno(id0);
	if (sindex0 < 0)
	{
		printf("�𾴵��ÿ�%s��������ĳ����Ҳ�����������������룬лл��", currentusername);
		return;
	}
	printf("�𾴵��ÿ�%s���������ǩΪ�ĸ�����:", currentusername);
	scanf("%s", id1);
	sindex1 = getshiftidexbyno(id1);
	if (sindex1 < 0)
	{
		printf("�𾴵��ÿ�%s��������ĳ����Ҳ�����������������룬лл��", currentusername);
		return;
	}
	changeticket(currentusername, id0, id1);
}

int login()
{
	int i;
	char name[20] = "";
	char pwd[20] = "";
	printf("\n�������û�����");
	scanf("%s", name);
	printf("\n���������룺");
	scanf("%s", pwd);

	if (streq(name, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s����Ա��¼�ɹ���\n", name);
		strcpy(currentusername, ADMIN);
		return 1;
	}

	i = getuseridexbyname(name);
	if (streq(allusers[i].password, pwd))
	{
		printf("%s�ÿ͵�¼�ɹ���\n", name);
		strcpy(currentusername, name);
		return 1;
	}

	printf("�û�����������󣬵�¼ʧ�ܣ�\n");
	return 0;
}

int main()
{
	int choice = -1;
	//ʾ���г����ݣ���ɾ��
	addshift("d001", 6, 0, "����", "�Ϻ�", 200, 3);
	addshift("k002", 11, 20, "�ɶ�", "����", 150, 6);
	addshift("k003", 15, 0, "��ɳ", "����", 500, 9);
	//ʾ���û�����������û��д�û��������д��3���û�
	registeruser("u1", "p1");
	registeruser("u3", "p3");
	registeruser("u2", "p2");
#if 0
	displayallshifts();

	strcpy(currentusername, "u1");
	searchandbuy("d001");
	searchandbuy("k002");
	displaymyshifts(currentusername);

	strcpy(currentusername, "u2");
	searchandbuy("d001");
	displaymyshifts(currentusername);

	//changeticket(currentusername, "d001", "k002");
	returnticket(currentusername, "d001");
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
		printf("\n\t 1. ��¼");
		printf("\n\t 2. ��ӳ���");
		printf("\n\t 3. �޸ķ���ʱ��ͼ۸�");
		printf("\n\t 4. ɾ������");
		printf("\n\t 5. ������г���");
		printf("\n\t 6. ��ѯ���β���Ʊ");
		printf("\n\t 7. ��Ʊ");
		printf("\n\t 8. ��ǩ");
		printf("\n\t 9. ��ѯ�ҵ������ѹ���ĳ�Ʊ");
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
			login();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			promptaddshift();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			prompteditshift();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			promptremoveshift();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			displayallshifts();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			if (!iscurrentuserpassenger())
			{
				printf("��ǰ�û�%s�����ÿͣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptsearchandbuy();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			if (!iscurrentuserpassenger())
			{
				printf("��ǰ�û�%s�����ÿͣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptreturnticket();
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			if (!iscurrentuserpassenger())
			{
				printf("��ǰ�û�%s�����ÿͣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptchangeticket();
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			if (!iscurrentuserpassenger())
			{
				printf("��ǰ�û�%s�����ÿͣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			displaymyshifts(currentusername);
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

