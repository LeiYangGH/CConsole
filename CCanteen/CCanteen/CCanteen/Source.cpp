#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define MAX_COUNT 20 //�ݶ����20�����ݣ�����
#define MAX_STRLEN 20 //�ַ��������
#define FORMAT_STU "%d\t%s\t%s\n"
#define MEMBERS_STU stu.no, stu.name, stu.sex
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\n"
#define MEMBERS_CU cu.no, cu.name
#define LINE  "\n------------------------\n"

typedef struct student
{
	int no;
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
}student;
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
}customer;
//�������ݶ��洢��������3���ṹ����������
student allstudents[MAX_COUNT];
int allstudentscount = 0;

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

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
}
//display all��ʾȫ��������displaystudent��ʾ���У���ͬ
void displayallstudents()
{
	int i;
	printf("����ѧ���������\n");
	printf("���\t����\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
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
	printf("����ѧ������������\n");
	printf("ѧ��\t�ͻ�\t����\n");
	printf(LINE);
	for (i = 0; i < allrentcdscount; i++)
	{
		if (allrentcds[i].isreturned == 0)
			displayrentcd(allrentcds[i]);
	}
}
//��ӵ���
void addstudent(int no, char *name, char *sex)
{
	student stu;
	stu.no = no;
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
}

//Ҫ���û����룬��������addstudent����ͬ���ֿ�����������Ϊ�˲��Է���
void inputstudents()
{
	//int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������ѧ�����(������0����):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ѧ�����ơ��Ա𣬶��ŷָ����س�����:");
		scanf("%s%s", name, sex);
		addstudent(no, name, sex);
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

void addcustomer(int no, char *name)
{
	int i;
	customer cu;
	cu.no = no;
	strcpy(cu.name, name);
	allcustomers[allcustomerscount++] = cu;
}

void inputcustomers()
{
	int i, no;
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
		addcustomer(no, name);
		printf("\n�ͻ�%s��Ϣ��ӳɹ�!\n", name);
	}
}

//ͨ�����Ʋ���stu������������student��ָ�룬��ͬ
void findstudentbyname(char *cdname, student **stu)
{
	int i;
	int found = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, cdname))
		{
			*stu = &allstudents[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s��ѧ��\n", cdname);
		*stu = NULL;
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






int main()
{
	int choice = -1;

	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	addstudent(1, "cd1", "F");
	addstudent(2, "cd2", "F");
	addstudent(3, "cd3", "M");

	addcustomer(1, "cust1");
	addcustomer(2, "cust2");


	//addreturn("cd3");
	//displayonecustomerrentcds("cust1");

#if DEV
	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	addstudent(1, "cd1");
	addstudent(2, "cd2");
	addstudent(3, "cd3");

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
		printf("\n\t ѧ��ѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��ѧ����Ϣ");
		printf("\n\t 2. �鿴����ѧ��");
		printf("\n\t 3. ¼��ͻ���Ϣ");
		printf("\n\t 4. �鿴���пͻ�");
		printf("\n\t 5. ����ѧ��");
		printf("\n\t 6. �鿴����ѧ���������");
		printf("\n\t 7. �鿴ĳλ�ͻ�ѧ���������");
		printf("\n\t 8. �黹ѧ��");
		printf("\n\n  ��ѡ��: ");
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
			inputstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			inputcustomers();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallcustomers();
			break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	inputrent();
			//	break;
			//case '6':
			//	printf("\n\n��ѡ���� 6\n");
			//	displayallrentcds();
			break;
			//case '7':
			//	printf("\n\n��ѡ���� 7\n");
			//	inputanddisplayonecustomerrentcds();
			//	break;
			//case '8':
			//	printf("\n\n��ѡ���� 8\n");
			//	inputreturn();
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}