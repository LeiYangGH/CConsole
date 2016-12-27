#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 1
#define COU_CNT 7
#define MAX_STRLEN 20
#define N 5
//����������ʽ��Ϊ�˷��㣬������N=5��д����
#define FORMAT_COU "%d\t%s\t%d\t%d\r\n"
#define MEMBERS_COU cou.no, cou.name, cou.points, cou.stucnt

#define FORMAT_STU "%s\t%s\t%s\t%d\r\n"
//#define FORMAT_STU "%s\t%s\t%s\t%d\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.2f\r\n"
#define MEMBERS_STU stu.no, stu.name, stu.sex, stu.totalpoints, stu.supplement
//#define N 2

typedef struct course
{
	int no;
	char name[10];
	int points;
	//int maxstucnt;
	int stucnt;
	struct course  *next;
}course;
char *coursefile = "courses.txt";
course *couhead;

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
	float scores[COU_CNT];
	int selcourses[COU_CNT];
	int selcouscnt;
	int totalpoints;
	char supplement[MAX_STRLEN];
	struct student  *next;
}student;
student *stuhead;

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
	course *p = couhead->next;
	printf("���пγ�����\r\n");
	printf("���\t�γ�\tѧ��\t����\r\n");
	while (p != NULL)
	{
		displaycourse(*p);
		p = p->next;
	}
}

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}

//��һ���ı���ֳ��ɼ�
void getcoursefromline(char *line, course *cou)
{
	char * part;
	int index = 0, courseno;
	part = strtok(line, ",");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			courseno = toint(part);
			break;
		case 2:
			strcpy(cou->name, part);
			break;
		case 3:
			cou->points = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, ",");
	}
	cou->no = courseno;
	cou->stucnt = 0;
}

//��ȡ���гɼ�������
void readallcourses()
{
	char line[200];
	course *p1, *p2;
	FILE *fp = fopen(coursefile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		fp = fopen(coursefile, "a+");
		getchar();
	}

	p1 = p2 = (course *)malloc(sizeof(course));
	couhead = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//����������ȥ��ĩβ���з�����Ҫ
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
		strtok(line, "\n");
		getcoursefromline(line, p1);
		if (couhead == NULL)
			couhead = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (course*)malloc(sizeof(course));
	}
	p2->next = NULL;
}

void addstudents(student **p1, student **p2, char *no, char *name, char *sex)
{
	strcpy((*p1)->no, no);
	strcpy((*p1)->name, name);
	strcpy((*p1)->sex, sex);
	strcpy((*p1)->supplement, "");
	(*p1)->totalpoints = 0;
	(*p1)->selcouscnt = 0;
	(*p2)->next = (*p1);
	(*p2) = (*p1);
	(*p1) = (student*)malloc(sizeof(student));

}

void inputstudents()
{
	int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	student *p1, *p2;
	stuhead = (student *)malloc(sizeof(student));
	p1 = p2 = (student *)malloc(sizeof(student));
	stuhead->next = p1;
#if DEV
#else
	while (1)
#endif
	{
		//printf("\n\n������ѧ��ѧ��(q����):");
		//scanf("%s", &no);
		//if (streq(no, "q"))
		//{
		//	printf("\n���ѽ������룡");
		//	break;
		//}
		//printf("\n������ѧ������:");
		//scanf("%s", name);
		//strcpy(p1->no, no);
		//strcpy(p1->name, name);
		//for (i = 0; i < N; i++)
		//{
		//	printf("\n�������%d�ſγ̳ɼ�:", i + 1);
		//	scanf("%d", &score);
		//	p1->score[i] = score;
		//}
		//p1->score[N] = 0;
		//p2->next = p1;
		//p2 = p1;
#if DEV
		addstudents(&p1, &p2, "01", "name", "sex");
		addstudents(&p1, &p2, "02", "ly", "b");
		addstudents(&p1, &p2, "03", "sm", "g");
#else
#endif
		printf("\nѧ��%s��Ϣ��ӳɹ�!\n", name);
	}
	p2->next = NULL;
}

int deletestudentbyno(student *L, char * no)
{
	student *p1 = L, *p2;
	if (L == NULL)
	{
		printf("\nѧ������Ϊ��!\n");
		return 0;
	}
	while (!streq(p1->no, no) && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (streq(p1->no, no))
	{
		if (p1 == L)
			L = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("��ɾ��ѧ��Ϊ%s��ѧ���ĳɼ���\r\n", no);
			return 1;
		}
	}
	else
	{
		printf("û�ҵ�ѧ��Ϊ%s��ѧ��!\r\n", no);
		return 0;
	}
}

//�����ɼ�
void calcaverage(student *L)
{
	/*int i;
	float sum;
	student *n;
	n = L;
	while (n != NULL)
	{
		sum = 0;
		for (i = 0; i < N; i++)
		{
			sum += n->score[i];
		}
		n->score[N] = sum / N;
		n = n->next;
	}
	printf("ƽ���ɼ��������\r\n");*/
}


void displayallstudents()  //�������ѧ����Ϣ
{
	student *p = stuhead->next;
	printf("����ѧ���ɼ�����\r\n");
	printf("ѧ��\t����\t�Ա�\t��ѧ��\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}


void findcoursebyno(int  no, course **cou)  //�������ֲ���ѧ��
{
	int found = 0;
	course *p = couhead;

	while (p != NULL)
	{
		if (p->no == no)
		{
			*cou = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("û�ҵ������Ϊ%d�Ŀγ�\r\n", no);
		*cou = NULL;
	}
}


int selectonecourse(student *stu, int couno)
{
	course *cou;

	if (stu->selcouscnt >= 5)
	{
		printf("ѡ�β��ܳ���5��\r\n");
		return 0;
	}
	findcoursebyno(couno, &cou);
	if (cou != NULL && cou->stucnt < cou->no)
	{
		stu->selcourses[stu->selcouscnt++] = couno;
		cou->stucnt++;
		printf("ѡ�γɹ���\r\n");
	}
}

void selectcourses(student *stu)
{
	student *p = stuhead->next;
	printf("����ѧ���ɼ�����\r\n");
	printf("ѧ��\t����\t�Ա�\t��ѧ��\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}


int main()
{
	int choice = -1;
#if DEV
	readallcourses();
	displayallcourses();
	inputstudents();
	displayallstudents();
#else
	char no[MAX_STRLEN] = "";
	student *L;
	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ�¼��ɾ������");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��ѧ���ɼ�");
		printf("\n\t 2. ����ƽ��");
		printf("\n\t 3. ����ѧ��ɾ��");
		printf("\n\t 4. �鿴���гɼ�");
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
			L = inputstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			calcaverage(L);
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			printf("\n\n������ѧ��ѧ��:");
			scanf("%s", &no);
			deletestudentbyno(L, no);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallstudents(L);
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