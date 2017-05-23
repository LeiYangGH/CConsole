#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c, stu.total, stu.average
#define STU_MEMBERS_NET stu.no, stu.name,  stu.math, stu.english, stu.chinese, stu.c
typedef struct student
{
	char no[20];
	char name[20];
	int age;
	//char sex;
	//char birthday[20];
	//char address[20];
	//char telephone[20];
	//char email[20];
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
	//printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", stu.no, stu.name, stu.age, stu.sex,
	//	stu.birthday, stu.address, stu.telephone, stu.email);
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.age);
}

int cmpstubyno(const void * a, const void * b)
{
	return ((student*)a)->no - ((student*)b)->no;
}

void displayallstudents()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpstubyno);//��������
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
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.age = toint(part);
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
		return;
	else
	{

		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_STU);
	}

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

int promptsearchbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	searcbyname(name);
	return strcmp(name, "q");
}

void searchbyno(char no[20])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (streq(allstudents[i].no, no))
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

void promptsearchbyno()
{
	char no[20];
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%d", &no);
	searchbyno(no);
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

void removestudent(char no[20])
{
	int i, index, found = 0;
	for (index = 0; index < allstudentscount; index++)
	{
		if (streq(allstudents[index].no, no))
		{
			found = 1;
			break;
		}
	}
	if (found)
	{
		for (i = index; i < allstudentscount - 1; i++)
			allstudents[i] = allstudents[i + 1];
		allstudentscount--;
		printf("ɾ����ϣ�ʣ��%d����\n", allstudentscount);
	}
	else
	{
		printf("û�ҵ����޷�ɾ��\n");

	}
}

void promptremovestudent()
{
	//int no;
	//printf("������Ҫɾ����ѧ��:");
	//scanf("%d", &no);
	//removestudent(no);
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
		fprintf(fp, "%s\t%s\t%d\n", stu.no, stu.name, stu.age);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}


void addstudent(char no[20], char name[], int age)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.age = age;
	allstudents[allstudentscount++] = stu;
}


void promptaddstudent()
{
	//int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	//printf("\n������ѧ��\n");
	//scanf("%d", &no);
	//printf("\n�������û���\n");
	//scanf("%s", name);
	//printf("\n��������ѧ��Ӣ����ġ�c���Գɼ������������ո����\n");
	//scanf("%d%d%d%d", &math, &english, &chinese, &c);
	//addstudent(no, name, math, english, chinese, c);
	//printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;

#if 1

	readallstudents();
	//addstudent("01", "name1", 1);
	//addstudent("03", "name3", 3);
	//addstudent("02", "name2", 2);
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*promptremovestudent();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	removestudent("03");
	displayallstudents();
	//searcbyname("name2");
	//searchbyno("033");
	//writeallstudents();

#else
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
			readallstudents();
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
			promptremovestudent();
			break;
		case 6:
			break;
		case 7:
			sortanddisplay();
			break;
		case 8:
			writeallstudents();
			break;
		case 9:
			sortanddisplay();
			break;
		case 10:


			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
#endif
	printf("\n\n��������˳�\n");
	system("pause");

	return 0;
	}

