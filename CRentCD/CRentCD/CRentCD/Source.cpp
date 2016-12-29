#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define MAX_COUNT 20
#define MAX_STRLEN 20
#define FORMAT_CD "%d\t%s\n"
#define MEMBERS_CD cd.no, cd.name
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\t%d\n"
#define MEMBERS_CU cu.no, cu.name, cu.vip
#define LINE  "\n------------------------\n"


typedef struct vcd
{
	int no;
	char name[MAX_STRLEN];
	int isrent;
}vcd;
typedef struct rentcd
{
	int cdno;
	char cdname[MAX_STRLEN];
	int cuno;
	char cuname[MAX_STRLEN];
	int days;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
	int vip;
}customer;

vcd allvcds[MAX_COUNT];
int allvcdscount = 0;

rentcd allrentcds[MAX_COUNT];
int allrentcdscount = 0;

customer allcustomers[MAX_COUNT];
int allcustomerscount = 0;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displayvcd(vcd cd)
{
	printf(FORMAT_CD, MEMBERS_CD);
}
void displayallvcds()
{
	int i;
	printf("����CD�������\n");
	printf("���\t����\n");
	printf(LINE);
	for (i = 0; i < allvcdscount; i++)
	{
		displayvcd(allvcds[i]);
	}
	printf(LINE);
}
//////////0
void displayrentcd(rentcd rcd)
{
	printf(FORMAT_RCD, MEMBERS_RCD);
}



void displayallrentcds()
{
	int i;
	printf("����CD����������\n");
	printf("CD\t�ͻ�\t����\n");
	printf(LINE);
	for (i = 0; i < allrentcdscount; i++)
	{
		displayrentcd(allrentcds[i]);
	}
}
///////////1
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
	cd.isrent = 0;
	allvcds[allvcdscount++] = cd;
}

void inputvcds()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������CD���(������0����):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������CD����:");
		scanf("%s", name);
		addvcd(no, name);
		printf("\nCD%s��Ϣ��ӳɹ�!\n", name);
	}
}


//////add cus start/////


void displaycustomer(customer cu)
{
	printf(FORMAT_CU, MEMBERS_CU);
	printf("\n");
}
void displayallcustomers()
{
	int i;
	printf("���пͻ�����\n");
	printf("ѧ��\t����\n");
	printf(LINE);
	for (i = 0; i < allcustomerscount; i++)
	{
		displaycustomer(allcustomers[i]);
	}
	printf(LINE);
}

void addcustomer(int no, char *name, int vip)
{
	int i;
	customer cu;
	cu.no = no;
	strcpy(cu.name, name);
	cu.vip = vip;//Ĭ��vip
	allcustomers[allcustomerscount++] = cu;
}

void inputcustomers()
{
	int i, no, vip;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������ͻ���ţ����ظ���Ȼ��(0����):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ͻ�����:");
		scanf("%s", name);
		printf("\n\n������ͻ�vip����Ȼ��(��ʱֻ��¼�����֣���ûʵ���书��):");
		scanf("%d", &vip);
		addcustomer(no, name, vip);
		printf("\n�ͻ�%s��Ϣ��ӳɹ�!\n", name);
	}
}

