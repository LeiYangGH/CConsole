#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
//#define FILE_INPUT "sample.txt"
#define FILE_BEST "best.txt"
#define FILE_SCORES "scores.txt"
#define FILE_ANALYSIS "analysis.txt"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define COURSES_COUNT 5

char best[QUESTIONS_COUNT];

typedef struct student
{
	char name[MAX_STRLEN];
	int score[COURSES_COUNT];
	int total;
	float average;
}student;
student allstudents[100];
int allstudentscount = 0;

#define TEST 0
int ascending = 1;
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
	printf("%s\t\%d\t\%d\t\%d\t\%d\t\%d\t%.1f\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average);
}

void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void displayonecourseorder()
{
	int i;
	printf("��%d��Ŀ��������\r\n", cmpcourseindex + 1);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		printf("\r\n");
		student stu = allstudents[i];
		printf("%s\t\%d\n", stu.name,
			stu.score[cmpcourseindex]);
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
			strcpy(stu.name, part);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			stu.score[index - 2] = toint(part);
			break;

		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			allstudents[i].total += allstudents[i].score[j];
		}
		allstudents[i].average = allstudents[i].total / (float)COURSES_COUNT;
	}
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
	calctotalandave();
}



int cmptotalfunc(const void * a, const void * b)
{
	return (((student*)a)->total - ((student*)b)->total)*ascending;
}
void sorttotal()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmptotalfunc);
}


int cmponecoursefunc(const void * a, const void * b)
{
	return (((student*)a)->score[cmpcourseindex] - ((student*)b)->score[cmpcourseindex])*ascending;
}
void sortonecourse()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmponecoursefunc);
}

void promptaskascending()
{
	int asc;
	printf("\n����������(1)���ǽ���(-1)���Իس�������");
	scanf("%d", &asc);
	ascending = asc;
}

void promptaskcmpcourseindex()
{
	int courseid;
	printf("\n������Ҫ����Ŀγ����(1~5)���Իس�������");
	scanf("%d", &courseid);
	cmpcourseindex = courseid - 1;
}


int main()
{
#if TEST
	readallstudents();
	//sorttotal();
	//displayallstudents();
	ascending = -1;
	cmpcourseindex = 4;
	sortonecourse();
	displayonecourseorder();
#else

	int choice = -1;
	printf("\n��ʼ���ļ�...\n");
	readallstudents();
	printf("\n���ļ�������\n");

	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ�����ͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ѧ���ܷ����������");
		printf("\n\t 2. ��ĳ�ſγ̷������������");
		//printf("\n\t 3. ��ĳ�ſγ�ƽ�������������");
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
			promptaskascending();
			sorttotal();
			displayallstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaskcmpcourseindex();
			promptaskascending();
			sortonecourse();
			displayonecourseorder();
			break;
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			//	sortanddisplaybytotal();
			//	break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}



#endif
	system("pause");
	return 0;
}
