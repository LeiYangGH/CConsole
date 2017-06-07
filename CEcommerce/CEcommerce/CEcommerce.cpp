#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_USER "user.txt"//�������ļ�
#define FILE_ADMIN "admin.txt"//����Ա�ļ�
#define FILE_WARE "ware.txt"//��Ʒ�ļ�������ɾ�Ĳ飬�´�����exeʱ����
#define FILE_LOG "log.txt"//�����¼�ļ���ֻ�ṩһ����׷�ӣ��´�����exeʱ������
#pragma region typedef
typedef struct ware//��Ʒ
{
	char wid[20];//��Ʒ��ʶ��
	char name[20];//����
	float price;//����
	char address[20];//����
	int quantity;//���
	int warnquantity;//������Ϳ����ֵ
}ware;

ware allwares[20];//������Ʒ����ͬ
int allwarescount = 0;//������Ʒ������������ͬ

typedef struct user//�û�
{
	char name[20];//����
	char password[20];//����
	int isadmin;//�Ƿ����Ա
	float money;//���
}user;
user allusers[20];
int alluserscount = 0;

typedef struct log//�����¼
{
	char uname[20];//����������
	char wid[20];//��Ʒʶ����
	float quantity;//����
	int paid;//�Ƿ񸶷ѣ�1Ϊ����0Ϊû�����൱�ڹ��ﳵ
}log;

user alllogs[10];
int alllogscount = 0;
#pragma endregion

char currentusername[20] = "";

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
#pragma region users
//��¼
void login()
{
	int i;
	char uname[20] = "";
	char pwd[20] = "";
	printf("\n�������û���\n");
	scanf("%s", uname);
	printf("\n����������\n");
	scanf("%s", pwd);
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(uname, allusers[i].name)
			&& streq(pwd, allusers[i].password))
		{
			printf("%s��¼�ɹ���\n", uname);
			strcpy(currentusername, uname);
			return;
		}
	}
	printf("�û�����������󣬵�¼ʧ�ܣ�\n");
}

//�Ƿ��Ѿ�������ͬ�û�
int isusernameexists(char uname[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(uname, allusers[i].name))
			return 1;
	}
	return 0;
}

//���븴�Ӷȣ���ʱ�涨����>=6
int ispassowrdcomplicated(char password[20])
{
	return strlen(password) >= 6;
}

//д�����û��͹���Ա���ļ�
void writeallusersandadmins()
{
	int i;
	user u;
	FILE *fp = fopen(FILE_USER, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_USER);
		getchar();
		exit(1);
	}
	for (i = 0; i < alluserscount; i++)
	{
		u = allusers[i];
		if (!u.isadmin)
			fprintf(fp, "%s\t%s\n", u.name, u.password);
	}
	fclose(fp);

	fp = fopen(FILE_ADMIN, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_ADMIN);
		getchar();
		exit(1);
	}
	for (i = 0; i < alluserscount; i++)
	{
		u = allusers[i];
		if (u.isadmin)
			fprintf(fp, "%s\t%s\n", u.name, u.password);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

//ע���û����Ѿ�ͨ����֤�Ĳ���
void registeruser(char uname[20], char password[20], int isadmin)
{
	user u;
	strcpy(u.name, uname);
	strcpy(u.password, password);
	u.isadmin = isadmin;
	u.money = 0;//��ʼ��Ϊ0
	allusers[alluserscount++] = u;
	writeallusersandadmins();
}

//��ǰ�û��Ƿ����Ա
int iscurrentuseradmin()
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (allusers[i].isadmin
			&& streq(currentusername, allusers[i].name))
			return 1;
	}
	return 0;
}

//��ǰ�û��Ƿ�������
int iscurrentuserconsumer()
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (!allusers[i].isadmin
			&& streq(currentusername, allusers[i].name))
			return 1;
	}
	return 0;
}

