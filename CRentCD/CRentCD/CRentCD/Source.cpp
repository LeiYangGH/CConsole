#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//conio.h���������˵����ã����˵���������ѡ��ʱ�������ԣ�����һ�㣬����㲻Ҫ���ͷ�ļ������˵��ĳ�scanfҲ����
#include <conio.h> 
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define MAX_COUNT 20 //�ݶ����20�����ݣ�����
#define MAX_STRLEN 20 //�ַ��������
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
	int isreturned;
}rentcd;
typedef struct customer
{
	int no;
	char name[MAX_STRLEN];
	int vip;
}customer;
//�������ݶ��洢��������3���ṹ����������
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
//display all��ʾȫ��������displayvcd��ʾ���У���ͬ
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
		if (allrentcds[i].isreturned == 0)
			displayrentcd(allrentcds[i]);
	}
}
//��ӵ���
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
	cd.isrent = 0;
	allvcds[allvcdscount++] = cd;
}

//Ҫ���û����룬��������addvcd����ͬ���ֿ�����������Ϊ�˲��Է���
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
		//����vip�����и�Ĭ��ֵ�����û��黹��ʱ���Զ�����vip������+1�ȣ�ʵ��������vip��̬����
		printf("\n\n������ͻ�vip����Ȼ��(��ʱֻ��¼�����֣���ûʵ���书��):");
		scanf("%d", &vip);
		addcustomer(no, name, vip);
		printf("\n�ͻ�%s��Ϣ��ӳɹ�!\n", name);
	}
}

//ͨ�����Ʋ���cd������������vcd��ָ�룬��ͬ
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

//����һ�����ҵ�
void findcunamebycdname(char *cdname, char *cuname)
{
	int i;
	for (i = 0; i < allrentcdscount; i++)
	{
		if (streq(allrentcds[i].cdname, cdname))
		{
			strcpy(cuname, allrentcds[i].cuname);
			break;
		}
	}
}

//����
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
			rcd.isreturned = 0;
			allrentcds[allrentcdscount++] = rcd;
			cd->isrent = 1;
			printf("���ɹ���\n");
		}
	}
}

//���벢����
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

//�黹
void addreturn(char *cdname)
{
	int i;
	vcd *cd;
	customer *cu;
	rentcd rcd;
	//Ҳ����������cd������黹��ģ����ʵɨ���룬������ҵ�������׳̶Ȼ���ͨ��cd name��Щ
	findvcdbyname(cdname, &cd);
	if (cd != NULL)
	{
		if (cd->isrent)
		{
			for (i = 0; i < allrentcdscount; i++)
			{
				rcd = allrentcds[i];
				if (streq(rcd.cdname, cdname))
				{
					findcustomerbyname(allrentcds[i].cuname, &cu);
					strcpy(allrentcds[i].cuname, "");
					allrentcds[i].cuno = 0;
					printf("���Ϊ��%d����ΪVIP������������������Լ�����ã� %dԪ \n", allrentcds[i].days, cu->vip);//��������
					allrentcds[i].days = 0;
					//������ֻ��Ҫ�����������ֵҲ����
					allrentcds[i].isreturned = 1;
					break;
				}
			}
			cd->isrent = 0;
			printf("�黹�ɹ���\n");
		}
		else
		{
			printf("CD %s ��û���⣬���ܹ黹��\n", cdname);//��Ӧ�÷������������ߵ���һ��
		}
	}
}

//���벢�黹
void inputreturn()
{
	char  cdname[MAX_STRLEN] = "";
	printf("������黹��CD���ƣ����ݱ�Ź黹�Ĺ���������Լ����ռӣ�:");
	scanf("%s", &cdname);
	addreturn(cdname);
}

//���ĳ�ͻ��ĳ���
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

//����ͻ�����ʾ�����
void inputanddisplayonecustomerrentcds()
{
	char name[MAX_STRLEN] = "";
	printf("\n������Ҫ��ѯ�������Ŀͻ�����:");
	scanf("%s", name);
	displayonecustomerrentcds(name);
}

int main()
{
	int choice = -1;

	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	//addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");

#if DEV
	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");

	addcustomer(1, "cust1", 1);
	addcustomer(2, "cust2", 2);

	addrent("cd1", "cust1", 2);
	addrent("cd2", "cust1", 3);
	//addrent("cd3", "cust2", 7);
	//addrent("cd1", "cust2", 7);//dup 

	displayallrentcds();
	displayonecustomerrentcds("cust1");
	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");
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
		printf("\n\t 8. �黹CD");
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
		case '8':
			printf("\n\n��ѡ���� 8\n");
			inputreturn();
			break;
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