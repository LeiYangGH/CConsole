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
	char address[20];//����
	float price;//����
	int quantity;//���
	int leastleft;//������Ϳ����ֵ
	int leastout;//������Ϳ����ֵ
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

log alllogs[10];
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
	printf("%s\t%s\t%s\t%.1f\t%d\t%d\t%d\n",
		w.wid, w.name, w.address, w.price, w.quantity, w.leastleft, w.leastout);
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

//��ʾ���п�治����Ʒ
void displaylowleftwares()
{
	int i;
	printf("��治����Ʒ��Ϣ����\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		if (allwares[i].quantity < allwares[i].leastleft)
			displayware(allwares[i]);
	}
	printf("--------------------------------------------\r\n");
}

int getsoldquantity(char wid[])
{
	int i, sum = 0;
	for (i = 0; i < alllogscount; i++)
	{
		if (alllogs[i].paid)
			sum += alllogs[i].quantity;
	}
	return sum;
}

//��ʾ��������������Ʒ
void displaylowoutwares()
{
	int i;
	printf("����������Ʒ��Ϣ����\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		if (getsoldquantity(allwares[i].wid) < allwares[i].leastout)
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
			strcpy(w.address, part);
			break;
		case 4:
			w.price = tofloat(part);
			break;
		case 5:
			w.quantity = toint(part);
			break;
		case 6:
			w.leastleft = toint(part);
			break;
		case 7:
			w.leastout = toint(part);
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
		fprintf(fp, "%s %s %s %.1f %d %d %d\n",
			w.wid, w.name, w.address, w.price, w.quantity, w.leastleft, w.leastout);
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
void addware(char wid[20], char wname[], char address[],
	float price, int quantity, int leastleft, int leastout)
{
	ware w;
	strcpy(w.wid, wid);
	strcpy(w.name, wname);
	strcpy(w.address, address);
	w.price = price;
	w.quantity = quantity;
	w.leastleft = leastleft;
	w.leastout = leastout;
	allwares[allwarescount++] = w;
	writeallwares();
}

//�Ƿ��Ѿ�������ͬ��Ʒ
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
	char address[20];//����
	float price;//����
	int quantity;//���
	int leastleft;//������Ϳ����ֵ
	int leastout;//������Ϳ����ֵ
	printf("\n��������Ʒʶ����:\n");
	scanf("%s", wid);
	if (iswarewidexists(wid))
	{
		printf("ʶ����%s�Ѿ����ڣ������ظ������Ʒ!", wid);
		return;
	}
	printf("\n��������Ʒ���ơ����أ����ǲ����ո���ַ��������ո����\n");
	scanf("%s%s", wname, address);
	printf("\n���ۣ������򸡵���������桢���������޺��������ޣ��������������ո����\n");
	scanf("%f%d%d%d", &price, &quantity, &leastleft, &leastout);
	addware(wid, wname, address, price, quantity, leastleft, leastout);
	printf("��ɵ�%d����Ʒ¼��!\r\n", allwarescount);
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
	int i;
	char choice;
	log l;
	FILE *fp;
	printf("������%s׷�ӹ����¼��ע������ڳ������ǰһ����׷�ӣ�������׷�ӻ����ظ���¼��\n��y������������ȡ����", FILE_LOG);
	fseek(stdin, 0, SEEK_END);
	choice = getchar();
	if (choice != 'y')
	{
		printf("��ȡ��!");
		return;
	}
	fp = fopen(FILE_LOG, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_LOG);
		getchar();
		exit(1);
	}
	for (i = 0; i < allwarescount; i++)
	{
		l = alllogs[i];
		fprintf(fp, "%s %s %s %.1f %d %d %d\n",
			l.uname, l.wid, l.quantity, l.paid);
	}
	fclose(fp);
	printf("�ѱ����¼����Ʒ�ļ���");
}

void addlog(char uname[], char wid[], int quantity, int paid)
{
	log l;
	strcpy(l.uname, uname);
	strcpy(l.wid, wid);
	l.quantity = quantity;
	l.paid = paid;
	alllogs[alllogscount++] = l;
}

