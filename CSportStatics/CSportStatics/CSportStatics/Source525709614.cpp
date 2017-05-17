#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
//#define FILE_ALLOUTPUT "alloutput.txt"
//#define FILE_GRADES "grades.txt"
#define MAX_STRLEN 20
//#define COURSES_COUNT 5
//#define GRADES_COUNT 5
#define TEST 1
typedef struct student
{
	char name[MAX_STRLEN];
	int a;
	int b;
	int c;
	float f;
}student;
student allstudents[100];
int allstudentscount = 0;

//typedef struct course
//{
//	int oldindex;
//	float average;
//	int countingrade[GRADES_COUNT];
//}course;
//course allcourses[COURSES_COUNT];


int cmpcourseindex;
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

float tofloat(char *s)
{
	double temp = strtod(s, NULL);
	return atof(s);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%16s\t%d\t%d\t%d\t%.2f\n", stu.name, stu.a, stu.b, stu.c, stu.f);
}

void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("%16s\t��Ŀ1\t��Ŀ2\t��Ŀ3\t��Ŀ4\n", "����");
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
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.name, part);
			break;
		case 2:
			stu.a = toint(part);
			break;
		case 3:
			stu.b = toint(part);
			break;
		case 4:
			stu.c = toint(part);
			break;
		case 5:
			stu.f = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return stu;
}

int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->b - ((student*)b)->b);
}
void sortbyi2()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);

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
	sortbyi2();
}







void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_INPUT, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_INPUT);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%.2f\n", stu.name, stu.a, stu.b, stu.c, stu.f);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void addstudent(char name[], int i1, int i2, int i3, float f)
{
	student stu;
	strcpy(stu.name, name);
	stu.a = i1;
	stu.b = i2;
	stu.c = i3;
	stu.f = f;
	allstudents[allstudentscount++] = stu;
	sortbyi2();
	writeallstudents();
}

void promptaddstudent()
{
	char name[MAX_STRLEN] = "";
	int   i1, i2, i3;
	float f;
	printf("\n������ѧ������\n");
	scanf("%s", name);
	printf("\n������3�Ƴɼ������������ո����\n");
	scanf("%d%d%d%f", &i1, &i2, &i3, &f);
	addstudent(name, i1, i2, i3, f);
	printf("��ɵ�%d��ѧ���ɼ�¼��!\r\n", allstudentscount);
}

int main()
{

#if TEST

	readallstudents();
	//addstudent("s", 1, 2, 3, 4.4);
	//sorttotal();
	displayallstudents();
	promptaddstudent();
	displayallstudents();

	//ascending = -1;
	//cmpcourseindex = 4;
	//sortonecourse();

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
