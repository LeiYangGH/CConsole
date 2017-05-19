#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "stuin.txt"
#define FILE_ALLOUTPUT "alloutput.txt"
#define FILE_GRADES "grades.txt"
#define MAX_STRLEN 20
#define GRADES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	int score;
	//int order;
}student;
student allstudents[1005];
int allstudentscount = 0;
int averagescore = 0;


#define TEST 1

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
	printf("ѧ��\t����\t�ɼ�\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}



//void writestudentsaveorder()
//{
//	int i;
//	FILE *fp;
//	fp = fopen(FILE_ALLOUTPUT, "w");
//	if (fp == NULL)
//	{
//		printf("\n���ļ�%sʧ��!", FILE_ALLOUTPUT);
//		getchar();
//		exit(1);
//	}
//	fprintf(fp, "����\t��Ŀ1\t��Ŀ2\t��Ŀ3\t��Ŀ4\t��Ŀ5\tƽ��\t����\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		student stu = allstudents[i];
//		fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%d\n", stu.name,
//			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
//			stu.average, stu.order);
//	}
//	fclose(fp);
//	printf("ѧ���ۺϳɼ���������ļ�%s\n", FILE_ALLOUTPUT);
//}

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, " \n");
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
		part = strtok(NULL, " \n");
	}
	return stu;
}

void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].score;
	}
	averagescore = sum / (float)allstudentscount;
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



int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}
void sortstudetsbyscore()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
}

void displayhigheststudents()
{
	int i = 0;
	printf("��߷�ͬѧ����\r\n");
	sortstudetsbyscore();
	printf("ѧ��\t����\t�ɼ�\n");
	printf("--------------------------------------------\r\n");
	while (allstudents[i].score == allstudents[0].score)
		displaystudent(allstudents[i++]);
	printf("\r\n--------------------------------------------\r\n");
}

void countbygradesforonecourse(int courseindex)
{
	//int i, t;
	//for (i = 0; i < allstudentscount; i++)
	//{
	//	t = allstudents[i].score[courseindex];
	//	if (t < 60)
	//		allcourses[courseindex].countingrade[0]++;
	//	else if (t >= 60 && t <= 69)
	//		allcourses[courseindex].countingrade[1]++;
	//	else if (t >= 70 && t <= 79)
	//		allcourses[courseindex].countingrade[2]++;
	//	else if (t >= 80 && t <= 89)
	//		allcourses[courseindex].countingrade[3]++;
	//	else if (t >= 90)
	//		allcourses[courseindex].countingrade[4]++;
	//}
}




void writeandprintgradescount()
{
	//int i, j;
	//char *grades[GRADES_COUNT] = { "<60","60~69", "70~79", "80~89", ">=90", };
	//FILE *fp;
	//fp = fopen(FILE_GRADES, "w");
	//if (fp == NULL)
	//{
	//	printf("\n���ļ�%sʧ��!", FILE_GRADES);
	//	getchar();
	//	exit(1);
	//}
	//printf("������\t��Ŀ1\t��Ŀ2\t��Ŀ3\t��Ŀ4\t��Ŀ5\n");
	//fprintf(fp, "������\t��Ŀ1\t��Ŀ2\t��Ŀ3\t��Ŀ4\t��Ŀ5\n");
	//for (i = 0; i < GRADES_COUNT; i++)
	//{
	//	printf("%s", grades[i]);
	//	fprintf(fp, "%s", grades[i]);
	//	for (j = 0; j < COURSES_COUNT; j++)
	//	{
	//		course cou = allcourses[j];
	//		printf("\t%d", cou.countingrade[i]);
	//		fprintf(fp, "\t%d", cou.countingrade[i]);
	//	}
	//	printf("\n");
	//	fprintf(fp, "\n");
	//}
	//fclose(fp);
	//printf("��������������ļ�%s\n", FILE_GRADES);
}


//void writeallstudents()
//{
//	int i;
//	student stu;
//	FILE *fp = fopen(FILE_INPUT, "w+");
//	if (fp == NULL)
//	{
//		printf("\n���ļ�%sʧ��!", FILE_INPUT);
//		getchar();
//		exit(1);
//	}
//
//
//	for (i = 0; i < allstudentscount; i++)
//	{
//		stu = allstudents[i];
//		fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\r\n", stu.name,
//			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
//	}
//	fclose(fp);
//	printf("�ѱ����¼���ļ���");
//}


int main()
{
#if TEST
	readallstudents();
	//calctotalandave();
	displayallstudents();

	//sorttotal();
	displayhigheststudents();

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