//�ӹ��ﳵ��log���
void addtocart(char uname[], char wid[], int quantity)
{
	int i, found = 0;//found:�������ߵĹ��ﳵ������ͬ��Ʒ����ֻ������
	for (i = alllogscount - 1; i >= 0; i--)
		if (streq(alllogs[i].uname, uname)
			&& streq(alllogs[i].wid, wid)
			&& alllogs[i].paid == 0)
		{
			alllogs[i].quantity += quantity;
			found = 1;
			break;
		}
	if (!found)//û���ҵ����������Ʒ
	{
		addlog(uname, wid, quantity, 0);
	}
}

//�۳���棬��治���򷵻�0
int deductwareleft(char wid[], int quantity)
{
	int index = getwareidexbywid(wid);
	if (index < 0)//���������е�����
	{
		printf("û�ҵ�ʶ����Ϊ%d����Ʒ��\n", wid);
		return 0;
	}
	if (allwares[index].quantity >= quantity)
	{
		allwares[index].quantity -= quantity;
		return 1;
	}
	else
	{
		printf("��Ʒ%s���Ϊ%d����治�㣡\n", allwares[index].name, allwares[index].quantity);
		return 0;
	}
}

void promptaddtocart(char uname[])
{
	char wid[20];
	int windex, quantity;
	printf("�𾴵Ŀͻ�%s����������빺�ﳵ����Ʒʶ����:", uname);
	scanf("%s", wid);
	windex = getwareidexbywid(wid);
	if (windex < 0)
	{
		printf("�𾴵Ŀͻ�%s�����������Ʒʶ�����Ҳ�����������������룬лл��", uname);
		return;
	}
	printf("�𾴵Ŀͻ�%s��������Ҫ�����%s��������������:", uname, allwares[windex].name);
	scanf("%d", &quantity);
	if (deductwareleft(wid, quantity))
	{
		printf("�𾴵Ŀͻ�%s����Ҫ����Ĳ�Ʒ%s����%d�ɹ���ӵ����ﳵ!", uname, allwares[windex].name, quantity);
	}
}


int recharge(char uname[], int money)
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(allusers[i].name, uname))
		{
			allusers[i].money += money;
			printf("�𾴵Ŀͻ�%s����Ϊ����ֵ�ɹ��������Ϊ%dԪ��\n", uname, allusers[i].money);
			return 1;
		}
	}
	return 0;
}

//��ֵ���ٶ�unameһ����������
void promptrecharge()
{
	int i, money;
	printf("�𾴵Ŀͻ�%s�����ã�������Ҫ��ֵ�Ľ���������:", currentusername);
	scanf("%d", &money);
	if (recharge(currentusername, money))
		printf("�𾴵Ŀͻ�%s����Ϊ����ֵ�ɹ��������Ϊ%dԪ��\n", currentusername, allusers[i].money);
}



//�۳��������򷵻�0
int deductusermoney(char uname[], float money)
{
	int index = getuseridexbyuname(uname);
	if (index < 0)//���������е�����
	{
		printf("û�ҵ��û���Ϊ%d�������ߣ�\n", uname);
		return 0;
	}
	if (allusers[index].money >= money)
	{
		allusers[index].money -= money;
		return 1;
	}
	else
	{
		printf("�𾴵Ŀͻ�%s����Ǹ�������Ϊ%.1f�����㣡\n", allusers[index].name, allusers[index].money);
		return 0;
	}
}

int getlatestlogidbyuserwareandpaid(char uname[], char wid[], int paid)
{
	int i;
	for (i = alllogscount - 1; i >= 0; i--)
		if (streq(alllogs[i].uname, uname)
			&& streq(alllogs[i].wid, wid)
			&& alllogs[i].paid == paid)
		{
			return i;
		}
	return -1;
}

