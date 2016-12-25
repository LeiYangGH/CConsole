#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FORMAT "%s\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STUDENTS_COUNT 10
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
#define STU_MEMBERS_NET stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
typedef struct student
{
	char no[50];
	char name[50];
	int score[3];
	int total;
}student;

student allstudents[STUDENTS_COUNT];
int allstudentscount = 0;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

////�ַ���ת����
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}

void displaystudent(student stu)
{
	printf("\r\n");
	printf(FORMAT, STU_MEMBERS_NET);
}

void displayallstudents()
{
	int i;
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//����������
int cmpfunc(const void * a, const void * b)
{
	return ((student*)b)->total - ((student*)a)->total;
}

void sortanddisplay()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
	printf("���ܳɼ��������������\r\n");
	displayallstudents();
}

void countbygrades()
{
	int i, t, cnt270300 = 0, cnt240269 = 0, cnt210239 = 0, cnt180209 = 0, cnt150179 = 0, cnt149 = 0;
	student stu;
	printf("�ܳɼ��ڸ���ֵ�εĳɼ�������������ͳ�����£�\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].total;
		if (t >= 270)
			cnt270300++;
		else if (t >= 240 && t <= 269)
			cnt240269++;
		else if (t >= 210 && t <= 239)
			cnt210239++;
		else if (t >= 180 && t <= 209)
			cnt180209++;
		else if (t >= 150 && t <= 179)
			cnt150179++;
		else if (t < 149)
			cnt149++;
	}
	printf("270~300\t240~269\t210~239\t180~209\t150~179\t149����\t������\r\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\r\n",
		cnt270300, cnt240269, cnt210239, cnt180209, cnt150179, cnt149);
	//��Ϊ������10���ˣ����԰ٷֱȾ�������*10
	printf("%d%%\t%d%%\t%d%%\t%d%%\t%d%%\t%d%%\t%d%%\r\n",
		cnt270300 * 10, cnt240269 * 10, cnt210239 * 10, cnt180209 * 10, cnt150179 * 10, cnt149 * 10,
		(cnt270300 + cnt240269 + cnt210239 + cnt180209) * 10);
	printf("--------------------------------------------\r\n");
}

void calcminmaxave()
{
	int i, min = 300, max = 0, t;
	float sum = 0, ave;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].total;
		sum += t;
		min = t < min ? t : min;
		max = t > max ? t : max;
	}
	ave = sum / STUDENTS_COUNT;
	printf("�ܳɼ���߷֣�%d��, ��ͷ�:%d��, ƽ����:%f��\r\n",
		max, min, ave);
}

//void inputstring(char str[])
//{
//	int len = -1;
//	char input[50] = "";
//	while (len < 1 || len > MAX_STRLEN)
//	{
//		printf("����������:");
//		fseek(stdin, 0, SEEK_END);
//		scanf("%s", input);
//		len = strlen(input);
//	}
//	strcpy(str, input);
//}

void searchtotalbyname(char *name)
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

void promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("������Ҫ��ѯ��ѧ������:");
	scanf("%s", &name);
	searchtotalbyname(name);
}

void searchtotalbyno(char no[])
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

void promptsearchtotalbyno()
{
	char no[MAX_STRLEN];
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%s", &no);
	searchtotalbyno(no);
}

void addstudent(char no[], char name[], int s0, int s1, int s2)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.total = s0 + s1 + s2;
	allstudents[allstudentscount++] = stu;
}

void createsamplestudents()
{
	printf("����ʾ���ɼ�����...");
	addstudent("16001", "Smile", 93, 96, 91);
	addstudent("16002", "Shawn", 95, 85, 65);
	addstudent("16003", "Tony", 92, 82, 62);
	addstudent("16004", "Flex", 91, 81, 61);
	addstudent("16005", "Smile5", 63, 63, 66);
	addstudent("16006", "Smile6", 96, 83, 63);
	addstudent("16007", "Smile7", 93, 83, 56);
	addstudent("16008", "Smile8", 97, 83, 73);
	addstudent("16009", "Smile9", 55, 55, 58);
	addstudent("16010", "Smile10", 13, 13, 43);
	allstudentscount = 9;
	printf("9��ʾ���ɼ������Ѵ�����\n");

}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3;
	printf("\n������ѧ��\n");
	scanf("%s", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n���������Ƴɼ������������ո����\n");
	scanf("%d%d%d", &s1, &s2, &s3);
	addstudent(no, name, s1, s2, s3);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;
	//createsamplestudents();
	//displayallstudents();
	//calcminmaxave();
	//countbygrades();
	//sortanddisplay();
	//system("pause");
	while (choice != 0)
	{
		printf("\n\t (��������س���û��Ӧ�����ٰ�һ��)");
		printf("\n\t ѧ���ɼ������ѯͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ���ѧ���ɼ�");
		printf("\n\t 2. ����������ƽ��");
		printf("\n\t 3. �ֶα����ͼ�����");
		printf("\n\t 4. ���ֵܷ�������");
		printf("\n\t 5. ����ѧ�Ų�ѯ");
		printf("\n\t 6. ����������ѯ");
		printf("\n\t 7. ����9��ʾ������");
		printf("\n\n  ��ѡ��: ");
		scanf("%1[01234567]d%*c", &choice);
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
			promptaddstudent();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			calcminmaxave();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			countbygrades();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			sortanddisplay();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptsearchtotalbyno();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			promptsearchtotalbyname();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			createsamplestudents();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