//prompt����ʽ��ʾ�û�����
void promptregisteruser(int willbeadmin)
{
	char uname[20];
	char password[20];
	char *role = willbeadmin ? "����Ա" : "������";
	if (willbeadmin && !iscurrentuseradmin())
	{
		printf("��ǰ�û�%s���ǹ���Ա������ע�����Ա!", currentusername);
		return;
	}
	printf("������Ҫע���%s���û���:", role);
	scanf("%s", uname);
	if (isusernameexists(uname))
	{
		printf("%s�Ѿ����ڣ������ظ�ע��!", uname);
		return;
	}
	printf("������Ҫע�������:");
	scanf("%s", password);
	if (!ispassowrdcomplicated(password))
	{
		printf("����%s̫�򵥣�����6λ!", password);
		return;
	}
	registeruser(uname, password, willbeadmin);
	printf("��%ע��ɹ�!", role);
}

//�ǳ�
void logout()
{
	strcpy(currentusername, "");
	printf("�ǳ��ɹ�!");
}

//��һ���ı����Ϊ�û�
user getuserfromline(char *line, int isadmin)
{
	char *part;
	int index = 0;
	user u;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(u.name, part);
			break;
		case 2:
			strcpy(u.password, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	u.isadmin = isadmin;
	u.money = 0;//��ʼ��Ϊ0
	return u;
}

//�������������ߺ͹���Ա
void readallusersandadmins()
{
	char line[200];
	FILE *fp = fopen(FILE_USER, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_USER);
	}
	else
	{
		alluserscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line, 0);
		}
		printf("\n�Ѷ����������ļ�!\n");
	}
	fp = fopen(FILE_ADMIN, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_ADMIN);
	}
	else
	{
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line, 1);
		}
		printf("\n�Ѷ������Ա�ļ�!\n");
	}
}

#pragma endregion

#pragma region ware


void displayware(ware w)
{
	printf("%s\t%s\t%.1f\t%s\t%d\n", w.wid, w.name, w.price, w.address, w.quantity);
}
//��ʾ������Ʒ
void displayallwares()
{
	int i;
	printf("����%d����Ʒ��Ϣ����\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		displayware(allwares[i]);
	}
	printf("--------------------------------------------\r\n");
}
//��һ���ı����벢����\t���Ų�֣���ϳ�һ��ware
ware getwarefromline(char *line)
{
	char *part;
	int index = 0;
	ware w;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(w.wid, part);
			break;
		case 2:
			strcpy(w.name, part);
			break;
		case 3:
			w.price = tofloat(part);
			break;
		case 4:
			strcpy(w.address, part);
			break;
		case 5:
			w.quantity = toint(part);
			break;
		case 6:
			w.warnquantity = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return w;
}

//����������Ʒ
void readallwares()
{
	char line[200];
	FILE *fp = fopen(FILE_WARE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_WARE);
	}
	else
	{
		allwarescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allwares[allwarescount++] = getwarefromline(line);
		}
		printf("\n�Ѷ�����Ʒ�ļ�!");
	}
}


//������Ʒʶ����ó������±�
int getwareidexbywid(char wid[20])
{
	int i;
	for (i = 0; i < allwarescount; i++)
	{
		ware w = allwares[i];
		if (streq(w.wid, wid))
			return i;
	}
	return -1;
}

//д������Ʒ��Ϣ���ļ�
void writeallwares()
{
	int i;
	ware w;
	FILE *fp = fopen(FILE_WARE, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_WARE);
		getchar();
		exit(1);
	}
	for (i = 0; i < allwarescount; i++)
	{
		w = allwares[i];
		fprintf(fp, "%s %s %.1f %s %d %d\n",
			w.wid, w.name, w.price, w.address, w.quantity, w.warnquantity);
	}
	fclose(fp);
	printf("�ѱ����¼����Ʒ�ļ���");
}


//�޸���Ʒֻ�����޸ļ۸�Ϳ��
void editware(char wid[50])
{
	int i;
	char pwd[20] = "";
	i = getwareidexbywid(wid);
	if (i >= 0)
	{
		printf("\n�������µļ۸������򸡵������Ϳ�棨���������ո����\n");
		scanf("%f%d", &allwares[i].price, &allwares[i].quantity);
		writeallwares();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧʶ�������Ʒ��\r\n");
	}
}

void prompteditware()
{
	char wid[50];
	printf("������Ҫ�޸ĵ�ʶ����:");
	scanf("%s", &wid);
	editware(wid);
}

////�����Ʒ
void addware(char wid[20], char wname[], float price, char address[], int quantity, int warnquantity)
{
	ware w;
	strcpy(w.wid, wid);
	strcpy(w.name, wname);
	w.price = price;
	strcpy(w.address, address);
	w.quantity = quantity;
	w.warnquantity = warnquantity;
	allwares[allwarescount++] = w;
	writeallwares();
}