float showcarttouser(char uname[])
{
	int i, windex;
	float multiple, total = 0;

	printf("�𾴵Ŀͻ�%s�����Ĺ��ﳵ��Ʒ��Ϣ����\r\n", uname);
	printf("��Ʒ\t����\t����\t�ܼ�\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < alllogscount; i++)
		if (streq(alllogs[i].uname, uname)
			&& alllogs[i].paid == 0)
		{
			windex = getwareidexbywid(alllogs[i].wid);
			ware w = allwares[windex];
			multiple = w.price* alllogs[i].quantity;
			total += multiple;
			printf("%s\t%.1f\t%d\t%.1f\n��\n",
				w.name, w.price, alllogs[i].quantity, multiple);
		}
	printf("--------------------------------------------\n");
	printf("��Ӧ����%.1f\n", total);
	return total;
}

//֧������log�����е�ǰ�û���δ֧����ȫ����Ϊ֧��
void pay(char uname[])
{
	int i, found = 0;//found:�������ߵĹ��ﳵ���У�δ֧������Ʒ
	float total = showcarttouser(uname);
	if (deductusermoney(uname, total))
	{
		//������ز��Ҷ������㷨�Ż���
		//��Ϊÿ�ζ�Ҫ���ﳵ�����Ʒȫ��֧����
		//���һ���������Ѿ�֧���ľͲ����ټ����ˣ�
		//�˴�û�Ż�
		for (i = alllogscount - 1; i >= 0; i--)
			if (streq(alllogs[i].uname, uname)
				&& alllogs[i].paid == 0)
			{
				alllogs[i].paid = 1;
			}
		printf("�𾴵Ŀͻ�%s������ɹ�����ӭ���´ι��٣�\n", uname);
	}
}

//���˻������������ű���log���˻�������������һ�ι��������
int maxquantitycanreturn(char uname[], char wid[])
{
	int index = getlatestlogidbyuserwareandpaid(uname, wid, 1);
	if (index >= 0)
		return alllogs[index].quantity;
	else
		return 0;
}

int returnware(char uname[], char wid[], int quantity)
{
	int i;
	log l;
	int windex = getwareidexbywid(wid);
	if (quantity > maxquantitycanreturn(uname, wid))
	{
		printf("�𾴵Ŀͻ�%s����Ҫ�˻�����Ʒ�����������һ�ι�����������˻�ʧ�ܣ�\n", uname);
		return 0;
	}
	//�˻��ǹ�����������������Ϳ�涼��ȥ����
	deductusermoney(uname, -allwares[windex].price*quantity);
	deductwareleft(wid, -quantity);
	//�˻�����Ҳ������ʷ��¼����ΪӰ���û���
	addlog(uname, wid, -quantity, 1);
	return 1;
}

void promptreturnware(char uname[])
{
	char wid[20];
	int windex, quantity;
	printf("�𾴵Ŀͻ�%s���������˻�����Ʒʶ����:", uname);
	scanf("%s", wid);
	windex = getwareidexbywid(wid);
	if (windex < 0)
	{
		printf("�𾴵Ŀͻ�%s�����������Ʒʶ�����Ҳ�����������������룬лл��", uname);
		return;
	}
	printf("�𾴵Ŀͻ�%s��������Ҫ�˻���%s��������������:", uname, allwares[windex].name);
	scanf("%d", &quantity);
	if (returnware(uname, wid, quantity))
	{
		printf("�𾴵Ŀͻ�%s���˻��ɹ��������Ŭ������õ���Ʒ��������֧��!", uname);
	}
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
			displayallwares();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			promptsearchbyname();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			promptaddware();
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			prompteditware();
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			promptremoveware();
			break;
		case 'a':
			printf("\n\n��ѡ���� a\n");
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			displaylowleftwares();
			displaylowoutwares();
			break;
		case 'b':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptaddtocart(currentusername);
			break;
		case 'c':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			pay(currentusername);
			break;
		case 'd':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptrecharge();
			break;
		case 'e':
			if (!iscurrentuserconsumer())
			{
				printf("��ǰ�û�%s���������ߣ�û��Ȩ�޲���!", currentusername);
				break;
			}
			promptreturnware(currentusername);
			break;
		case 'f':
			if (!iscurrentuseradmin())
			{
				printf("��ǰ�û�%s���ǹ���Ա��û��Ȩ�޲���!", currentusername);
				break;
			}
			writealllogs();
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