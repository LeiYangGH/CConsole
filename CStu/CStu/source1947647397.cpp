#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "stu.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];//ѧ��
	char name[MAX_STRLEN];//����
	int score[COURSES_COUNT];//����
	int total;//�ܷ�
	float average;//ƽ��
}student;
student allstudents[100];//����ѧ��
int allstudentscount = 0;//ѧ������


//typedef struct course//�γ�
//{
//	int oldindex;//�γ���input.txt������
//	float average;//ƽ����
//}course;
//course allcourses[COURSES_COUNT];//5�ſγ�

								 //�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}
//int cmpcourseindex;//����Ŀγ��±꣨0��4��
				   //�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}
//��ʾһ��ѧ���ɼ�
//void displaystudent(student stu)
//{
//	printf("%s\t%d\t%d\t%d\t%d\t%d\n", stu.name,
//		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
//}
//
////��ʾ����ѧ���ɼ�
//void displayallstudents()
//{
//	int i;
//	printf("����%dλͬѧ��������\r\n", allstudentscount);
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		displaystudent(allstudents[i]);
//	}
//	printf("--------------------------------------------\r\n");
//}
//��ʾһ��ѧ���ɼ�
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", stu.no, stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
}

//��ʾ����ѧ���ɼ�
void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��������:\r\n", allstudentscount);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
		"ѧ��", "����", "����", "��ѧ", "Ӣ��", "����", "����");
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------------\r\n");
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
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			stu.score[index - 3] = toint(part);
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
	}
	else
	{
		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allstudentscount;
			allstudents[allstudentscount - 1] = getstudentfromline(line);
		}
		//calctotalandave();
	}

}


//�������������ǿ�������qsortҪ��ĸ�ʽ�����ܷ���ѧ��
//int cmptotalfunc(const void * a, const void * b)
//{
//	return ((student*)a)->total - ((student*)b)->total;
//}
//void sorttotal()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmptotalfunc);
//}

////��ĳ��Ŀ�����гɼ�
//int cmponecoursefunc(const void * a, const void * b)
//{
//	return ((student*)a)->score[cmpcourseindex] - ((student*)b)->score[cmpcourseindex];
//}
//void sortonecourse()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmponecoursefunc);
//}

//����ÿ����Ŀ��ƽ����
//void calceachcourseave()
//{
//	int i, j;
//	float sum;
//	for (j = 0; j < COURSES_COUNT; j++)
//	{
//		sum = 0;
//		for (i = 0; i < allstudentscount; i++)
//		{
//			sum += allstudents[i].score[j];
//		}
//		allcourses[j].oldindex = j;
//		allcourses[j].average = sum / (float)COURSES_COUNT;
//	}
//}

//��Ŀƽ��������
//int cmpcoursesavefunc(const void * a, const void * b)
//{
//	return  ((course*)a)->average > ((course*)b)->average;
//}
//void sortcoursesave()
//{
//	qsort(allcourses, COURSES_COUNT, sizeof(course), cmpcoursesavefunc);
//}


//��ʾ����Ҫ����Ŀ�Ŀ
int promptaskcmpcourseindex()
{
	int courseid;
	printf("\n������Ҫ����Ŀγ����(1~5)���Իس�������");
	scanf("%d", &courseid);
	return courseid - 1;
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
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\r\n", stu.no, stu.name,
			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void addstudent(char no[], char name[], int s0, int s1, int s2, int s3, int s4)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.score[3] = s3;
	stu.score[4] = s4;
	allstudents[allstudentscount++] = stu;
	//calctotalandave();
	writeallstudents();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n������Ҫ���ӵ�ѧ��ѧ�š��������ո����\n");
	scanf("%s%s", no, name);
	printf("\n������5�Ƴɼ������������ո����\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("��ɵ�%d��ѧ���ɼ�¼��!\r\n", allstudentscount);
}

void calcdisplayhighlowave(int courseid)
{
	int i, t, h = 0, l = 100, sum = 0;
	float ave;
	int  below60stuindexes[20], belowcount = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score[courseid];
		h = h < t ? t : h;
		l = l > t ? t : l;
		sum += t;
		if (t < 60)
			below60stuindexes[belowcount++] = i;
	}
	ave = sum / (float)allstudentscount;
	printf("��%d�ſγ�ͳ����Ϣ��\r\n", courseid + 1);
	printf("ƽ����:%.1f����߷�%d����ͷ�%d\n", ave, h, l);
	printf("��������:", ave, h, l);
	for (i = 0; i < belowcount; i++)
	{
		printf("%s\t", allstudents[below60stuindexes[i]].name);
	}
	printf("\n");
}


//1
void calcdisplaybeststudetns()
{
	int i, j, below60courseexist;
	float ave;
	int  beststuindexes[20], bestcount = 0;

	calctotalandave();
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].average > 85)
		{
			below60courseexist = 0;
			for (j = 0; j < COURSES_COUNT; j++)
			{
				if (allstudents[i].score[j] < 60)
				{
					below60courseexist = 1;
					break;
				}
			}
			if (below60courseexist == 0)
			{
				beststuindexes[bestcount++] = i;
			}
		}
	}
	if (bestcount == 0)
		printf("��ѧ�����ߣ�ƽ���ִ���85����û�в�����γ̣�:��û�ˣ�");
	else
	{
		printf("��ѧ�����ߣ�ƽ���ִ���85����û�в�����γ̣�:");
		for (i = 0; i < bestcount; i++)
		{
			printf("%s\t", allstudents[beststuindexes[i]].name);
		}
	}
	printf("\n");
}

//���ݱ�Ų�����������
int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].no, no))
			return i;
	}
	return -1;//û�ҵ�
}

void editstudent(char no[50])
{
	int i;
	int s1, s2, s3, s4, s5;
	i = getstudentidexbyno(no);
	if (i >= 0)
	{
		printf("\n������5�Ƴɼ������������ո����\n");
		scanf("%d%d%d%d%d",
			&allstudents[i].score[0],
			&allstudents[i].score[1],
			&allstudents[i].score[2],
			&allstudents[i].score[3],
			&allstudents[i].score[4]);
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

//2
int main()
{
#if 1
	readallstudents();
	displayallstudents();
	//promptaddstudent();
	prompteditstudent();
	displayallstudents();
	//calcdisplayhighlowave(promptaskcmpcourseindex());
	//calcdisplaybeststudetns();
	system("pause");

#endif
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
		printf("\n\t 4. ����ѧ���ɼ�");
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
			/*sorttotal();
			displayallstudents();*/
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaskcmpcourseindex();

			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");

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

	system("pause");
	return 0;
}
