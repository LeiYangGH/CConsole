#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
//#define FILE_STU "sample.txt"
//#define FILE_BEST "best.txt"
//#define FILE_SCORES "scores.txt"
//#define FILE_ANALYSIS "analysis.txt"
#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c, stu.total, stu.average
#define STU_MEMBERS_NET stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c
typedef struct student
{
	int no;
	char name[50];
	int math;
	int english;
	int chinese;
	int c;
	int total;
	float average;
}student;

student allstudents[100];
student sortstudents[100];
int allstudentscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "stu.txt";
student *head;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

int tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf(FORMATNET, STU_MEMBERS_NET);
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
			stu.no = toint(part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.math = toint(part);
			break;
		case 4:
			stu.english = toint(part);
			break;
		case 5:
			stu.chinese = toint(part);
			break;
		case 6:
			stu.c = toint(part);
			break;
		case 7:
			stu.total = toint(part);
			break;
		case 8:
			stu.average = tofloat(part);
			break;
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
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
	}
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

int below60()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total < 60)
			c++;
	}
	return c;
}

int below60_80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 60 && allstudents[i].total < 80)
			c++;
	}
	return c;
}

int above80()
{
	int i, c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].total >= 80)
			c++;
	}
	return c;
}

float ave()
{
	int i;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
		sum += allstudents[i].total;
	return sum / (float)allstudentscount;
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("����������,����q�˳���ѯ:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

int searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
			return allstudents[i].average;
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
	return 0;
}

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	printf("ѧ��%s�ĳɼ�Ϊ%d��", name, searchtotalbyname(name));
	return strcmp(name, "q");
}



int searchtotalbyno(int no)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (allstudents[i].no == no)
			return allstudents[i].average;
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
	return 0;
}

void promptsearchtotalbyno()
{
	int no;
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%d", &no);
	printf("ѧ��%d�ĳɼ�Ϊ%d��", no, searchtotalbyno(no));
}

//����ɼ���Ϣ
void inputname(char str[])
{
	//int len = -1;
	//while (len < 2 || len > 49)
	//{
	printf("����������(2-45���ַ�)�����ܴ��ո�Tab��س���:");
	//	scanf("%s", str);
	//	len = strlen(str);
	//}
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

void createsamplestudents()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMATNET, 33, "Smile", 13, 23, 33, 43);
	fprintf(fp, FORMATNET, 44, "Lukas", 14, 24, 34, 44);
	fprintf(fp, FORMATNET, 55, "Shawn", 15, 25, 35, 45);
	fprintf(fp, FORMATNET, 22, "Tony", 12, 22, 32, 42);
	fprintf(fp, FORMATNET, 11, "Flex", 11, 21, 31, 41);
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽student.txt��\n");
}



int getstudentidexbyid(int no)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (b.no == no)
			return i;
	}
}

void removestudent(int no)
{
	int i;
	int index;
	index = getstudentidexbyid(no);
	for (i = index; i < allstudentscount - 1; i++)
		allstudents[i] = allstudents[i + 1];
	allstudentscount--;
	printf("ɾ����ϣ�ʣ��%d����\r\n", allstudentscount);

}

void promptremovestudent()
{
	int no = 99;
	removestudent(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n����������\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
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
		fprintf(fp, FORMATNET, STU_MEMBERS_NET);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}

void addstudent(int no, char name[], int math, int english, int chinese, int c)
{
	student stu;
	stu.no = no;
	strcpy(stu.name, name);
	stu.math = math;
	stu.english = english;
	stu.chinese = chinese;
	stu.c = c;
	allstudents[allstudentscount++] = stu;
}

void calcanddisplaytotalandaverage()
{
	int i;
	student stu;
	printf("����%d��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		allstudents[i].total = stu.total = calctotal(stu.math, stu.english, stu.chinese, stu.c);
		allstudents[i].average = stu.average = calcave(stu.total);
		printf("%d\t%s\t%d\t%.1f\r\n", stu.no, stu.name, stu.total, stu.average);
	}
	printf("--------------------------------------------\r\n");
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
		scores[i] = allstudents[i].math;
	}
	calcanddisplaysubject("��ѧ", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].english;
	}
	calcanddisplaysubject("Ӣ��", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].chinese;
	}
	calcanddisplaysubject("����", scores);

	for (i = 0; i < allstudentscount; i++)
	{
		scores[i] = allstudents[i].c;
	}
	calcanddisplaysubject("C����", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddstudent()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n������ѧ��\n");
	scanf("%d", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n��������ѧ��Ӣ����ġ�c���Գɼ������������ո����\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addstudent(no, name, math, english, chinese, c);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;

	/*if (login())
	{
		printf("login ok\n");
	}
	else
		printf("login fail\n");*/

	createsamplestudents();

	readallstudents();
	//printf("\n%d\n", allstudentscount);
	/*promptaddstudent();
	writeallstudents();*/
	/*promptremovestudent();
	writeallstudents();*/
	//promptsearchtotalbyname();
	//promptsearchtotalbyno();

	//displayallstudents();
	calcanddisplaytotalandaverage();
	sortanddisplay();
	calcanddisplayallsubjects();
	//addstudent();
	//writeallstudents();

	//char name[20] = "Miller";
	//deletestudent(delname);

	//viewstudent(name);
	//sortandviewall();

	/*char name[20] = "insert";
	int sc = 55;
	if (insert(head, 3, name, sc))
	printf("\nisnerted\n");*/
	//viewallstudents();
	//while (choice != 0)
	//{
	//	printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
	//	printf("\n\t------------------------------");
	//	printf("\n\n\t 0. �˳� 0");
	//	printf("\n\n\t 1. ��� 1");
	//	printf("\n\t 2. ɾ�� 2");
	//	printf("\n\t 3. �鿴���� 3");
	//	printf("\n\t 4. �����������ҵ��� 4");
	//	printf("\n\t 5. ���ɼ��������� 5");
	//	printf("\n\t 6. ���� 6");
	//	printf("\n\t 7. ���� 7");
	//	printf("\n\n ��ѡ��: ");
	//	scanf("%1[01234567]d%*c", &choice);
	//	choice = getche();
	//	switch (choice)
	//	{
	//	case '0':
	//		printf("\n\n ��ѡ�����˳�: ");
	//		fseek(stdin, 0, SEEK_END);
	//		system("pause");
	//		exit(0);
	//		break;
	//	case '1':
	//		printf("\n\n��ѡ���� 1\n");
	//		addstudent();
	//		break;
	//	case '2':
	//		printf("\n\n��ѡ���� 2\n");
	//		promptdeletebyname();
	//		break;
	//	case '3':
	//		printf("\n\n��ѡ���� 3\n");
	//		viewallstudents();
	//		break;
	//	case '4':
	//		printf("\n\n��ѡ���� 4\n");
	//		promptsearchtotalbyname();
	//		break;
	//	case '5':
	//		printf("\n\n��ѡ���� 5\n");
	//		sortandviewall();
	//		break;
	//	case '6':
	//		printf("\n\n��ѡ���� 6\n");
	//		promptinsertbeforeno();
	//		break;
	//	case '7':
	//		printf("\n\n��ѡ���� 7\n");
	//		writeallstudents();
	//		break;
	//	default:
	//		printf("\n\n������������ѡ\n");
	//		break;
	//	}
	//	getch();
	//}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

