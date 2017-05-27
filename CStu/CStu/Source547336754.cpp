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
}student;

student allstudents[100];
int allstudentscount = 0;

float averagechinese, averagemath, averageenglish;

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
void sortstudentsbytotal()
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
	sortstudentsbytotal();
	printf("��ÿ��ѧ������ƽ���ɼ����������\r\n");
	displayallstudents();
}

int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].no, no))
			return i;
	}
	return -1;
}

void editstudent(char no[50])
{
	int i;
	i = getstudentidexbyno(no);
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
	scanf("%s", &no);
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
	char no[50]; char name[MAX_STRLEN] = "";
	int math; int english; int chinese;
	printf("\n������ѧ�ź��������ո����\n");
	scanf("%s%s", no, name);
	printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
	scanf("%d%d%d", &chinese, &math, &english);
	addstudent(no, name, chinese, math, english);
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

void calccoursesaverages()
{
	int i, sum;
	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].chinese;
	}
	averagechinese = sum / (float)allstudentscount;

	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].math;
	}
	averagemath = sum / (float)allstudentscount;

	sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].english;
	}
	averageenglish = sum / (float)allstudentscount;
}

void calccoursesaveragesanddisplay()
{
	calccoursesaverages();
	printf("����ƽ����:%.1f\n", averagechinese);
	printf("��ѧƽ����:%.1f\n", averagemath);
	printf("Ӣ��ƽ����:%.1f\n", averageenglish);
}

void calccoursesaveragesbelowcountanddisplay()
{
	int i, c;
	calccoursesaverages();
	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].chinese > averagechinese)
			c++;
	}
	printf("��������ƽ���ɼ���ѧ������:%d\n", c);

	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].math > averagemath)
			c++;
	}
	printf("������ѧƽ���ɼ���ѧ������:%d\n", c);

	c = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].english > averageenglish)
			c++;
	}
	printf("����Ӣ��ƽ���ɼ���ѧ������:%d\n", c);
}


void menuf()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t    1����ʾÿ�ſγ̳ɼ���ߵ�ѧ��������Ϣ");
		printf("\n\t    2����ʾÿ�ſγ̵�ƽ���ɼ�");
		printf("\n\t    3����ʾ����ĳ�ſγ�ƽ���ɼ���ѧ������");
		printf("\n\t  ��0�����ϼ�\n");
		fseek(stdin, 0, SEEK_END);//������뻺��������������Ƿ����������ѭ��
		choice = getchar();
		switch (choice)
		{
		case '1':
			calcanddisplaycoursehighest();
			break;
		case '2':
			calccoursesaveragesanddisplay();
			break;
		case '3':
			calccoursesaveragesbelowcountanddisplay();
			break;
		default:
			printf("\n\n��������!");
			break;
		}
	}
}

int main()
{
	char choice = -1;


#if 0
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
	readallstudents();
	while (choice != 'g')
	{
		printf("\n\t ��ѡ��ϵͳ������");
		printf("\n\t a���ɼ�¼��");
		printf("\n\t b���ɼ���ʾ");
		printf("\n\t c���ɼ�����");
		printf("\n\t d���ɼ�����");
		printf("\n\t e���ɼ��޸�");
		printf("\n\t f���ɼ�ͳ��");
		printf("\n\t    1����ʾÿ�ſγ̳ɼ���ߵ�ѧ��������Ϣ");
		printf("\n\t    2����ʾÿ�ſγ̵�ƽ���ɼ�");
		printf("\n\t    3����ʾ����ĳ�ſγ�ƽ���ɼ���ѧ������");
		printf("\n\t g���˳�ϵͳ\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case 'a':
			printf("\n\n��ѡ���� a\n");
			promptaddstudent();
		case 'b':
			printf("\n\n��ѡ���� b\n");
			displayallstudents();
			break;
		case 'c':
			printf("\n\n��ѡ���� c\n");
			writeallstudents();
			break;
		case 'd':
			printf("\n\n��ѡ���� d\n");
			sortanddisplay();
			break;
		case 'e':
			printf("\n\n��ѡ���� e\n");
			prompteditstudent();
			break;
		case 'f':
			printf("\n\n��ѡ���� f\n");
			menuf();
			break;
		case 'g':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
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

