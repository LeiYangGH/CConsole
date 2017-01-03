#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define MAX_STRLEN 20
#define SINGERS_COUNT 10
#define JUDGES_COUNT 10
#define LINE  "\n------------------------\n"
typedef struct singer
{
	int no;
	char name[50];
	int score[JUDGES_COUNT];
	int total;
	float ave;
}singer;

singer allsingers[SINGERS_COUNT];
int allsingerscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaysinger(singer sgr)
{
	int i;
	printf("\n");
	printf("���ֱ�ţ�%d\t������%s\t�������£�\n", sgr.no, sgr.name, sgr.total);
	for (i = 0; i < JUDGES_COUNT; i++)
		printf("%d\t", sgr.score[i]);
	printf("\n");
}

void displayallsingers()
{
	int i;
	printf("����ԭʼ�ɼ�����\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(allsingers[i]);
	}
	printf("--------------------------------------------\n");
}

void displayallave()
{
	int i;
	singer sgr;
	printf("�������ճɼ�����\n", allsingerscount);
	printf("���\t����\t�ɼ�\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		printf("%d\t%s\t%.1f\n", sgr.no, sgr.name, sgr.ave);
	}
	printf("--------------------------------------------\n");
}

int cmpfunc(const void * a, const void * b)
{
	return ((singer*)b)->ave - ((singer*)a)->ave;
}

void displayscoreandrank(singer sgr, int rank)
{
	printf("���\t����\t�ɼ�\t����\n");
	printf("%d\t%s\t%.1f\t%d\n",
		sgr.no, sgr.name, sgr.ave, rank);
}

void addsinger(int no, char name[], int scores[])
{
	int i;
	singer sgr;
	sgr.no = no;
	strcpy(sgr.name, name);
	for (i = 0; i < JUDGES_COUNT; i++)
		sgr.score[i] = scores[i];
	sgr.total = 0;
	allsingers[allsingerscount++] = sgr;
}

void createsamplesingers()
{
	int scores1[JUDGES_COUNT] = { 11,12,13,14,15,16,17,18,19,91 };
	int scores2[JUDGES_COUNT] = { 21,22,23,24,25,26,27,28,29,92 };
	int scores3[JUDGES_COUNT] = { 31,32,33,34,35,36,37,38,39,93 };
	int scores4[JUDGES_COUNT] = { 41,42,44,44,45,46,47,48,49,94 };
	int scores5[JUDGES_COUNT] = { 51,52,55,55,55,56,57,58,59,95 };
	int scores6[JUDGES_COUNT] = { 61,62,66,66,66,66,67,68,69,96 };
	int scores7[JUDGES_COUNT] = { 71,72,77,77,77,77,77,78,79,97 };
	int scores8[JUDGES_COUNT] = { 81,82,88,88,88,88,88,88,89,98 };

	printf("����ʾ����������...");
	addsinger(1, "name1", scores1);
	addsinger(3, "name3", scores3);
	addsinger(2, "name2", scores2);
	addsinger(4, "name4", scores4);
	addsinger(5, "name5", scores5);
	addsinger(6, "name6", scores6);
	addsinger(7, "name7", scores7);
	addsinger(8, "name8", scores8);
	printf("8��ʾ�����������Ѵ���\n");
}

void calcandsortaverage()
{
	int i, j, min, max, score;
	for (i = 0; i < allsingerscount; i++)
	{
		min = max = allsingers[i].score[0];//��ʼֵ
		allsingers[i].total = 0;
		for (j = 0; j < JUDGES_COUNT; j++)
		{
			score = allsingers[i].score[j];
			allsingers[i].total += score;
			if (min > score)
				min = score;
			if (max < score)
				max = score;
		}
		allsingers[i].total -= (min + max);
		allsingers[i].ave = allsingers[i].total / (float)(JUDGES_COUNT - 2);
	}
	qsort(allsingers, allsingerscount, sizeof(singer), cmpfunc);

}

void calcsortanddisplayaverage()
{
	calcandsortaverage();
	displayallave();
}


void inputaddsinger()
{
	int no; char name[MAX_STRLEN] = "";
	int scores[JUDGES_COUNT] = { 0 };
	printf("\n��������\n");
	scanf("%d", &no);
	printf("\n����������\n");
	scanf("%s", name);
	printf("\n������%d�����еĳɼ�(������)���ո����\n", JUDGES_COUNT);
	scanf("%d%d%d%d%d%d%d%d%d%d", &scores[0], &scores[1], &scores[2], &scores[3], &scores[4], &scores[5], &scores[6], &scores[7], &scores[8], &scores[9]);
	addsinger(no, name, scores);
	printf("��ɵ�%d������¼��!\n", allsingerscount);
}

void findtotalbyname(char *name)
{
	int i;
	singer sgr;
	calcandsortaverage();
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		if (strcmp(name, allsingers[i].name) == 0)
		{
			displayscoreandrank(sgr, i + 1);
			return;
		}
	}
	printf("û�ҵ���Ӧ���ֵ���Ϣ��\n");
}

int inputfindtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("������Ҫ��ѯ�ĸ��ֵ������������ո񣬻س�����:");
	scanf("%s", name);
	findtotalbyname(name);
	return strcmp(name, "q");
}



void findtotalbyno(int no)
{
	int i;
	singer sgr;
	calcandsortaverage();
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		if (allsingers[i].no == no)
		{
			displayscoreandrank(sgr, i + 1);
			return;
		}
	}
	printf("û�ҵ���Ӧ���ֵ���Ϣ��\n");
}

void inputfindtotalbyno()
{
	int no;
	printf("������Ҫ��ѯ�ĸ��ֵı��:");
	scanf("%d", &no);
	findtotalbyno(no);
}

int main()
{
	int choice = -1;
	createsamplesingers();

#if DEV

	inputaddsinger();

	displayallsingers();

	calcsortanddisplayaverage();
	//findtotalbyno(3);
	//inputfindtotalbyno();
	inputfindtotalbyname();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
#else
	while (choice != 0)
	{
		printf("\n\t �質��������");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼����һ�����ֵĳɼ�");
		printf("\n\t 2. �鿴���и��ֵĳɼ�");
		printf("\n\t 3. ������������ɼ�");
		printf("\n\t 4. ���ݸ��ֱ�Ų���");
		printf("\n\t 5. ���ݸ������ֲ���");
		printf("\n\n  ��ѡ��: ");
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
			inputaddsinger();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallsingers();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			calcsortanddisplayaverage();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			inputfindtotalbyno();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			inputfindtotalbyname();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
#endif
	system("pause");
	return 0;
}

