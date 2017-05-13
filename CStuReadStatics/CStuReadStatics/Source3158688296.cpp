#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5
#define GRADES_COUNT 5

typedef struct student
{
	char  no[11];           //ѧ��
	char  name[20];    //����
	int  score;              //�ɼ�
}student;
student allstudents[100];
int allstudentscount = 0;


#define TEST 1
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



int cmpstuscorefunc(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}
void sortstudentsbyscore()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuscorefunc);
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
	if (!login())
		return 0;

	readallstudents();
	//sorttotal();
	displayallstudents();
	//ascending = -1;
	//cmpcourseindex = 4;
	//sortonecourse();
	//displayonecourseorder();
#else

	int choice = -1;
	printf("\n��ʼ���ļ�...\n");
	readallstudents();
	printf("\n���ļ�������\n");

	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ�����ͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �ۺϳɼ����μ������");
		printf("\n\t 2. �γ̷ֶ��������");
		printf("\n\t 3. ������в�����");
		printf("\n\t 4. ���ѧ���ɼ�");
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
			sortstuave();
			displayallstudents();
			writestudentsaveorder();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			countbygradesforallcourses();
			writeandprintgradescount();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayallbelow60();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptaddstudent();
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
