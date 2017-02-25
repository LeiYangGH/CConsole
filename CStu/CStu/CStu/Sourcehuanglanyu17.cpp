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

void countbygradesforonesubject(int subjectId)
{
	int i, t, cnt100_90 = 0, cnt89_80 = 0, cnt79_70 = 0, cnt69_60 = 0, cnt59_0 = 0;
	student stu;
	printf("��%d��Ŀ�ɼ��ڸ���ֵ�εĳɼ�����ͳ�����£�\r\n", subjectId + 1);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].scores[subjectId];
		if (t >= 90)
			cnt100_90++;
		else if (t >= 80 && t <= 89)
			cnt89_80++;
		else if (t >= 70 && t <= 79)
			cnt79_70++;
		else if (t >= 60 && t <= 69)
			cnt69_60++;
		else if (t < 149)
			cnt59_0++;
	}
	printf("100-90\t89-80\t79-70\t69-60\t59-0\t\n");
	printf("%d\t%d\t%d\t%d\t%d\n",
		cnt100_90, cnt89_80, cnt79_70, cnt69_60, cnt59_0);
	printf("%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\n",
		cnt100_90 * 100 / (float)allstudentscount,
		cnt89_80 * 100 / (float)allstudentscount,
		cnt79_70 * 100 / (float)allstudentscount,
		cnt69_60 * 100 / (float)allstudentscount,
		cnt59_0 * 100 / (float)allstudentscount
	);
	printf("--------------------------------------------\r\n");
}

void countbygrades()
{
	int i;
	int totalSubject = 0;
	float aveSubject;
	student stu;
	printf("--------------------------------------------\r\n");
	for (i = 0; i < subjects_count; i++)
	{
		countbygradesforonesubject(i);
	}
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
	//�Ȱ��ܷ�����
	qsort(allstudents, allstudentscount, sizeof(student), cmpbytotal);
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			printf("%s,��%d��, ��ϸ����\n", name, allstudentscount - i);
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
	scores[2] = 1;
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
		printf("\n\t 5. ��������ѯѧ���������俼�Գɼ�");
		printf("\n\t 6. ͳ��");
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
			promptsearchtotalbyname();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			countbygrades();
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