//�Ƿ��Ѿ�������ͬ�û�
int iswarewidexists(char wid[20])
{
	int i;
	for (i = 0; i < allwarescount; i++)
	{
		if (streq(wid, allwares[i].wid))
			return 1;
	}
	return 0;
}

void promptaddware()
{
	char wid[20];//��Ʒ��ʶ��
	char wname[20];//����
	float price;//����
	char address[20];//����
	int quantity;//���
	int warnquantity;//������Ϳ����ֵ
	printf("\n��������Ʒʶ����:\n");
	scanf("%s", wid);
	if (iswarewidexists(wid))
	{
		printf("ʶ����%s�Ѿ����ڣ������ظ������Ʒ!", wid);
		return;
	}
	printf("\n��������Ʒ���ơ����أ����ǲ����ո���ַ����������ۣ������򸡵���������桢���������ޣ��������������ո����\n");
	scanf("%s%s%f%d%d", wname, address, &price, &quantity, &warnquantity);

	addware(wid, wname, price, address, quantity, warnquantity);
	printf("��ɵ�%d�����¼��!\r\n", allwarescount);
}

//ɾ����Ʒ
void removeware(char no[20])
{
	int i;
	int index;
	index = getwareidexbywid(no);
	if (index >= 0)
	{
		for (i = index; i < allwarescount - 1; i++)
			allwares[i] = allwares[i + 1];
		allwarescount--;
		writeallwares();
		printf("ɾ����ϣ�ʣ��%d����Ʒ��\r\n", allwarescount);
	}
	else
	{
		printf("û�ҵ���Ӧʶ�������Ʒ��\r\n");
	}

}

void promptremoveware()
{
	char no[20];
	printf("������Ҫɾ������Ʒ��ʶ����:");
	scanf("%s", no);
	removeware(no);
}

//ͨ�����Ʋ�����Ʒ
void searchwarebyname(char *name)
{
	int i;
	for (i = 0; i < allwarescount; i++)
		if (strcmp(name, allwares[i].name) == 0)
		{
			displayware(allwares[i]);
			return;
		}
	printf("û�ҵ���Ӧ��Ʒ����Ϣ��\r\n");
}
//�û��������Ʋ�������Ʒ��Ϣ
void promptsearchbyname()
{
	char name[20];
	printf("������Ҫ���ҵ���Ʒ����:");
	scanf("%s", name);
	searchwarebyname(name);
}

#pragma endregion
//д���й����¼
void writealllogs()
{

}
//ÿ�μ��빺�ﳵ�ͼ������������򾯸�
void warnlack(char wid[20])
{

}
//�ӹ��ﳵ��log���
void addwant(char uname[], char wid[], int quantity)
{

}

//��ֵ
void recharge(char uname[], float money)
{

}

//֧������log�����е�ǰ�û���δ֧����ȫ����Ϊ֧��
void pay(char uname[])
{

}

//�˻������ű���log���˻�������������һ�ι��������
void returnware(char uname[], char wid[], int quantity)
{

}




int main()
{
	char choice = -1;
	readallusersandadmins();
	readallwares();
#if 0
	readallusers();
	login();
	promptregisteruser(0);
#endif
	while (choice != 'g')
	{
		printf("\n\t ���й���ϵͳ");
		printf("\n\t 1---�û���¼");
		printf("\n\t 2---�û��ǳ�");
		printf("\n\t 3---ע��������");
		printf("\n\t 4---ע�����Ա");
		printf("\n\t 5---�鿴������Ʒ��Ϣ");
		printf("\n\t 6---�������Ʋ�����Ʒ");
		printf("\n\t 7---�����Ʒ");
		printf("\n\t 8---����ʶ�����޸���Ʒ�۸�Ϳ��");
		printf("\n\t 9---����ʶ����ɾ����Ʒ");
		printf("\n\t 0---�˳�����\n\n");
		printf("\n---��ѡ��");
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
			logout();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptregisteruser(0);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptregisteruser(1);
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			displayallwares();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			promptsearchbyname();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			promptaddware();
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			prompteditware();
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			promptremoveware();
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