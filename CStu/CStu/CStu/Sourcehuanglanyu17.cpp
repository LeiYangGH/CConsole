#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRLEN 20
#define MAX_SUBJECT_COUNT 6
#define STUDENTS_COUNT 30
typedef struct student
{
	char no[50];
	char name[50];
	int scores[MAX_SUBJECT_COUNT];
	int total;
	float average;
}student;

int subjects_count = 3;//Ĭ�Ͽ�Ŀ��

student allstudents[STUDENTS_COUNT];
int allstudentscount = 0;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void promptinputsubjectcount()
{
	printf("�������Ŀ������1��6��:");
	scanf("%d", &subjects_count);
	fseek(stdin, 0, SEEK_END);
	if (subjects_count < 1 || subjects_count>6)
		subjects_count = 3;//Ĭ�Ͽ�Ŀ����
}

void displaystudent(student stu)
{
	int i;
	printf("\r\n");
	printf("%s\t%s\t", stu.no, stu.name);
	for (i = 0; i < subjects_count; i++)
	{
		printf("%d\t", stu.scores[i]);
	}
	printf("%d\t%.1f\n", stu.total, stu.average);

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
int cmpbytotal(const void * a, const void * b)
{
	return ((student*)a)->total - ((student*)b)->total;
}

int cmpbyno(const void * a, const void * b)
{
	return ((student*)a)->no - ((student*)b)->no;
}

void sortanddisplaybytotal()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpbytotal);
	printf("���ܷ����������\r\n");
	displayallstudents();
}

void sortanddisplaybyno()
{
	qsort(allstudents, allstudentscount, sizeof(student), cmpbyno);
	printf("��ѧ�����������\r\n");
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
	printf("�ܳɼ���߷֣�%d, ��ͷ�:%d, ƽ����:%.2f\r\n",
		max, min, ave);
}

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

void addstudent(char no[], char name[], int scores[])
{
	int i;
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.total = 0;
	for (i = 0; i < subjects_count; i++)
	{
		stu.scores[i] = scores[i];
		stu.total += scores[i];
	}
	for (i = subjects_count; i < MAX_SUBJECT_COUNT; i++)
	{
		stu.scores[i] = 0;
	}
	stu.average = stu.total / (float)subjects_count;
	allstudents[allstudentscount++] = stu;
}

void createsamplestudents()
{
	int scores[MAX_SUBJECT_COUNT];
	printf("����ʾ���ɼ�����...");
	scores[0] = 93;
	scores[1] = 96;
	scores[2] = 91;
	scores[3] = 0;
	scores[4] = 0;
	scores[5] = 0;
	addstudent("16001123", "Smile", scores);
	scores[0] = 95;
	scores[1] = 85;
	scores[2] = 65;
	scores[3] = 0;
	scores[4] = 0;
	scores[5] = 0;
	addstudent("20161465", "Shawn", scores);
	scores[0] = 92;
	scores[1] = 82;
	scores[2] = 61;
	scores[3] = 0;
	scores[4] = 0;
	scores[5] = 0;
	addstudent("30161465", "Tony", scores);
	//addstudent("16004", "Flex", 91, 81, 61);
	//addstudent("16005", "Smile5", 63, 63, 66);
	//addstudent("16006", "Smile6", 96, 83, 63);
	//addstudent("16007", "Smile7", 93, 83, 56);
	//addstudent("16008", "Smile8", 97, 83, 73);
	//addstudent("16009", "Smile9", 55, 55, 58);
	//addstudent("16010", "Smile10", 13, 13, 43);
	//allstudentscount = 1;
	printf("ʾ���ɼ������Ѵ�����\n");

}

void promptaddstudent()
{
	int i;
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int scores[MAX_SUBJECT_COUNT];
	printf("\n������ѧ��\n");
	scanf("%s", &no);
	printf("\n����������\n");
	scanf("%s", name);
	for (i = 0; i < subjects_count; i++)
	{
		printf("\n�������%d�Ƴɼ���������:", i + 1);
		scanf("%d", &scores[i]);
	}
	addstudent(no, name, scores);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}

void calcanddisplaytotalandaverageforonesubject(int subjectId)
{
	int i;
	int totalSubject = 0;
	float aveSubject;
	student stu;
	for (i = 0; i < allstudentscount; i++)
	{
		totalSubject += allstudents[i].scores[subjectId];
	}
	aveSubject = totalSubject / (float)allstudentscount;
	printf("%d\t%d\t%.1f\n", subjectId + 1, totalSubject, aveSubject);

}

void calcanddisplaytotalandaverage()
{
	int i;
	int totalSubject = 0;
	float aveSubject;
	student stu;
	printf("��Ŀ\t�ܷ�\tƽ����\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < subjects_count; i++)
	{
		calcanddisplaytotalandaverageforonesubject(i);
	}
	printf("--------------------------------------------\r\n");
}

int main()
{
	int choice = -1;
	//promptinputsubjectcount();
	createsamplestudents();
	//displayallstudents();
	//calcminmaxave();
	//countbygrades();
	//sortanddisplay();
	//system("pause");
	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ������ѯͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �ֶ�¼��");
		printf("\n\t 2. ����ÿ�ſγ̵��ֺܷ�ƽ����");
		printf("\n\t 3. ��ѧ���ܷ��ɸߵ����ų����α�");
		printf("\n\t 4. ��ѧ����С�����ų��ɼ���");
		//printf("\n\t 5. ��������ѯѧ���������俼�Գɼ�");
		//printf("\n\t 6. ͳ��");
		printf("\n\t 7. ���");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
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
			calcanddisplaytotalandaverage();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			sortanddisplaybytotal();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			sortanddisplaybyno();
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
			sortanddisplaybyno();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

