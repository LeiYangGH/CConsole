#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 0
#define COU_CNT 7
#define MAX_STRLEN 20
#define FORMAT_COU "%d\t%s\t%d\t%d\r\n"
#define MEMBERS_COU cou.no, cou.name, cou.points, cou.stucnt
#define FORMAT_STU "%s\t%s\t%s\t%d\r\n"
#define MEMBERS_STU stu.no, stu.name, stu.sex, stu.totalpoints, stu.supplement
#define LINE  "\n------------------------\n"

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
	//float scores[COU_CNT];
	int scores[COU_CNT];
	int selcourses[COU_CNT];
	int selcouscnt;
	int totalpoints;
	char supplement[MAX_STRLEN];
	struct student  *next;
}student;
student *stuhead;

char curstuname[MAX_STRLEN] = "";
student * curstu;

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
	//course *p = couhead->next;
	course *p = couhead;
	printf("���пγ��������\r\n");
	printf(LINE);
	printf("���\t����\tѧ��\t����\r\n");
	printf(LINE);
	while (p != NULL)
	{
		displaycourse(*p);
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
	student *p = stuhead->next;
	printf("����ѧ��ѡ�ν������\r\n");
	printf(LINE);
	while (p != NULL)
	{
		displayonestuselcourses(p);
		p = p->next;
	}
}

void inputonestuscores(student *stu)
{
	int i;
	int score;
	char sup[MAX_STRLEN] = "";
	course *cou;
	printf("����������ѧ��%s�Ŀγ̷���\r\n", stu->name);
	for (i = 0; i < stu->selcouscnt; i++)
	{
		findcoursebyno(stu->selcourses[i], &cou);
		printf("%s�ķ�����", cou->name);
		scanf("%d", &score);
		stu->scores[i] = score;
		if (score < 60)
		{
			printf("�����벹����Ϣ��");
			scanf("%s", &sup);
			strcpy(&stu->supplement[i], sup);
		}
	}
	printf("\r\n");
}
void inputallstuscores()
{
	student *p = stuhead->next;
	printf("����������ѧ���Ŀγ̷���\r\n");
	printf(LINE);
	while (p != NULL)
	{
		inputonestuscores(p);
		p = p->next;
	}
	printf("����ѧ���Ŀγ�������ϡ�\r\n");
}


int isbelow60forcou(student *stu, int no)
{
	int i;
	for (i = 0; i < stu->selcouscnt; i++)
	{
		if (stu->selcourses[i] == no && stu->scores[i] < 60)
			return 1;
		return 0;
	}
}

void listallnamesbelow60forcou(int no)
{
	int i;
	student *p = stuhead->next;
	printf("\n��%d�Ź��β������ѧ����\r\n", no);
	while (p != NULL)
	{
		if (isbelow60forcou(p, no))
		{
			printf("%s\t", p->name);
		}
		printf(LINE);
		p = p->next;
	}
}

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
	printf("\r\n");
}
void displayallstudents()
{
	if (stuhead == NULL)
	{
		printf("��û�������κ�ѧ����Ϣ��\r\n");
	}
	else
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
	char sex[MAX_STRLEN] = "";
	student *p1, *p2;
	stuhead = (student *)malloc(sizeof(student));
	p1 = p2 = (student *)malloc(sizeof(student));
	stuhead->next = p1;
#if DEV
#else
	while (1)
#endif
	{

#if DEV
		addstudents(&p1, &p2, "01", "name", "sex");
		addstudents(&p1, &p2, "02", "ly", "b");
		addstudents(&p1, &p2, "03", "sm", "g");
#else
		printf("\n\n������ѧ��ѧ��(q����):");
		scanf("%s", &no);
		if (streq(no, "q"))
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ѧ������:");
		scanf("%s", name);
		printf("\n������ѧ���Ա�:");
		scanf("%s", sex);
		addstudents(&p1, &p2, no, name, sex);
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

void findstudentbyname(char *name, student **stu)
{
	int found = 0;
	student *p = stuhead;

	while (p != NULL)
	{
		if (streq(p->name, name))
		{
			*stu = p;
			return;
		}
		p = p->next;
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s��ѧ��\r\n", name);
		*stu = NULL;
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
	if (cou != NULL)
	{
		if (cou->stucnt < cou->no)
		{
			stu->selcourses[stu->selcouscnt] = couno;
			stu->totalpoints += cou->points;
			stu->selcouscnt++;
			cou->stucnt++;
			printf("ѡ�γɹ���\r\n");
			return 1;
		}
		else
		{
			printf("�γ�%s�Ѿ�ѡ����\r\n", cou->name);
			return 0;
		}
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
	while (stu->selcouscnt < 5)
	{
		printf("������Ҫѡ��Ŀγ̺ţ�1��7����0����ѡ��");
		scanf("%d", &no);
		fseek(stdin, 0, SEEK_END);
		if (no == 0)
		{
			if (stu->selcouscnt >= 3)
			{
				printf("�����˳��˿γ�ѡ��\n");
				break;
			}
			else
			{
				printf("����ѡ������3�ſγ̣�\n");
			}
		}
		selectonecourse(stu, no);
	};
	printf("ѡ�ν�����\n");
}

int cmpfunc(const void * a, const void * b)   //��ѧ�ֱȽ�
{
	student* stua = (student*)a;
	student* stub = (student*)b;
	if (stua->totalpoints == stub->totalpoints)
		return stua->name - stub->name;
	else
		return stua->totalpoints - stub->totalpoints;
}

void sortanddisplayallstudents()
{
	int i, cnt = 0;
	student all[50];
	student *p = stuhead->next;

	printf("����ѧ���ɼ����������������\r\n");
	while (p != NULL)
	{
		student stu;

		strcpy(stu.no, p->no);
		strcpy(stu.name, p->name);
		strcpy(stu.sex, p->sex);

		stu.totalpoints = p->totalpoints;
		all[cnt++] = stu;
		p = p->next;
	}
	qsort(all, cnt, sizeof(student), cmpfunc);//��������

	printf("ѧ��\t����\t��ѧ��\n");
	for (i = 0; i < cnt; i++)
	{
		printf("%s\t%s\t%d\n", all[i].no, all[i].name, all[i].totalpoints);
	}
}



int main()
{
	int choice = -1;
	readallcourses();
#if DEV
	student *stu;
	strcpy(curstuname, "ly");
	displayallcourses();
	inputstudents();
	displayallstudents();
	findstudentbyname(curstuname, &curstu);
	selectonecourse(curstu, 1);
	selectonecourse(curstu, 2);
	selectonecourse(curstu, 3);
	selectonecourse(curstu, 4);
	selectonecourse(curstu, 5);
	selectonecourse(curstu, 6);
	findstudentbyname("sm", &stu);
	selectonecourse(stu, 1);
	selectonecourse(stu, 2);
	selectonecourse(stu, 5);
	displayallstuselcourses();
	sortanddisplayallstudents();
#else
	while (choice != 0)
	{
		printf("\n\t ѧ��ѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��ѧ����Ϣ");
		printf("\n\t 2. �鿴���пγ�");
		printf("\n\t 3. �鿴����ѧ��");
		printf("\n\t 4. ѧ����¼����¼�����ѡ�Σ�");
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