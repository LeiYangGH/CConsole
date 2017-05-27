#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
#define MAX_STRLEN 20
typedef struct student
{
	char no[50];
	char name[50];
	int chinese;
	int math;
	int english;
	int total;
	float average;
}student;
//char *coursenames[3] = { "����","��ѧ", "Ӣ��" };
student allstudents[100];
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
			stu.math = toint(part);
			break;
		case 4:
			stu.english = toint(part);
			break;
		case 5:
			stu.chinese = toint(part);
			break;
			/*case 6:
				stu.c = toint(part);
				break;
			case 7:
				stu.total = toint(part);
				break;
			case 8:
				stu.average = tofloat(part);
				break;*/
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
	}
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

int cmpfunc(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = allstudents[i].chinese + allstudents[i].math + allstudents[i].english;
	}
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("���������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
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



int getstudentidexbyid(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		student b = allstudents[i];
		if (streq(b.no, no))
			return i;
	}
	return -1;
}

void editstudent(char no[50])
{
	int i;
	i = getstudentidexbyid(no);
	if (i >= 0)
	{
		printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
		scanf("%d%d%d", &allstudents[i].chinese, &allstudents[i].math, &allstudents[i].english);
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧѧ�ŵ�ѧ����\r\n");
	}

}

void prompteditstudent()
{
	char no[50];
	printf("������Ҫ�޸ĵ�ѧ��:");
	scanf("%d", &no);
	editstudent(no);
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
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.math, stu.english, stu.chinese);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}


void addstudent(char no[50], char name[], int math, int english, int chinese)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.math = math;
	stu.english = english;
	stu.chinese = chinese;
	allstudents[allstudentscount++] = stu;
}




void promptaddstudent()
{
	char no[50]; char name[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n������ѧ��\n");
	scanf("%d", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
	scanf("%d%d%d%d", &chinese, &math, &english);
	addstudent(no, name, math, english, chinese);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}

void calcanddisplaycoursehighest()
{
	int i, t, index, h;

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].chinese;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("������߷�:%d\tѧ��:%s\n", h, allstudents[index].name);

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].math;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("��ѧ��߷�:%d\tѧ��:%s\n", h, allstudents[index].name);

	h = 0;
	index = -1;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].english;
		if (h < t)
		{
			h = t;
			index = i;
		}
	}
	printf("Ӣ����߷�:%d\tѧ��:%s\n", h, allstudents[index].name);
}


int main()
{
	int choice = -1;

#if 1
	//readallstudents();

	addstudent("04", "n4", 41, 92, 43);
	addstudent("01", "n1", 11, 12, 13);
	addstudent("02", "n2", 21, 22, 93);
	addstudent("05", "n5", 51, 52, 53);
	addstudent("06", "n6", 61, 62, 63);
	addstudent("03", "n3", 31, 32, 33);
	//editstudent("01");
	////printf("\n%d\n", allstudentscount);
	///*promptaddstudent();
	//writeallstudents();*/
	///*prompteditstudent();
	//writeallstudents();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	calcanddisplaycoursehighest();
	system("pause");

#endif
	while (choice != 0)
	{
		char *menu = "**********************�˵�****************************\n"
			"��1��������ѧ������               ��6����ѧ�Ƽ������\n"
			"��2��������������ѯ               ��7����ѧ����������\n"
			"��3��������ѧ�Ų�ѯ               ��8��������ѧ������\n"
			"��4�������ѧ������               ��9�� : �鿴ѧ������\n"
			"��5�����޸�ѧ������               ��10���������ƽ����\n"
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

			break;
		case 3:

			break;
		case 4:
			promptaddstudent();
			break;
		case 5:
			prompteditstudent();
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
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

