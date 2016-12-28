#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define COU_CNT 7
#define MAX_STRLEN 20
#define MAX_COUNT 50
#define FORMAT_COU "%d\t%s\r\n"
#define MEMBERS_COU cou.no, cou.name
#define FORMAT_STU "%s\t%s\r\n"
#define MEMBERS_STU stu.no, stu.name
#define LINE  "\n------------------------\n"

//#define N 2

typedef struct course
{
	int no;
	//char no[MAX_STRLEN];
	char name[MAX_STRLEN];
}course;
course allcourses[MAX_COUNT];
int allcoursescount = 0;

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	int scores[COU_CNT];
	int selcourses[COU_CNT];
	int selcouscnt;
}student;
student allstudents[MAX_COUNT];
int allstudentscount = 0;

char curstuname[MAX_STRLEN] = "";
student  *curstu;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaycourse(course cou)
{
	printf(FORMAT_COU, MEMBERS_COU);
	printf("\r\n");
}
void displayallcourses()
{
	int i;
	printf("���пγ��������\r\n");
	printf("���\t����\r\n");
	printf(LINE);
	for (i = 0; i < allcoursescount; i++)
	{
		displaycourse(allcourses[i]);
	}
	printf(LINE);
}
void findcoursebyno(int no, course **cou)
{
	int i;
	int found = 0;
	for (i = 0; i < allcoursescount; i++)
	{
		if (allcourses[i].no == no)
		{
			*cou = &allcourses[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ������Ϊ%d�Ŀγ�\r\n", no);
		*cou = NULL;
	}
}

void displayonestuselcourses(student *stu)
{
	int i;
	course *cou;
	printf("ѧ��%sѡ��%d������\r\n", stu->name, stu->selcouscnt);
	for (i = 0; i < stu->selcouscnt; i++)
	{
		findcoursebyno(stu->selcourses[i], &cou);
		printf("%s\t", cou->name);
	}
	printf("\r\n");
}
void displayallstuselcourses()
{
	int i;
	printf("����ѧ��ѡ�ν������\r\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displayonestuselcourses(&allstudents[i]);
	}
	printf(LINE);
}

//void inputonestuscores(student *stu)
//{
//	int i;
//	int score;
//	char sup[MAX_STRLEN] = "";
//	course *cou;
//	printf("����������ѧ��%s�Ŀγ̷���\r\n", stu->name);
//	for (i = 0; i < stu->selcouscnt; i++)
//	{
//		findcoursebyno(stu->selcourses[i], &cou);
//		printf("%s�ķ�����", cou->name);
//		scanf("%d", &score);
//		stu->scores[i] = score;
//		if (score < 60)
//		{
//			printf("�����벹����Ϣ��");
//			scanf("%s", &sup);
//			strcpy(&stu->supplement[i], sup);
//		}
//	}
//	printf("\r\n");
//}
//void inputallstuscores()
//{
//	student *p = stuhead->next;
//	printf("����������ѧ���Ŀγ̷���\r\n");
//	printf(LINE);
//	while (p != NULL)
//	{
//		inputonestuscores(p);
//		p = p->next;
//	}
//	printf("����ѧ���Ŀγ�������ϡ�\r\n");
//}



void addscourse(int no, char *name)
{
	course cou;
	cou.no = no;
	strcpy(cou.name, name);
	allcourses[allcoursescount++] = cou;
}


void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()
{
	int i;
	printf("����ѧ������\r\n");
	printf("ѧ��\t����\r\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf(LINE);
}
/////////////
void addcourse(int no, char *name)
{
	course cou;
	cou.no = no;
	strcpy(cou.name, name);
	allcourses[allcoursescount++] = cou;
}

void inputcourses()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������γ̱��(������0����):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������γ�����:");
		scanf("%s", name);
		addcourse(no, name);
		printf("\n�γ�%s��Ϣ��ӳɹ�!\n", name);
	}
}

/////////////

void addstudent(char *no, char *name)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.selcouscnt = 0;
	allstudents[allstudentscount++] = stu;
}

void inputstudents()
{
	int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������ѧ��ѧ��(q����):");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ѧ������:");
		scanf("%s", name);
		addstudent(no, name);
		printf("\nѧ��%s��Ϣ��ӳɹ�!\n", name);
	}
}


void findstudentbyname(char *name, student **stu)
{
	int i;
	int found = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, name))
		{
			*stu = &allstudents[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s��ѧ��\r\n", name);
		*stu = NULL;
	}
}

void selectonecourse(student *stu, int couno)
{
	course *cou;
	findcoursebyno(couno, &cou);
	if (cou != NULL)
	{
		stu->selcourses[stu->selcouscnt] = couno;
		stu->selcouscnt++;
		printf("ѡ�γɹ���\r\n");
	}
}

void selectcourses(student *stu)
{
	int no;
	if (stu == NULL)
	{
		printf("��������������ѡ�Σ�\n");
		return;
	}
	do
	{
		printf("������Ҫѡ��Ŀγ̺ţ�0����ѡ��");
		scanf("%d", &no);
		fseek(stdin, 0, SEEK_END);
		if (no == 0)
		{
			printf("�����˳��˿γ�ѡ��\n");
			break;
		}
		selectonecourse(stu, no);
	} while (1);
	printf("ѡ�ν�����\n");
}

int main()
{
	int choice = -1;
	addstudent("001", "n1");
	addstudent("002", "ly");
	addstudent("003", "n3");
	displayallstudents();
	strcpy(curstuname, "ly");
	findstudentbyname(curstuname, &curstu);


	addscourse(1, "c1");
	addscourse(2, "c2");
	displayallcourses();
	//inputstudents();
	selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	//findstudentbyname("sm", &stu);
	/*selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);*/
	displayallstuselcourses();
#if DEV



#else
	while (choice != 0)
	{
		printf("\n\t ѧ��ѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��ѧ����Ϣ");
		printf("\n\t 2. �鿴���пγ�");
		printf("\n\t 3. �鿴����ѧ��");
		printf("\n\t 4. ���ĵ�ǰѧ������");
		printf("\n\t 5. ��ǰѧ��ѡ��");
		printf("\n\t 6. �鿴����ѧ��ѡ��");
		printf("\n\t 7. ¼��γ���Ϣ");
		printf("\n\n  ��ѡ��: ");
		choice = getche();
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
			inputstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallcourses();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayallstudents();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			printf("�����������������س�����:");
			scanf("%s", curstuname);
			findstudentbyname(curstuname, &curstu);
			printf("��ǰѧ��������%s\n", curstuname);
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			selectcourses(curstu);
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			displayallstuselcourses();
			break;
		case '7':
			printf("\n\n��ѡ���� 6\n");
			inputcourses();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}