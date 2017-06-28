#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma region typedef
typedef struct user//�û�
{
	char name[20];//����
	char password[20];//����
	int isadmin;//�Ƿ����Ա
	float money;//���
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

//���븴�Ӷȣ���ʱ�涨����>=6
int ispassowrdcomplicated(char password[20])
{
	return strlen(password) >= 6;
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
 
#if 0 //������
	//login();
	//promptregisteruser(0);
	strcpy(currentusername, "u1");
	addtocart("u1", "006", 2);
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
			promptregisteruser(0);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptregisteruser(1);
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
		case 'b':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case 'c':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case 'd':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case 'e':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			break;
		case 'f':
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