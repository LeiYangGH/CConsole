#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define MAX_COUNT 20 //�ݶ����20�����ݣ�����
#define MAX_STRLEN 20 //�ַ��������
#define FORMAT_STU "%s\t%s\t%s\r\n" //\r is for write
#define MEMBERS_STU stu.no, stu.name, stu.sex
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_CU "%d\t%s\n"
#define MEMBERS_CU cu.no, cu.name
#define LINE  "\n------------------------\n"
#define FILE_STU "stu.txt"
typedef struct student
{
	char no[MAX_STRLEN];
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
void addstudent(char * no, char *name, char *sex)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
}

//Ҫ���û����룬��������addstudent����ͬ���ֿ�����������Ϊ�˲��Է���
void inputstudents()
{
	//int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������ѧ�����(������q����):");
		scanf("%s", no);
		if (streq(no, "q"))
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

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			strcpy(stu.sex, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void createsamplestudents()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMAT_STU, "01", "smile", "F");
	fprintf(fp, FORMAT_STU, "02", "lukas", "M");
	fprintf(fp, FORMAT_STU, "03", "shawn", "F");
	fprintf(fp, FORMAT_STU, "04", "tony", "M");
	fprintf(fp, FORMAT_STU, "05", "flex", "F");
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽student.txt��\n");
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_STU);
		createsamplestudents();
		fp = fopen(FILE_STU, "r");
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_STU);

}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, FORMAT_STU, MEMBERS_STU);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
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
	//createsamplestudents();
	readallstudents();
	displayallstudents();

#if DEV
	//������Щ�ǲ���ʱ������Եģ�����ɾ��

#else
	while (choice != 0)
	{
		printf("\n\t ѧ��ѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ����ѧ����Ϣ");
		printf("\n\t 2. �鿴����ѧ��");
		/*printf("\n\t 3. ¼��ͻ���Ϣ");
		printf("\n\t 4. �鿴���пͻ�");
		printf("\n\t 5. ����ѧ��");
		printf("\n\t 6. �鿴����ѧ���������");
		printf("\n\t 7. �鿴ĳλ�ͻ�ѧ���������");
		printf("\n\t 8. �黹ѧ��");*/
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
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			//	inputcustomers();
			//	break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			//	displayallcustomers();
			//	break;
				//case '5':
				//	printf("\n\n��ѡ���� 5\n");
				//	inputrent();
				//	break;
				//case '6':
				//	printf("\n\n��ѡ���� 6\n");
				//	displayallrentcds();
				//break;
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