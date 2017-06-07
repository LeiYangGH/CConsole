#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_USER "user.txt"
#define FILE_ADMIN "admin.txt"
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

char currentusername[20] = "";

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

#pragma region users
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

void writeallusers()
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
	writeallusers();
}

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


void logout()
{
	strcpy(currentusername, "");
	printf("�ǳ��ɹ�!");
}

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

void readallusers()
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




void displayallwares()
{
}

void readallwares()
{
}

int getwareidexbyno(char wid[20])
{
	return 1;

}

void writeallwares()
{
}

void editware(char wid[20])
{
}

void addware(char wid[20], char uname[], float price, char address, int quantity, int warnquantity)
{
}

void removeware(char wid[20])
{
}

void searcbyname(char *uname)
{
}

void writealllogs()
{

}

void warnlack(char wid[20])
{

}

void addwant(char uname[], char wid[], int quantity)
{

}

void recharge(char uname[], float money)
{

}

void pay(char uname[])
{

}

void returnware(char uname[], char wid[], int quantity)
{

}




int main()
{
	char choice = -1;
	readallusers();
#if 0
	readallusers();
	login();
	promptregisteruser(0);
#endif
	while (choice != 'g')
	{
		printf("\n\t ���й���ϵͳ");
		printf("\n\t 1---�û���¼");
		printf("\n\t 2---ע��������");
		printf("\n\t 3---ע�����Ա");
		printf("\n\t 4---�û��ǳ�");
		printf("\n\t 0---�˳�����\n\n");
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
			promptregisteruser(0);
			break;
		case '3':
			printf("\n\n��ѡ���� 2\n");
			promptregisteruser(1);
			break;
		case '4':
			printf("\n\n��ѡ���� 2\n");
			logout();
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