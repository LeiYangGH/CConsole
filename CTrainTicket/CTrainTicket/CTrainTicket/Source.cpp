#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TRAIN_COUNT 10
#define MAX_CARRIAGE_COUNT 20
#define MAX_SEAT_COUNT 130

int order[MAX_TRAIN_COUNT][MAX_CARRIAGE_COUNT][MAX_SEAT_COUNT];
int traincount = 0;
int carriagecount = 0;
int seatcount = 0;
int initdone = 0;
#define TEST 0
//
//int subjects_count = 3;//Ĭ�Ͽ�Ŀ��
//
//student allstudents[STUDENTS_COUNT];
//int allstudentscount = 0;
//
//void promptinputsubjectcount()
//{
//	printf("�������Ŀ������1��6��:");
//	scanf("%d", &subjects_count);
//	fseek(stdin, 0, SEEK_END);
//	if (subjects_count < 1 || subjects_count>6)
//		subjects_count = 3;//Ĭ�Ͽ�Ŀ����
//}
//
//void displaystudent(student stu)
//{
//	int i;
//	printf("\r\n");
//	printf("%s\t%s\t", stu.no, stu.name);
//	for (i = 0; i < subjects_count; i++)
//	{
//		printf("%d\t", stu.scores[i]);
//	}
//	printf("%d\t%.1f\n", stu.total, stu.average);
//
//}
//
//void displayallstudents()
//{
//	int i;
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		displaystudent(allstudents[i]);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
////����������
//int cmpbytotal(const void * a, const void * b)
//{
//	return ((student*)a)->total - ((student*)b)->total;
//}
//
//int cmpbyno(const void * a, const void * b)
//{
//	return ((student*)a)->no - ((student*)b)->no;
//}
//
//void sortanddisplaybytotal()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmpbytotal);
//	printf("���ܷ����������\r\n");
//	displayallstudents();
//}
//
//void sortanddisplaybyno()
//{
//	qsort(allstudents, allstudentscount, sizeof(student), cmpbyno);
//	printf("��ѧ�����������\r\n");
//	displayallstudents();
//}
//
//void countbygradesforonesubject(int subjectId)
//{
//	int i, t, cnt100_90 = 0, cnt89_80 = 0, cnt79_70 = 0, cnt69_60 = 0, cnt59_0 = 0;
//	printf("��%d��Ŀ�ɼ��ڸ���ֵ�εĳɼ�����ͳ�����£�\r\n", subjectId + 1);
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allstudentscount; i++)
//	{
//		t = allstudents[i].scores[subjectId];
//		if (t >= 90)
//			cnt100_90++;
//		else if (t >= 80 && t <= 89)
//			cnt89_80++;
//		else if (t >= 70 && t <= 79)
//			cnt79_70++;
//		else if (t >= 60 && t <= 69)
//			cnt69_60++;
//		else if (t < 149)
//			cnt59_0++;
//	}
//	printf("100-90\t89-80\t79-70\t69-60\t59-0\t\n");
//	printf("%d\t%d\t%d\t%d\t%d\n",
//		cnt100_90, cnt89_80, cnt79_70, cnt69_60, cnt59_0);
//	printf("%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\n",
//		cnt100_90 * 100 / (float)allstudentscount,
//		cnt89_80 * 100 / (float)allstudentscount,
//		cnt79_70 * 100 / (float)allstudentscount,
//		cnt69_60 * 100 / (float)allstudentscount,
//		cnt59_0 * 100 / (float)allstudentscount
//	);
//	printf("--------------------------------------------\r\n");
//}
//
//void countbygrades()
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < subjects_count; i++)
//	{
//		countbygradesforonesubject(i);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
//void searchtotalbyname(char *name)
//{
//	int i;
//	//�Ȱ��ܷ�����
//	qsort(allstudents, allstudentscount, sizeof(student), cmpbytotal);
//	for (i = 0; i < allstudentscount; i++)
//		if (strcmp(name, allstudents[i].name) == 0)
//		{
//			printf("%s,��%d��, ��ϸ����\n", name, allstudentscount - i);
//			displaystudent(allstudents[i]);
//			return;
//		}
//	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
//}
//
//void promptsearchtotalbyname()
//{
//	char name[MAX_STRLEN] = "";
//	printf("������Ҫ��ѯ��ѧ������:");
//	scanf("%s", &name);
//	searchtotalbyname(name);
//}
//
//
//void addstudent(char no[], char name[], int scores[])
//{
//	int i;
//	student stu;
//	strcpy(stu.no, no);
//	strcpy(stu.name, name);
//	stu.total = 0;
//	for (i = 0; i < subjects_count; i++)
//	{
//		stu.scores[i] = scores[i];
//		stu.total += scores[i];
//	}
//	for (i = subjects_count; i < MAX_SUBJECT_COUNT; i++)
//	{
//		stu.scores[i] = 0;
//	}
//	stu.average = stu.total / (float)subjects_count;
//	allstudents[allstudentscount++] = stu;
//}
//


