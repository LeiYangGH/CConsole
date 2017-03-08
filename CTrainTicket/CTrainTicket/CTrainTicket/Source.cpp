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
//void createsamplestudents()
//{
//	int scores[MAX_SUBJECT_COUNT];
//	printf("����ʾ���ɼ�����...");
//	scores[0] = 93;
//	scores[1] = 96;
//	scores[2] = 91;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addstudent("16001123", "Smile", scores);
//	scores[0] = 95;
//	scores[1] = 85;
//	scores[2] = 65;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addstudent("20161465", "Shawn", scores);
//	scores[0] = 92;
//	scores[1] = 82;
//	scores[2] = 1;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addstudent("30161465", "Tony", scores);
//	//addstudent("16004", "Flex", 91, 81, 61);
//	//addstudent("16005", "Smile5", 63, 63, 66);
//	//addstudent("16006", "Smile6", 96, 83, 63);
//	//addstudent("16007", "Smile7", 93, 83, 56);
//	//addstudent("16008", "Smile8", 97, 83, 73);
//	//addstudent("16009", "Smile9", 55, 55, 58);
//	//addstudent("16010", "Smile10", 13, 13, 43);
//	//allstudentscount = 1;
//	printf("ʾ���ɼ������Ѵ�����\n");
//
//}
//
//void promptaddstudent()
//{
//	int i;
//	char no[MAX_STRLEN];
//	char name[MAX_STRLEN] = "";
//	int scores[MAX_SUBJECT_COUNT];
//	printf("\n������ѧ��\n");
//	scanf("%s", &no);
//	printf("\n����������\n");
//	scanf("%s", name);
//	for (i = 0; i < subjects_count; i++)
//	{
//		printf("\n�������%d�Ƴɼ���������:", i + 1);
//		scanf("%d", &scores[i]);
//	}
//	addstudent(no, name, scores);
//	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
//}
//
//void calcanddisplaytotalandaverageforonesubject(int subjectId)
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	student stu;
//	for (i = 0; i < allstudentscount; i++)
//	{
//		totalSubject += allstudents[i].scores[subjectId];
//	}
//	aveSubject = totalSubject / (float)allstudentscount;
//	printf("%d\t%d\t%.1f\n", subjectId + 1, totalSubject, aveSubject);
//
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

void initmax(int *num, int max, char *description)
{
	int input = 0;
	do
	{
		printf("\n������%s,(��Χ1~%d):", description, max);
		scanf("%d", &input);
		fseek(stdin, 0, SEEK_END);
	} while (input<1 || input>max);
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
		printf("�Ѿ���ʼ�����������ٳ�ʼ��\n");
	else
	{
		initmax(&traincount, MAX_TRAIN_COUNT, "������");
		initmax(&carriagecount, MAX_CARRIAGE_COUNT, "ÿ���εĳ�����");
		initmax(&seatcount, MAX_SEAT_COUNT, "ÿ�������λ��");
		for (i = 0; i < traincount; i++)
			for (j = 0; j < carriagecount; j++)
				for (k = 0; k < seatcount; k++)
					order[i][j][k] = 0;
		initdone = 1;
	}
#endif
}

int main()
{
	int choice = -1;
#if TEST
	init();
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t �𳵶�Ʊϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ʼ��");
		//printf("\n\t 2. ��ѯ");
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
			//case '2':
			//	printf("\n\n��ѡ���� 2\n");
			//	calcanddisplaytotalandaverage();
			//	break;
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

