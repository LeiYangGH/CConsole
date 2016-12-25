#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FORMAT "%s\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STUDENTS_COUNT 10
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
#define STU_MEMBERS_NET stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
typedef struct student
{
	char no[50];
	char name[50];
	int score[3];
	int total;
}student;

student allstudents[STUDENTS_COUNT];
student sortstudents[STUDENTS_COUNT];
int allstudentscount = 0;

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
	printf("\r\n");
	printf(FORMAT, STU_MEMBERS_NET);
}

void displayallstudents()
{
	int i;
	printf("����%d��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		sortstudents[i] = allstudents[i];
	}
	qsort(sortstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("���������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(sortstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}



void countbygrades()
{
	//int i, t, cnt90 = 0, cnt7589 = 0, cnt6074 = 0, cnt60 = 0;
	//student stu;
	//printf("�ַܷ���������ͳ��%d��������\r\n", allstudentscount);
	//printf("--------------------------------------------\r\n");
	//for (i = 0; i < allstudentscount; i++)
	//{
	//	t = allstudents[i].average;
	//	if (t >= 90)
	//		cnt90++;
	//	else if (t >= 75 && t <= 89)
	//		cnt7589++;
	//	else if (t >= 60 && t <= 74)
	//		cnt6074++;
	//	else if (t < 60)
	//		cnt60++;
	//}
	//printf("90������:%d��, 75~89:%d��, 60~74:%d��, 60������:%d��\r\n",
	//	cnt90, cnt7589, cnt6074, cnt60);
	//printf("--------------------------------------------\r\n");
}

void calcminmaxave()
{
	int i, min = 300, max = 0, t;
	float sum = 0, ave;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].total;
		sum += t;
		min = t < min ? t : min;
		max = t > max ? t : max;
	}
	ave = sum / STUDENTS_COUNT;
	printf("�ܳɼ���߷֣�%d��, ��ͷ�:%d��, ƽ����:%f��\r\n",
		max, min, ave);
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("����������:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

void searchtotalbyname(char *name)
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

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	searchtotalbyname(name);
	return strcmp(name, "q");
}

void searchtotalbyno(char no[])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (allstudents[i].no == no)
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

void promptsearchtotalbyno()
{
	char no[MAX_STRLEN];
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%d", &no);
	searchtotalbyno(no);
}

//����ɼ���Ϣ
void inputname(char str[])
{
	printf("����������(2-45���ַ�)�����ܴ��ո�Tab��س���:");
	scanf("%s", str);
	printf("�����������ΪΪ %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("���������1��100:");
		scanf("%d", &n);
	}
	return n;
}

void addstudent(char no[], char name[], int s0, int s1, int s2)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.total = s0 + s1 + s2;
	allstudents[allstudentscount++] = stu;
}

void createsamplestudents()
{
	printf("����ʾ���ɼ�����...");
	addstudent("16001", "Smile", 13, 83, 63);
	addstudent("16002", "Shawn", 15, 85, 65);
	addstudent("16003", "Tony", 12, 82, 62);
	addstudent("16004", "Flex", 11, 81, 61);
	addstudent("16005", "Smile5", 13, 83, 63);
	addstudent("16006", "Smile6", 23, 83, 63);
	addstudent("16007", "Smile7", 33, 83, 63);
	addstudent("16008", "Smile8", 13, 83, 63);
	addstudent("16009", "Smile9", 13, 83, 63);
	addstudent("16010", "Smile10", 13, 83, 63);
	printf("9��ʾ���ɼ������ѱ��浽��\n");
}

int getstudentidexbyid(char no[])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (b.no == no)///
			return i;
	}
}


int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}



void calcanddisplaytotalandaverage()
{
	//int i;
	//student stu;
	//printf("���и����ܷ֡�ƽ��������\r\n");
	//printf("--------------------------------------------\r\n");
	//for (i = 0; i < allstudentscount; i++)
	//{
	//	stu = allstudents[i];
	//	allstudents[i].total = stu.total = calctotal(stu.score[0], stu.score[1], stu.score[2], stu.c);
	//	allstudents[i].average = stu.average = calcave(stu.total);
	//	printf("%d\t%s\t%d\t%.1f\r\n", stu.no, stu.name, stu.total, stu.average);
	//}
	//printf("--------------------------------------------\r\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("��Ŀ:%s ƽ����%.1f�������ʰٷ�֮%.1f���������ʰٷ�֮%.1f\r\n", subuject,
		(sum / (float)allstudentscount),
		(1 - below60 / (float)allstudentscount)*100.0f,
		(below60 / (float)allstudentscount)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	int i, sum = 0, below60 = 0;
	int scores[100];
	student stu;
	printf("���п�Ŀ�ɼ�ͳ������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].score[0];
	}
	calcanddisplaysubject("��ѧ", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].score[1];
	}
	calcanddisplaysubject("Ӣ��", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].score[2];
	}
	calcanddisplaysubject("����", scores);


	printf("--------------------------------------------\r\n");
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3;
	printf("\n������ѧ��\n");
	scanf("%s", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n���������Ƴɼ������������ո����\n");
	scanf("%d%d%d", &s1, &s2, &s3);
	addstudent(no, name, s1, s2, s3);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;



	createsamplestudents();
	//promptaddstudent();
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*promptremovestudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	calcminmaxave();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
	//calcanddisplayallsubjects();

	//countbygrades();
	system("pause");

	while (choice != 0)
	{
		char *menu = "**********************�˵�****************************\n"
			"��1��������ѧ������               ��6����ѧ�Ƽ������\n"
			"��2��������������ѯ               ��7����ѧ����������\n"
			"��3��������ѧ�Ų�ѯ               ��8��������ѧ������\n"
			"��4�������ѧ������               ��9�� : �鿴ѧ������\n"
			"��5����ɾ��ѧ������               ��10���������ƽ����\n"
			"��0�����˳�����ϵͳ";
		printf("������ѡ�����֣����س�\n", menu);
		printf("%s\n", menu);
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			system("pause");
			exit(0);
			break;
		case 1:
			break;
		case 2:
			promptsearchtotalbyname();
			break;
		case 3:
			promptsearchtotalbyno();
			break;
		case 4:
			promptaddstudent();
			break;
		case 5:
			break;
		case 6:
			countbygrades();
			break;
		case 7:
			sortanddisplay();
			break;
		case 8:
			break;
		case 9:
			sortanddisplay();
			break;
		case 10:
			calcanddisplaytotalandaverage();
			calcanddisplayallsubjects();

			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