//void calcanddisplaytotalandaverage()
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	student stu;
//	printf("��Ŀ\t�ܷ�\tƽ����\n");
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < subjects_count; i++)
//	{
//		calcanddisplaytotalandaverageforonesubject(i);
//	}
//	printf("--------------------------------------------\r\n");
//}

void inputnum(int *num, int max, char *description)
{
	int input = 0;
	do
	{
		printf("\n������%s,(��Χ1~%d):", description, max);
		scanf("%d", &input);
		fseek(stdin, 0, SEEK_END);
	} while (input<1 || input>max);
	*num = input;
}

void init()
{
	int i, j, k;
#if TEST
	traincount = 2;
	carriagecount = 2;
	seatcount = 2;
#else
	if (initdone)
	{
		printf("�Ѿ���ʼ�����������ٳ�ʼ��\n");
		return;
	}
	inputnum(&traincount, MAX_TRAIN_COUNT, "������");
	inputnum(&carriagecount, MAX_CARRIAGE_COUNT, "ÿ���εĳ�����");
	inputnum(&seatcount, MAX_SEAT_COUNT, "ÿ�������λ��");
	for (i = 0; i < traincount; i++)
		for (j = 0; j < carriagecount; j++)
			for (k = 0; k < seatcount; k++)
				order[i][j][k] = 0;
	initdone = 1;

#endif
}

void showavailableseats(int trainid, int carriageid)
{
	int train, i, j, k;
	printf("��%d���� ��%d����ʣ����λ������:\n", trainid + 1, carriageid + 1);
	printf("--------------------------------------------\n");
	for (k = 0; k < seatcount; k++)
	{
		if (order[trainid][carriageid][k] == 0)
		{
			printf("%d\t", k + 1);
		}
	}
	printf("\n--------------------------------------------\n");
}



void showavailable(int trainid)
{
	int j;
	for (j = 0; j < carriagecount; j++)
		showavailableseats(trainid, j);
}

void promptshowavailable()
{
	int i;
	if (!initdone)
	{
		printf("���ȳ�ʼ����ִ����������\n");
		return;
	}
	inputnum(&i, carriagecount, "Ҫ��ѯ��Ʊ�ĳ���");
	showavailable(i - 1);
}

int main()
{
	int choice = -1;
#if TEST
	init();
	showavailable(0);
	showavailable(1);
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �𳵶�Ʊϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ʼ��");
		printf("\n\t 2. ��ѯ");
		//printf("\n\t 3. ��Ʊ");
		//printf("\n\t 4. ��Ʊ");
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
			init();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptshowavailable();
			break;
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			//	sortanddisplaybytotal();
			//	break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			//	sortanddisplaybyno();
			//	break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	promptsearchtotalbyname();
			//	break;
			//case '6':
			//	printf("\n\n��ѡ���� 6\n");
			//	countbygrades();
			//	break;
			//case '7':
			//	printf("\n\n��ѡ���� 7\n");
			//	sortanddisplaybyno();
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

