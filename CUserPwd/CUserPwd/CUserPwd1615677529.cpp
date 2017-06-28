//1�� ��Ʋ�ʵ��һ���û�����ʵ���û��Ĺ���Ҫ��ʵ�����ֽ�ɫ����ͨ�û��͹���Ա���û���admin�����룺admin����һ���˵���
//1)       ע��
//2)       ��¼
//��ѡ��
//ѡ��1.ע���Ҫ�������û�������Ϣ���û��������롢ȷ�����롢�Ա𡢳��������Լ���֤��Ϣ�����䣩��Ҫ�����֤��Ϣ���������䣬�Ҳ����ظ�ע�ᣬ����������䲻��ȷ�����������롣��ʾ�����������@��.��@��.ǰ�棬��@���ܿ�ͷ��.���ܽ�β���������Լ�ȷ������Ӧ�ñ���һ�£�����һ�������������롣
//ѡ��2.��¼��ʵ�ֶ����˵���
//1)       ��ͨ�û���¼
//2)       ����Ա��¼
//��ѡ��
//ѡ��1.��ͨ�û���¼�������û����Լ����룬����������������ᣬ�����ζ���������û��������������ٽ��е�¼������¼�ɹ����û������޸��Լ��Ļ�����Ϣ�����䲻���޸ģ���
//ѡ��2.����Ա��¼�������û�����admin�����루admin����ʵ�������˵���
//1)       ��ʾ�����û��������û�������
//2)       ��ʾ�����û��������û�������
//ѡ��2.��ʾ�����û���ʵ�����¹��ܣ������û������в�ѯ�������ڸ��û��������û�������״̬�����
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ADMIN "admin"
#pragma region typedef
typedef struct user//�û�
{
	char name[20];//����
	char password[20];//����
	char gender[20];//�Ա�
	char birthday[20];//��������
	char email[20];//��֤����
	int islocked;
}user;
user allusers[20];
int alluserscount = 0;


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
void displayuser(user u)
{
	printf("%s\t%s\t%s\t%s\n",
		u.name, u.gender, u.birthday, u.email);
}

int cmpfunc(const void * a, const void * b)
{
	return ((user*)a)->name - ((user*)b)->name;
}

