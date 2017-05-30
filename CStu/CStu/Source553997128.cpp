#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct student
{
	char no[50];
	char name[50];
	int chinese;
	int math;
	int english;
	int total;
}student;

student allstudents[100];
int allstudentscount = 0;

float averagechinese, averagemath, averageenglish;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.chinese, stu.math, stu.english);
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

//qsort�ǿ�������Ҫ������д��������total����
int cmpfunc(const void * b, const void * a)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sortstudentsbytotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = allstudents[i].chinese + allstudents[i].math + allstudents[i].english;
	}
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortstudentsbytotalanddisplay()
{
	int i;
	sortstudentsbytotal();
	printf("��ÿ��ѧ������ƽ���ɼ����������\r\n");
	displayallstudents();
}

void addstudent(char no[50], char name[], int chinese, int math, int english)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.chinese = chinese;
	stu.math = math;
	stu.english = english;
	allstudents[allstudentscount++] = stu;
}

void promptaddstudent()
{
	char no[50]; char name[50] = "";
	int math; int english; int chinese;
	printf("\n������ѧ�ź��������ո����\n");
	scanf("%s%s", no, name);
	printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, chinese, math, english);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
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
	searcbyname(name);
}
//����ѧ��
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
//�û����벢����ѧ��
void promptsearchbyno()
{
	char no[20];
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%s", no);
	searchbyno(no);
}


int main()
{
	char choice = -1;
#if 0//�����ã�if���ɾ��
	//readallstudents();

	addstudent("04", "n4", 41, 92, 93);
	addstudent("01", "n1", 11, 12, 3);
	addstudent("02", "n2", 21, 22, 99);
	addstudent("05", "n5", 51, 52, 93);
	addstudent("06", "n6", 61, 62, 93);
	addstudent("03", "n3", 31, 32, 93);
	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	//calcanddisplaycoursehighest();
	calccoursesaveragesanddisplay();
	calccoursesaveragesbelowcountanddisplay();
	system("pause");

#endif
	while (choice != 0)
	{
		printf("\n\t ѧ����Ϣ����ϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ���ѧ����Ϣ");
		printf("\n\t 2. ���ֽܷ���鿴����ѧ����Ϣ");
		printf("\n\t 3. ��ѧ�Ų�ѯ");
		printf("\n\t 4. ��������ѯ");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);//������뻺��������������Ƿ����������ѭ��
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
			promptaddstudent();

			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			sortstudentsbytotalanddisplay();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptsearchbyno();
			break;
		case '4':
			printf("\n\n��ѡ���� 3\n");
			promptsearchbyname();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	printf("\n\n��������˳�\n");
	system("pause");

	return 0;
}

