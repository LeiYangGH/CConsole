#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"

typedef struct student
{
	char  no[11];           //ѧ��
	char  name[20];    //����
	int  score;              //�ɼ�
}student;
student allstudents[100];
int allstudentscount = 0;


#define TEST 0
int cmpcourseindex;
//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score);
}

void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("ѧ��\t����\t����\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
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
			stu.score = toint(part);
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_INPUT);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		++allstudentscount;
		allstudents[allstudentscount - 1] = getstudentfromline(line);
	}
}

int cmpstuscorefunc(const void * a, const void * b)
{
	return ((student*)a)->score - ((student*)b)->score;
}
void sortstudentsbyscore()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuscorefunc);
}

int cmpstunamefunc(const void * a, const void * b)
{
	return strcmp(((student*)a)->name, ((student*)b)->name);
}
void sortstudentsbyname()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstunamefunc);
}

void displayhighest()
{
	sortstudentsbyscore();
	printf("\n��߷�ѧ��Ϊ\n");
	displaystudent(allstudents[allstudentscount - 1]);
}

int login()
{
	int trytimes = 3;
	char username[20] = "";
	char password[20] = "";
	while (trytimes > 0)
	{
		printf("\n����%d�λ���\n", trytimes--);
		printf("\n�������û���:");
		scanf("%s", &username);
		printf("\n����������:");
		scanf("%s", &password);
		if (strcmp(username, "admin") == 0
			&& strcmp(password, "123456") == 0)
			return 1;
	}
	return 0;
}

int main()
{
#if TEST
	readallstudents();
	//sortstudentsbyscore();
	//sortstudentsbyname();
	displayallstudents();
	displayhighest();
#else
	if (!login())
		return 0;
	int choice = -1;
	printf("\n��ʼ���ļ�...\n");
	readallstudents();
	printf("\n���ļ�������\n");

	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ�����ͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �ɼ�����");
		printf("\n\t 2. ��������");
		printf("\n\t 3. �ɼ���߷�");
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
			sortstudentsbyscore();
			displayallstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			sortstudentsbyname();
			displayallstudents();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayhighest();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
#endif
	system("pause");
	return 0;
}