void displayallusers()
{
	int i;
	qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("����%dλ�û���Ϣ����\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
}

void displayalllockedusers()
{
	int i;
	qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("���б������û���Ϣ����\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		if (allusers[i].islocked)
			displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
}

//�Ƿ��Ѿ�������ͬ�û���
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

//�����û����ó������±�
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

//��¼
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

	if (allusers[index].islocked)
	{
		printf("\n�û�%sΪ����״̬������ϵ����Ա����\n", name);
		return 0;
	}

	strcpy(exppwd, allusers[index].password);

	printf("����������: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", pwd);
	while (!streq(exppwd, pwd) && retryleft-- > 0)
	{
		printf("�������,����������:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", pwd);
	}
	if (streq(exppwd, pwd))
	{
		printf("%s��¼�ɹ���\n", name);
		strcpy(currentusername, name);
		return 1;
	}
	else
	{
		allusers[index].islocked = 1;
		printf("��Ǹ���û�%s�ѱ�����", name);
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


int isemailvalid(char email[20])
{
	int i, len = strlen(email), iat = -1, idot = -1;
	for (i = 0; i < len; i++)
	{
		if (email[i] == '@')
			iat = i;
		else if (email[i] == '.')
			idot = i;
	}
	return iat != -1 && idot != -1
		&& iat < idot
		&& iat != 0 && idot != len - 1;
}


//ע���û����Ѿ�ͨ����֤�Ĳ���
void registeruser(char name[20], char password[20], char gender[20], char birthday[20], char email[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	strcpy(u.gender, gender);
	strcpy(u.birthday, birthday);
	strcpy(u.email, email);
	u.islocked = 0;
	allusers[alluserscount++] = u;
}

//��ǰ�û��Ƿ����Ա
int iscurrentuseradmin()
{
	return streq(currentusername, ADMIN);
}


void promptregisteruser()
{
	char name[20];//����
	char password[20] = "1";//����
	char password1[20] = "2";//����
	char gender[20];//�Ա�
	char birthday[20];//��������
	char email[20];//��֤����

	printf("\n������Ҫע��ĵ��û���:");
	scanf("%s", name);
	if (isusernameexists(name))
	{
		printf("%s�Ѿ����ڣ������ظ�ע��!", name);
		return;
	}
	while (!streq(password, password1))
	{
		printf("������Ҫע�������:");
		scanf("%s", password);
		printf("���ٴ�����Ҫע�������:");
		scanf("%s", password1);
		if (!streq(password, password1))
		{
			printf("������������벻һ�£�");
		}
	}
	printf("�������Ա�����գ��ո����:");
	scanf("%s%s", gender, birthday);
	while (!isemailvalid(email))
	{
		printf("��������֤����:");
		scanf("%s", email);
		if (!isemailvalid(email))
		{
			printf("���������@��.��@��.ǰ�棬��@���ܿ�ͷ��.���ܽ�β!");
		}
	}
	registeruser(name, password, gender, birthday, email);
	printf("���û�ע��ɹ�!");
}

void promptunlockuser()
{
	int index;
	char name[20];//����
	printf("\n������Ҫ�������û���:");
	scanf("%s", name);
	index = getuseridexbyuname(name);
	if (index < 0)
	{
		printf("\n�û���������\n");
		return;
	}

	if (allusers[index].islocked)
	{
		allusers[index].islocked = 0;
		printf("\nΪ�û�%s�����ɹ�\n", name);
	}
	else
		printf("\n�û�%s��ǰΪ��Ծ״̬������Ҫ����\n", name);
}

void edituser(char name[50])
{
	int index;
	char gender[20];//�Ա�
	char birthday[20];//��������	i = getuseridexbyuname(name);
	index = getuseridexbyuname(name);
	if (index >= 0)
	{
		printf("\n�������µ��Ա𡢳�������\n");
		scanf("%s%s", allusers[index].gender, allusers[index].birthday);
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧ�û������û���\r\n");
	}
}


//�ǳ�
void logout()
{
	strcpy(currentusername, "");
	printf("�ǳ��ɹ�!");
}


#pragma endregion


void menu22()
{
	int choice = -1;
	char location[50];
	char type[20];
	while (choice != 0)
	{
		printf("\n\t �û�����");
		printf("\n\t 0. �����ϼ��˵�");
		printf("\n\t    ��¼");
		printf("\n\t\t   ����Ա��¼");
		printf("\n\t\t\t   1.��ʾ�����û�");
		printf("\n\t\t\t   2.��ʾ�����û�");
		printf("\n\t\t\t   3.�����û�����");
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
			displayallusers();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayalllockedusers();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptunlockuser();
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
		printf("\n\t �û�����");
		printf("\n\t 0. �����ϼ��˵�");
		printf("\n\t    ��¼");
		printf("\n\t\t   1.��ͨ�û���¼�����޸��Լ��Ļ�����Ϣ��");
		printf("\n\t\t   2.����Ա��¼");
		printf("\n\t\t\t   ��ʾ�����û�");
		printf("\n\t\t\t   ��ʾ�����û�");
		printf("\n\t\t\t   �����û�����");
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
			if (userlogin())
			{
				edituser(currentusername);
			}
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			if (adminlogin())
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
	char choice = -1;
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
#if 0 //������
	//login();
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
	//promptregisteruser();
	//promptregisteruser();
	edituser("u1");
	displayallusers();
	strcpy(currentusername, "u1");
#endif
	while (choice != 0)
	{
		printf("\n\t �û�����");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ע��");
		printf("\n\t 2. ��¼");
		printf("\n\t\t   ��ͨ�û���¼�����޸��Լ��Ļ�����Ϣ��");
		printf("\n\t\t   ����Ա��¼");
		printf("\n\t\t\t   ��ʾ�����û�");
		printf("\n\t\t\t   ��ʾ�����û�");
		printf("\n\t\t\t   �����û�����");
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
			promptregisteruser();
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