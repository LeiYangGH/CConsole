//C���Կγ���ƣ���c�������һ��������ϵͳ������д����Ҫ��:
//������Ϣ�������֤�š��������Ա����䡢ѧ����סַ���绰�ȣ����֤�Ų��ظ�����
//�����һ��������ϵͳ����ϵͳ�������¹��ܣ�
//1. ������Ϣ¼�빦��(������Ϣ���ļ����棬�����ڵ�����ֱ�Ӳ��Ҳ��򿪸��ļ���
//	2��������Ϣ�������
//	3������������
//	4�������������ѯ
//	5��������Ϣɾ��
//	6��������Ϣ�޸�

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_STU "stu.txt"
#define MAX_STRLEN 20
typedef struct student
{
	char snum[20];
	char name[20];
	char birthday[20];
	int chinese;
	int math;
	int english;
	int total;
}student;

student allstudents[100];
int allstudentscount = 0;

float averagechinese, averagemath, averageenglish;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}


//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}


void displaystudent(student stu)
{
	printf("%s\t%s\t%s\t%d\t%d\t%d\n", stu.snum, stu.name, stu.birthday, stu.chinese, stu.math, stu.english);
}

void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��Ϣ����\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��student
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.snum, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			strcpy(stu.birthday, part);
			break;
		case 4:
			stu.math = toint(part);
			break;
		case 5:
			stu.english = toint(part);
			break;
		case 6:
			stu.chinese = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return stu;
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
	}
	else
	{
		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_STU);
	}
}

//qsort�ǿ�������Ҫ������д��������total����
int cmpfunc(const void * b, const void * a)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sortstudentsbytotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = allstudents[i].chinese + allstudents[i].math + allstudents[i].english;
	}
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortstudentsbytotalanddisplay()
{
	int i;
	sortstudentsbytotal();
	printf("��ÿ��ѧ������ƽ���ɼ����������\r\n");
	displayallstudents();
}

//���ݱ�Ų�����������
int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].snum, no))
			return i;
	}
	return -1;//û�ҵ�
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
		fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%d\n", stu.snum, stu.name, stu.birthday, stu.math, stu.english, stu.chinese);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void editstudent(char no[50])
{
	int i;
	char pwd[20] = "";
	i = getstudentidexbyno(no);
	if (i >= 0)
	{
		printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
		scanf("%d%d%d", &allstudents[i].chinese, &allstudents[i].math, &allstudents[i].english);
		writeallstudents();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧѧ�ŵ�ѧ����\r\n");
	}
}

void prompteditstudent()
{
	char no[50];
	printf("������Ҫ�޸ĵ�ѧ��:");
	scanf("%s", &no);
	editstudent(no);
}

void addstudent(char no[50], char name[], char birthday[], int chinese, int math, int english)
{
	student stu;
	strcpy(stu.snum, no);
	strcpy(stu.name, name);
	strcpy(stu.birthday, birthday);
	stu.chinese = chinese;
	stu.math = math;
	stu.english = english;
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

void promptaddstudent()
{
	char no[50];
	char name[MAX_STRLEN] = "";
	char birthday[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n������ѧ�š������������գ����ǲ����ո���ַ��������ո����\n");
	scanf("%s%s%s", no, name, birthday);
	printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, birthday, chinese, math, english);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}

void promptaddallstudent()
{
	int i, count;
	char no[50];
	char name[MAX_STRLEN] = "";
	char birthday[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n������Ҫ�������λѧ����Ϣ(1-10):");
	scanf("%d", &count);
	allstudentscount = 0;
	for (i = 0; i < count; i++)
	{
		promptaddstudent();
	}
}

void promptaddallorreadstudent()
{
	char choice = -1;
	fseek(stdin, 0, SEEK_END);
	printf("��ѡ���ֶ�����(h)�����ļ�(r)�����Ƿ���(q)��");
	choice = getchar();
	if (choice == 'q')
		return;
	if (allstudentscount > 0)
	{
		printf("\nע�⣺Ŀǰ�Ѿ���%dλѧ����Ϣ�����¶���򴴽��Ḳ��ԭ���ļ�¼��");
	}
	if (choice == 'h')
		promptaddallstudent();
	else if (choice == 'r')
		readallstudents();
}

void removestudent(char no[20])
{
	int i;
	int index;
	index = getstudentidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allstudentscount - 1; i++)
			allstudents[i] = allstudents[i + 1];
		allstudentscount--;
		writeallstudents();
		printf("ɾ����ϣ�ʣ��%d����\r\n", allstudentscount);
	}
	else
	{
		printf("û�ҵ���Ӧѧ�ŵ�ѧ����\r\n");
	}

}

void promptremovestudent()
{
	char no[20];
	printf("������Ҫɾ����ѧ��:");
	scanf("%s", no);
	removestudent(no);
}

//��������
void searcbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}
//�û����벢��������
void promptsearchbyname()
{
	char name[20];
	printf("����������:");
	scanf("%s", name);
	searcbyname(name);
}

int main()
{
	char choice = -1;
#if 0//�����ã�if���ɾ��
	readallstudents();
	//addstudent("05", "n5", "20170605", 41, 92, 93);
	//addstudent("06", "n6", "20170606", 46, 96, 96);

	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	promptaddallstudent();
	displayallstudents();
	//promptsearchbyname();
	//sortstudentsbytotal();
	//prompteditstudent();
	//promptremovestudent();
	//displayallstudents();


	system("pause");

#endif
	readallstudents();
	while (choice != 'g')
	{
		printf("\n\t ѧ����Ϣ����ϵͳ");
		printf("\n\t 0---ѧ����Ϣ�Ĵ���");
		printf("\n\t 1---ѧ����Ϣ������");
		printf("\n\t 2---ѧ����Ϣ������");
		printf("\n\t 3---ѧ����Ϣ��ɾ��");
		printf("\n\t 4---ѧ����Ϣ���޸�");
		printf("\n\t 5---ѧ����Ϣ�Ĳ���");
		printf("\n\t 6---ѧ����Ϣ�����");
		printf("\n\t 7---�˳�\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n��ѡ���� 0\n");
			promptaddallorreadstudent();
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			sortstudentsbytotalanddisplay();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaddstudent();
			break;
		case '3':
			printf("\n\n��ѡ���� c\n");
			promptremovestudent();
			break;
		case '4':
			printf("\n\n��ѡ���� d\n");
			prompteditstudent();
			break;
		case '5':
			printf("\n\n��ѡ���� e\n");
			promptsearchbyname();
			break;
		case '6':
			printf("\n\n��ѡ���� f\n");
			displayallstudents();
			break;
		case '7':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
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

