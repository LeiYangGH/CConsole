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

//int cmpfunc(const void * a, const void * b)
//{
//	return ((user*)a)->author - ((user*)b)->author;
//}

void displayallusers()
{
	int i;
	//qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("����%dλ�û���Ϣ����\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
}


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

//int ispassowrdcomplicated(char password[20])
//{
//	return strlen(password) >= 6;
//}

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

//�ǳ�
void logout()
{
	strcpy(currentusername, "");
	printf("�ǳ��ɹ�!");
}


#pragma endregion

#pragma region ware





//
////�޸���Ʒֻ�����޸ļ۸�Ϳ��
//void editware(char wid[50])
//{
//	int i;
//	char pwd[20] = "";
//	i = getwareidexbywid(wid);
//	if (i >= 0)
//	{
//		printf("\n�������µļ۸������򸡵������Ϳ�棨���������ո����\n");
//		scanf("%f%d", &allwares[i].price, &allwares[i].quantity);
//		writeallwares();
//		printf("�޸���ϡ�\r\n");
//	}
//	else
//	{
//		printf("û�ҵ���Ӧʶ�������Ʒ��\r\n");
//	}
//}
//
//void prompteditware()
//{
//	char wid[50];
//	printf("������Ҫ�޸ĵ�ʶ����:");
//	scanf("%s", &wid);
//	editware(wid);
//}

////�����Ʒ
//void addware(char wid[20], char wname[], char address[],
//	float price, int quantity, int leastleft, int leastout)
//{
//	ware w;
//	strcpy(w.wid, wid);
//	strcpy(w.name, wname);
//	strcpy(w.address, address);
//	w.price = price;
//	w.quantity = quantity;
//	w.leastleft = leastleft;
//	w.leastout = leastout;
//	allwares[allwarescount++] = w;
//	writeallwares();
//}


//ͨ�����Ʋ�����Ʒ
//void searchwarebyname(char *name)
//{
//	int i;
//	for (i = 0; i < allwarescount; i++)
//		if (strcmp(name, allwares[i].name) == 0)
//		{
//			displayware(allwares[i]);
//			return;
//		}
//	printf("û�ҵ���Ӧ��Ʒ����Ϣ��\r\n");
//}
////�û��������Ʋ�������Ʒ��Ϣ
//void promptsearchbyname()
//{
//	char name[20];
//	printf("������Ҫ���ҵ���Ʒ����:");
//	scanf("%s", name);
//	searchwarebyname(name);
//}


#pragma endregion




int main()
{
	char choice = -1;

#if 1 //������
	//login();
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
	promptregisteruser();
	//promptregisteruser();
	displayallusers();
	strcpy(currentusername, "u1");
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
		printf("\n\t a---��ʾ��治���������Ʒ");
		printf("\n\t b---�����Ʒ�����ﳵ");
		printf("\n\t c---���ʸ���");
		printf("\n\t d---��ֵ");
		printf("\n\t e---�˻�");
		printf("\n\t f---�ѱ������е����Ѽ�¼׷�ӵ��ļ�");
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
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case 'a':
			printf("\n\n��ѡ���� a\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
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