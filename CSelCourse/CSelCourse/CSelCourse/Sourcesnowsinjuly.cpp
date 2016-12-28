#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 1
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
student  curstu;

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
	printf("���пγ��������\r\n");
	printf(LINE);
	printf("���\t����\tѧ��\t����\r\n");
}
//void findcoursebyno(int  no, course **cou)  //�������ֲ���ѧ��
//{
//	int found = 0;
//	course *p = couhead;
//
//	while (p != NULL)
//	{
//		if (p->no == no)
//		{
//			*cou = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("û�ҵ������Ϊ%d�Ŀγ�\r\n", no);
//		*cou = NULL;
//	}
//}

//void displayonestuselcourses(student *stu)
//{
//	int i;
//	course *cou;
//	printf("ѧ��%sѡ��%d������\r\n", stu->name, stu->selcouscnt);
//	for (i = 0; i < stu->selcouscnt; i++)
//	{
//		findcoursebyno(stu->selcourses[i], &cou);
//		printf("%s\t", cou->name);
//	}
//	printf("\r\n");
//}
//void displayallstuselcourses()
//{
//	student *p = stuhead->next;
//	printf("����ѧ��ѡ�ν������\r\n");
//	printf(LINE);
//	while (p != NULL)
//	{
//		displayonestuselcourses(p);
//		p = p->next;
//	}
//}

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






void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()
{
	int i;
	printf("����ѧ���ɼ�����\r\n");
	printf("ѧ��\t����\t�Ա�\t��ѧ��\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}


void addstudent(char *no, char *name)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.selcouscnt = 0;
	allstudents[allstudentscount++] = stu;
}

//void inputstudents()
//{
//	int i, score;
//	char no[MAX_STRLEN] = "";
//	char name[MAX_STRLEN] = "";
//	char sex[MAX_STRLEN] = "";
//	student *p1, *p2;
//	stuhead = (student *)malloc(sizeof(student));
//	p1 = p2 = (student *)malloc(sizeof(student));
//	stuhead->next = p1;
//#if DEV
//#else
//	while (1)
//#endif
//	{
//
//#if DEV
//		addstudents(&p1, &p2, "01", "name", "sex");
//		addstudents(&p1, &p2, "02", "ly", "b");
//		addstudents(&p1, &p2, "03", "sm", "g");
//#else
//		printf("\n\n������ѧ��ѧ��(q����):");
//		scanf("%s", &no);
//		if (streq(no, "q"))
//		{
//			printf("\n���ѽ������룡");
//			break;
//	}
//		printf("\n������ѧ������:");
//		scanf("%s", name);
//		printf("\n������ѧ���Ա�:");
//		scanf("%s", sex);
//		addstudents(&p1, &p2, no, name, sex);
//#endif
//		printf("\nѧ��%s��Ϣ��ӳɹ�!\n", name);
//}
//	p2->next = NULL;
//}


//void findstudentbyname(char *name, student **stu)
//{
//	int found = 0;
//	student *p = stuhead;
//
//	while (p != NULL)
//	{
//		if (streq(p->name, name))
//		{
//			*stu = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("û�ҵ�����Ϊ%s��ѧ��\r\n", name);
//		*stu = NULL;
//	}
//}

//int selectonecourse(student *stu, int couno)
//{
//	course *cou;
//
//	if (stu->selcouscnt >= 5)
//	{
//		printf("ѡ�β��ܳ���5��\r\n");
//		return 0;
//	}
//	findcoursebyno(couno, &cou);
//	if (cou != NULL)
//	{
//		if (cou->stucnt < cou->no)
//		{
//			stu->selcourses[stu->selcouscnt] = couno;
//			stu->totalpoints += cou->points;
//			stu->selcouscnt++;
//			cou->stucnt++;
//			printf("ѡ�γɹ���\r\n");
//			return 1;
//		}
//		else
//		{
//			printf("�γ�%s�Ѿ�ѡ����\r\n", cou->name);
//			return 0;
//		}
//	}
//}
//
//void selectcourses(student *stu)
//{
//	int no;
//	if (stu == NULL)
//	{
//		printf("��������������ѡ�Σ�\n");
//		return;
//	}
//	do
//	{
//		printf("������Ҫѡ��Ŀγ̺ţ�1��7����0����ѡ��");
//		scanf("%d", &no);
//		fseek(stdin, 0, SEEK_END);
//		if (no == 0)
//		{
//			if (stu->selcouscnt >= 3)
//			{
//				printf("�����˳��˿γ�ѡ��\n");
//				break;
//			}
//			else
//			{
//				printf("����ѡ������3�ſγ̣�\n");
//			}
//		}
//		selectonecourse(stu, no);
//	} while (stu->selcouscnt <= 5);
//	printf("ѡ�ν�����\n");
//}
//



int main()
{
	int choice = -1;
#if DEV
	addstudent("001", "n1");
	addstudent("002", "ly");
	addstudent("003", "n3");
	strcpy(curstuname, "ly");
	//displayallcourses();
	//inputstudents();
	displayallstudents();
	//findstudentbyname(curstuname, &curstu);
	/*selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	selectonecourse(curstu, 3);
	selectonecourse(curstu, 4);
	selectonecourse(curstu, 5);
	selectonecourse(curstu, 6);*/
	//findstudentbyname("sm", &stu);
	/*selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);*/
	//displayallstuselcourses();
	//sortanddisplayallstudents();
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
		printf("\n\t 7. ѧ����ѧ���ܻ����������");
		printf("\n\t 8. ��������ѧ���ɼ�");
		printf("\n\t 9. һ�ź����Ź��β������ѧ��");
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
			printf("\n\n��ѡ���� 7\n");
			sortanddisplayallstudents();
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			inputallstuscores();
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			listallnamesbelow60forcou(1);
			listallnamesbelow60forcou(3);
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