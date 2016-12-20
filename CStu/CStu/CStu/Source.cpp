#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FORMAT3DSD "%d\t%s\t%d\r\n"
typedef struct student
{
	int no;
	char name[50];
	int score;
	student *next;
}student;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

char *scoresfile = "scores.txt";
student *head;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//��һ���ı���ֳ��ɼ� 
void getstudentfromline(char *line, student *adg)
{
	char * part;
	int index = 0;

	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			adg->no = toint(part);
			break;
		case 2:
			strcpy(adg->name, part);
			break;
		case 3:
			adg->score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
}


//��ʾһ���ɼ� 
void displaystudent(student stu)
{
	printf(FORMAT3DSD, stu.no, stu.name, stu.score);
	printf("\r\n");
}

//��ȡ���гɼ�������
void readallstudents()
{
	char line[200];
	student *p1, *p2;
	FILE *fp = fopen(scoresfile, "r");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p1 = p2 = (student *)malloc(sizeof(student));
	head = p1;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			break;
		//����������ȥ��ĩβ���з�����Ҫ
		//http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input 
		strtok(line, "\n");
		getstudentfromline(line, p1);
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (student*)malloc(sizeof(student));
	}
	p2->next = NULL;
}


//�������гɼ�
void writeallstudents()
{
	student *p;
	FILE *fp = fopen(scoresfile, "wb");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}

	p = head;

	while (p != NULL)
	{
		student stu = *p;

		fprintf(fp, FORMAT3DSD, stu.no, stu.name, stu.score);
		p = p->next;
	}
	fclose(fp);
	printf("�ѱ��浽�ļ���");
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

int getnewno(student **tail)
{
	int newno = 0;
	student *p = head;
	if (head->no > newno)
		newno = head->no;
	while (p->next != NULL)
	{
		if (p->no > newno)
			newno = p->no;
		p = p->next;
	}
	if (p->no > newno)
		newno = p->no;
	newno++;
	*tail = p;
	return newno;
}

//�����ɼ�
void addstudent()
{
	int newno = 0, score;//�³ɼ���ţ���ǰ���+1
	student *p = head;
	student *n;
	char name[50] = "";

	inputname(name);

	newno = getnewno(&p);

	n = (student *)malloc(sizeof(student));

	n->no = newno;
	strcpy(n->name, name);
	score = inputscore();
	n->score = score;

	p->next = n;
	n->next = NULL;
	printf("\n%s�ɼ�%d��ӳɹ�!\n", name, score);
}


bool insert(student *pHead, int front, char *name, int score)
{
	int i = 0, newno;
	student *_node = pHead;
	student *pSwap;
	student *pNew;
	student *x;
	newno = getnewno(&x);
	if ((front < 1) && (NULL != _node))
	{
		return false;
	}
	while (i < front - 1)
	{
		_node = _node->next;
		++i;
	}
	pNew = (student*)malloc(sizeof(student));

	pNew->no = newno;
	strcpy(pNew->name, name);
	pNew->score = score;
	pSwap = _node->next;
	_node->next = pNew;
	pNew->next = pSwap;
	return true;

}

//ɾ���ɼ�
//http://blog.csdn.net/iwm_next/article/details/7450734
void deletestudent(char * name)
{
	student *p1 = head, *p2;
	if (head == NULL)
	{
		printf("\n�ɼ�Ϊ��!\n");
		return;
	}
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (strcmp(p1->name, name) == 0)
	{

		if (p1 == head)
			head = p1->next;
		else
		{
			p2->next = p1->next;
			free(p1);
			printf("��ɾ������Ϊ%s��ѧ���ĳɼ���\r\n", name);
		}
	}
	else
		printf("û�ҵ�����Ϊ%s��ѧ��!\r\n", name);
}

void viewstudent(char * name)
{
	int found = 0;
	student *p = head;

	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			found = 1;
			printf("%s�ĳɼ�����\r\n", name);

			displaystudent(*p);
		}
		p = p->next;
	}
	if (!found)
		printf("û�ҵ���Ϊ%s��ѧ��\r\n", name);
}

void viewallstudents()
{
	student *p = head;

	printf("����ѧ���ɼ�����\r\n");
	while (p != NULL)
	{
		displaystudent(*p);
		p = p->next;
	}
}

void createsamplestudents()
{
	FILE *fp = fopen(scoresfile, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMAT3DSD, 1, "Flex", 75);
	fprintf(fp, FORMAT3DSD, 2, "Tony", 80);
	fprintf(fp, FORMAT3DSD, 3, "������������", 90);
	fprintf(fp, FORMAT3DSD, 4, "Lukas", 88);
	fprintf(fp, FORMAT3DSD, 5, "Shawn", 100);

	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽student.txt��");
}

int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->score - ((student*)b)->score;
}
void sortandviewall()
{
	int i, cnt = 0;
	student all[50];
	student *p = head;

	printf("����ѧ���ɼ����������������\r\n");
	while (p != NULL)
	{
		student stu;
		stu.no = p->no;
		strcpy(stu.name, p->name);
		stu.score = p->score;
		all[cnt++] = stu;
		p = p->next;
	}
	qsort(all, cnt, sizeof(student), cmpfunc);
	for (i = 0; i < cnt; i++)
	{
		displaystudent(all[i]);
	}
}

void promptinsertbeforeno()
{
	int no, score;
	char name[50] = "";
	printf("\n������Ҫ���ĸ���ŵ�ѧ��֮�����?\n");
	scanf("%d", &no);

	inputname(name);
	score = inputscore();
	if (insert(head, no, name, score))
		printf("\n����ɹ���\n");
}

void promptsearchtotalbyname()
{
	char name[50] = "";
	inputname(name);
	viewstudent(name);
}

void promptdeletebyname()
{
	char name[50] = "";
	inputname(name);
	deletestudent(name);
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

int main()
{
	int choice = -1;

	if (login())
	{
		printf("login ok\n");
	}
	else
		printf("login fail\n");

	//createsamplestudents();

	//readallstudents();
	//viewallstudents();
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