void findvcdbyname(char *cdname, vcd **cd)
{
	int i;
	int found = 0;
	for (i = 0; i < allvcdscount; i++)
	{
		if (streq(allvcds[i].name, cdname))
		{
			*cd = &allvcds[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s��CD\n", cdname);
		*cd = NULL;
	}
}

void findcustomerbyname(char *cuname, customer **cu)
{
	int i;
	int found = 0;
	for (i = 0; i < allcustomerscount; i++)
	{
		if (streq(allcustomers[i].name, cuname))
		{
			*cu = &allcustomers[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s�Ŀͻ�\n", cuname);
		*cu = NULL;
	}
}

void addrent(char *cdname, char *cuname, int days)
{
	vcd *cd;
	customer *cu;
	rentcd rcd;
	findvcdbyname(cdname, &cd);
	findcustomerbyname(cuname, &cu);
	if (cd != NULL && cu != NULL)
	{
		if (cd->isrent)
		{
			printf("CD %s �Ѿ����⣬�����ٳ��⣡\n", cdname);
		}
		else
		{
			rcd.cdno = cd->no;
			strcpy(rcd.cdname, cdname);
			rcd.cuno = cu->no;
			strcpy(rcd.cuname, cuname);
			rcd.days = days;
			allrentcds[allrentcdscount++] = rcd;
			cd->isrent = 1;
			printf("���ɹ���\n");
		}
	}
}

void inputrent()
{
	char  cdname[MAX_STRLEN] = "";
	char  cuname[MAX_STRLEN] = "";
	int days;
	/*printf("���������Ҫ�����CD����:");
	scanf("%s", &cdname);
	printf("������Ҫ�����ͻ�������:");
	scanf("%s", &cuname);
	printf("�������������(��ʱ������������������Ըĳ��Զ������ڼ���):");
	scanf("%d", &days);*/
	//���������ĸ����ã�
	printf("���������Ҫ�����CD���ơ��ͻ����ơ���������(��ʱ������������������Ըĳ��Զ������ڼ���)���м�ո�ָ����س�����:");
	scanf("%s%s%d", &cdname, &cuname, &days);
	addrent(cdname, cuname, days);
}

void displayonecustomerrentcds(char *name)
{
	int i, pay = 0;
	rentcd rcd;
	customer *cu;
	findcustomerbyname(name, &cu);
	if (cu != NULL)
	{
		printf("�ͻ� %s ����CD����������\n", name);
		printf("CD\t�ͻ�\t����\n");
		printf(LINE);
		for (i = 0; i < allrentcdscount; i++)
		{
			rcd = allrentcds[i];
			if (streq(rcd.cuname, name))
			{
				displayrentcd(rcd);
				pay += rcd.days;
			}
		}
		printf("�����%d\n", pay);
	}
}

void inputanddisplayonecustomerrentcds()
{
	char name[MAX_STRLEN] = "";
	printf("\n������Ҫ��ѯ�������Ŀͻ�����:");
	scanf("%s", name);
	displayonecustomerrentcds(name);
}

//////add cus end/////
int main()
{
	int choice = -1;
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
#if DEV

	//strcpy(curstuname, "ly");
	displayallvcds();


	displayallcustomers();
	//findvcdbyname(curstuname, &curstu);
	//selectonecd(curstu, 1);
	//selectonecd(curstu, 2);
	//selectonecd(curstu, 3);
	//selectonecd(curstu, 4);
	//selectonecd(curstu, 5);
	//selectonecd(curstu, 6);
	//findvcdbyname("sm", &cu);
	//selectonecd(cu, 1);
	//selectonecd(cu, 2);
	//selectonecd(cu, 5);
	//displayallstuselcds();
	//sortanddisplayallvcds();
#else
	while (choice != 0)
	{
		printf("\n\t CDѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��CD��Ϣ");
		printf("\n\t 2. �鿴����CD");
		printf("\n\t 3. ¼��ͻ���Ϣ");
		printf("\n\t 4. �鿴���пͻ�");
		printf("\n\t 5. ����CD");
		printf("\n\t 6. �鿴����CD�������");
		printf("\n\t 7. �鿴ĳλ�ͻ�CD�������");
		//printf("\n\t 8. ��������CD�ɼ�");
		//printf("\n\t 9. һ�ź����Ź��β������CD");
		printf("\n\n  ��ѡ��: ");
		choice = getche();
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
			inputvcds();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallvcds();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			inputcustomers();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallcustomers();
			/*printf("�����������������س�����:");
			scanf("%s", curstuname);
			findvcdbyname(curstuname, &curstu);
			printf("��ǰCD������%s\n", curstuname);*/
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			inputrent();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			displayallrentcds();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			inputanddisplayonecustomerrentcds();
			break;
			//case '8':
			//	printf("\n\n��ѡ���� 8\n");
			//	inputallstuscores();
			//	break;
			//case '9':
			//	printf("\n\n��ѡ���� 9\n");
			//	listallnamesbelow60forcou(1);
			//	listallnamesbelow60forcou(3);
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}