#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5

typedef struct student
{
	char name[MAX_STRLEN];//����
	int score[COURSES_COUNT];//����
	int total;//�ܷ�
	float average;//ƽ��
}student;
student allstudents[100];//����ѧ��
int allstudentscount = 0;//ѧ������

typedef struct course//�γ�
{
	int oldindex;//�γ���input.txt������
	float average;//ƽ����
}course;
course allcourses[COURSES_COUNT];//5�ſγ�


int ascending = 1;//�����ǽ���
int cmpcourseindex;//����Ŀγ��±꣨0��4��
//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}
//��ʾһ��ѧ���ɼ�
void displaystudent(student stu)
{
	printf("\r\n");
	printf("%s\t\%d\t\%d\t\%d\t\%d\t\%d\t%.1f\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average);
}

//��ʾ����ѧ���ɼ�
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
//��ʾһ�ſγ�����
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


//��ʾ���п�Ŀƽ��������
void displayallcoursesaveorder()
{
	int i;
	printf("���п�Ŀƽ������������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{
		printf("\r\n");
		course cou = allcourses[i];
		printf("��%d��\t\%.1f\n", cou.oldindex + 1,
			cou.average);
	}
	printf("\r\n--------------------------------------------\r\n");
}
//��һ�в�ֹ����һ��ѧ��
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");//ͨ��\t���Ų�ֲ�ͬ����
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

//�����ֺܷ�ƽ����
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

//���ļ���ѧ������
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


//�������������ǿ�������qsortҪ��ĸ�ʽ�����ܷ���ѧ��
int cmptotalfunc(const void * a, const void * b)
{
	return (((student*)a)->total - ((student*)b)->total)*ascending;
}
void sorttotal()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmptotalfunc);
}

//��ĳ��Ŀ�����гɼ�
int cmponecoursefunc(const void * a, const void * b)
{
	return (((student*)a)->score[cmpcourseindex] - ((student*)b)->score[cmpcourseindex])*ascending;
}
void sortonecourse()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmponecoursefunc);
}

//����ÿ����Ŀ��ƽ����
void calceachcourseave()
{
	int i, j;
	float sum;
	for (j = 0; j < COURSES_COUNT; j++)
	{
		sum = 0;
		for (i = 0; i < allstudentscount; i++)
		{
			sum += allstudents[i].score[j];
		}
		allcourses[j].oldindex = j;
		allcourses[j].average = sum / (float)COURSES_COUNT;
	}
}

//��Ŀƽ��������
int cmpcoursesavefunc(const void * a, const void * b)
{
	return (((course*)a)->average - ((course*)b)->average)*ascending;
}
void sortcoursesave()
{
	qsort(allcourses, COURSES_COUNT, sizeof(course), cmpcoursesavefunc);
}

//��ʾѡ�������ǽ���
void promptaskascending()
{
	int asc;
	printf("\n����������(1)���ǽ���(-1)���Իس�������");
	scanf("%d", &asc);
	ascending = asc;
}

//��ʾ����Ҫ����Ŀ�Ŀ
void promptaskcmpcourseindex()
{
	int courseid;
	printf("\n������Ҫ����Ŀγ����(1~5)���Իس�������");
	scanf("%d", &courseid);
	cmpcourseindex = courseid - 1;
}


int main()
{
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
		printf("\n\t 3. �����пγ�ƽ�������������");
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
		case '3':
			printf("\n\n��ѡ���� 3\n");
			calceachcourseave();
			promptaskascending();
			sortcoursesave();
			displayallcoursesaveorder();
			break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}

	system("pause");
	return 0;
}
