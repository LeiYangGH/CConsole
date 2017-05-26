#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRLEN 20
#define STUDENTS_COUNT 6
#define COURSES_COUNT 5
#define GRADES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];// ѧ��
	char name[MAX_STRLEN];//����
	int score[COURSES_COUNT];//����
	int total;//�ܷ�
	float average;//ƽ��
}student;
student allstudents[6];//����ѧ��
int allstudentscount = 0;//ѧ������

typedef struct calcstudent
{
	int highest;//���
	int lowest;//���
	int total;//�ܷ�
	float average;//ƽ��

}calcstudent;
calcstudent allcalcstudents[6];//����ѧ��


typedef struct course//�γ�
{
	int highest;
	int lowest;
	int total;
	float average;
}course;
course allcourses[COURSES_COUNT];//5�ſγ�
char *coursenames[MAX_STRLEN] = { "����","��ѧ", "Ӣ��", "����", "����" };

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
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("%s\t%s\t%s\t%s\t%s\n", "����", "��ѧ", "Ӣ��", "����", "����");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

//��Ŀƽ��������
int cmpstubyonecourse(const void * a, const void * b)
{
	return (int)(((student*)a)->score[0] - ((student*)b)->score[0]);
}
//1
void displaystudentonecourse(student stu, int courseid)
{
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score[courseid]);
}

//��ʾ����ѧ���ɼ�
void displayonecoursesort()
{
	int i;
	printf("\n\nѡȡ��һ�Ƴɼ���С�����������ѧ�ţ��������ɼ�\r\n", allstudentscount);
	printf("%s\t%s\t%d\n", "ѧ��", "����", "�ɼ�");
	qsort(allstudents, STUDENTS_COUNT, sizeof(student), cmpstubyonecourse);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudentonecourse(allstudents[i], 0);
	}
	printf("\r\n--------------------------------------------\r\n");
}
//2


//��ʾ����ѧ���ɼ�
void displayallcalcstudents()
{
	int i;
	printf("����ÿ���˵���߳ɼ�����ͳɼ���ƽ���ɼ�\r\n");
	printf("%s\t%s\t%s\t%s\n", "����", "���", "���", "ƽ��");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		calcstudent stu = allcalcstudents[i];
		printf("%s\t%d\t%d\t%.1f\n", allstudents[i].name,
			stu.highest, stu.lowest, stu.average);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void calchighlowave()
{
	int i, t, j, h, l, sum;
	float ave;
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		h = 0, l = 100, sum = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)COURSES_COUNT;
		allcalcstudents[i].highest = h;
		allcalcstudents[i].lowest = l;
		allcalcstudents[i].total = sum;
		allcalcstudents[i].average = ave;
	}
}

void calchighlowaveanddisplay()
{
	calchighlowave();
	displayallcalcstudents();
}

//��ʾ���п�Ŀƽ��������
void displayallcourses()
{
	int i;
	printf("����ÿ�Ƴɼ��е���߳ɼ�����ͳɼ���ƽ���ɼ�\r\n");
	printf("%s\t%s\t%s\t%s\n", "��Ŀ", "���", "���", "ƽ��");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{
		course cou = allcourses[i];
		printf("%s\t%d\t%d\t%.1f\n", coursenames[i],
			cou.highest, cou.lowest, cou.average);
	}
	printf("\r\n--------------------------------------------\r\n");
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

//����ÿ����Ŀ��ƽ����
void calccoursesanddisplay()
{
	int i, t, j, h, l, sum;
	float ave;
	for (j = 0; j < COURSES_COUNT; j++)
	{
		h = 0, l = 100, sum = 0;

		for (i = 0; i < STUDENTS_COUNT; i++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)STUDENTS_COUNT;
		allcourses[j].highest = h;
		allcourses[j].lowest = l;
		allcourses[j].total = sum;
		allcourses[j].average = ave;
	}
	displayallcourses();
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
	calctotalandave();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n������ѧ��ѧ�š��������ո����\n");
	scanf("%s%s", no, name);
	printf("\n������5�Ƴɼ������������ո����\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("��ɵ�%d��ѧ���ɼ�¼��!\r\n", allstudentscount);
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
	printf("%s\t%s\t%s\t%s\t%s\n", "����", "��ѧ", "Ӣ��", "����", "����");
	searcbyname(name);
}

void displaystudentsgrade()
{
	int i, gradeindex;
	float ave;
	calchighlowave();

	char *grades[GRADES_COUNT] = { "������(0��59)","����(60��69)", "�е�(70��79)", "����(80��89)", "����(90��100)", };
	printf("��ƽ���ɼ�����ÿ�˵��ţ������У����񣬲�����\r\n");
	printf("%s\t%s\t%s\n", "����", "ƽ����", "�ȼ�");
	for (i = 0; i < allstudentscount; i++)
	{
		ave = allstudents[i].average;
		if (ave < 60)
			gradeindex = 0;
		else if (ave >= 60 && ave <= 69)
			gradeindex = 1;
		else if (ave >= 70 && ave <= 79)
			gradeindex = 2;
		else if (ave >= 80 && ave <= 89)
			gradeindex = 3;
		else if (ave >= 90)
			gradeindex = 4;
		printf("%s\t%.1f\t%s\n", allstudents[i].name, ave, grades[gradeindex]);
	}
}

int main()
{
	int choice = -1;

	addstudent("04", "n4", 41, 42, 43, 44, 45);
	addstudent("01", "n1", 11, 12, 13, 14, 15);
	addstudent("02", "n2", 21, 22, 23, 24, 25);
	addstudent("06", "n6", 61, 62, 63, 64, 65);
	addstudent("03", "n3", 31, 32, 33, 34, 35);
	//addstudent("05", "n5", 51, 52, 53, 54, 55);

#if 0
	addstudent("05", "n5", 51, 52, 53, 54, 55);

	//displayallstudents();
	//calchighlowaveanddisplay();
	//calccoursesanddisplay();
	//searcbyname("n1");
	//displayonecoursesort();
	//displaystudentsgrade();
	//system("pause");
#endif
	printf("���Զ����5��ѧ���ɼ����������1��ѧ���ɼ���Ϊ�˷�����ԣ�����ҵ��ʱ������޸Ĵ���Ϊȫ���������룩\n");
	promptaddstudent();
	displayallstudents();
	calchighlowaveanddisplay();
	calccoursesanddisplay();
	displaystudentsgrade();
	displayonecoursesort();
	printf("���루��scanf����ѯÿ���˸���ɼ���Ϣ\n");
	promptsearchbyname();
	system("pause");
	return 0;
}

